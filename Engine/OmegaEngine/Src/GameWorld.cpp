#include "Precompiled.h"
#include "GameWorld.h"
#include "Service.h"

using namespace Omega;

void GameWorld::Initialize(size_t capacity)
{
	OMEGAASSERT(!mInitialized, "[GameWorld] -- World already initialized.");

	for (const auto& service : mServices)
	{
		service->Initialize();
	}

	mGameObjectAllocator = std::make_unique<GameObjectAllocator>(capacity);
	mGameObjectHandlePool = std::make_unique<GameObjectHandlePool>(capacity);

	mInitialized = true;
}

void GameWorld::Terminate()
{
	if (!mInitialized) return;

	OMEGAASSERT(!mUpdating, "[GameWorld] -- Cannot terminate wotrld during update.");

	// Destroy all active objects
	mUpdating = true;
	std::for_each(mUpdateList.begin(), mUpdateList.end(), [this](const auto& gameObject)
		{
			Destroy(gameObject->GetHandle());
		});
	mUpdating = false;
	mUpdateList.clear();

	// Now destroy everything
	ProcessDestroyList();

	mGameObjectAllocator.reset();
	mGameObjectHandlePool.reset();

	for (const auto& service : mServices)
	{
		service->Terminate();
	}

	mInitialized = false;
}

void GameWorld::Create(std::initializer_list<std::filesystem::path> listTemplateFiles, std::string_view name)
{
	for (const std::filesystem::path& templatefiles : listTemplateFiles)
	{
		Create(templatefiles, name);
	}
}

GameObjectHandle GameWorld::Create(const std::filesystem::path& templateFileName, std::string_view name)
{
	auto gameObject = GameObjectFactory::Create(*mGameObjectAllocator, templateFileName);
	if (!gameObject)
	{
		LOG("[GameWorld] -- Failed to create game object from template %s.", templateFileName.u8string().c_str());
		return GameObjectHandle();
	}

	// Register with the handle pool
	const auto handle = mGameObjectHandlePool->Register(gameObject);

	// Initialize the game object
	gameObject->mWorld = this;
	gameObject->mName = name;
	gameObject->mHandle = handle;
	gameObject->Initialize();

	mUpdateList.emplace_back(gameObject);
	return handle;
}

GameObjectHandle GameWorld::Find(std::string_view name)
{
	auto iter = std::find_if(mUpdateList.begin(), mUpdateList.end(), [&name](auto& gameObject)
		{
			return gameObject->GetName() == name;
		});

	if (iter != mUpdateList.end())
	{
		return (*iter)->GetHandle();
	}

	return GameObjectHandle();
}

void GameWorld::Destroy(GameObjectHandle handle)
{
	if (!handle.IsValid()) return;

	// Cache the pointer and unregister with the handle pool.
	// No one can touch this game object anymore!
	GameObject* gameObject = handle.Get();
	mGameObjectHandlePool->Unregister(handle);

	// Check if we can destroy it now
	if (mUpdating)
	{
		mDestroyList.emplace_back(gameObject);
	}
	else
	{
		DestroyInternal(gameObject);
	}

	// remove from mUpdateList
	// game object terminate
	// unregister with handle pool ( invalidate all existing handles)
	// GameObjectFactory::Destroy
}

void GameWorld::Update(float deltaTime)
{
	OMEGAASSERT(!mUpdating, "[GameWorld] -- Already updating the world!");

	// Lock the update list
	mUpdating = true;

	for (const auto& service : mServices)
	{
		service->Update(deltaTime);
	}

	// Re-compute size in case new object
	// list during iteration.
	for (const auto& gameObj : mUpdateList)
	{
		if (gameObj->GetHandle().IsValid())
		{
			gameObj->Update(deltaTime);
		}
	}
	// Unlock the update list
	mUpdating = false;

	// Unlock the update list
	ProcessDestroyList();
}

void GameWorld::Render()
{
	for (const auto& service : mServices)
	{
		service->Render();
	}

	for (const auto& gameObject : mUpdateList)
	{
		gameObject->Render();
	}
}

void GameWorld::DebugUI()
{
	for (const auto& service : mServices)
	{
		service->DebugUI();
	}

	for (const auto& gameObject : mUpdateList)
	{
		gameObject->DebugUI();
	}
}

void GameWorld::DestroyInternal(GameObject* gameObject)
{
	OMEGAASSERT(!mUpdating, "[GameWorld] -- Cannot destroy game object during update.");

	// If pointer is invalid, nothing to do so just exit
	if (!gameObject) return;

	// First remove it from the update list
	if (const auto iter = std::find(mUpdateList.begin(), mUpdateList.end(), gameObject);
		iter != mUpdateList.end())
	{
		mUpdateList.erase(iter);
	}

	// Terminate the game object
	gameObject->Terminate();

	// Next destroy the game object
	GameObjectFactory::Destroy(*mGameObjectAllocator, gameObject);
}

void GameWorld::ProcessDestroyList()
{
	for (auto& gameObject : mDestroyList)
	{
		DestroyInternal(gameObject);
	}
	mDestroyList.clear();
}
