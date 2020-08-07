#include "Precompiled.h"
#include "GameWorld.h"

using namespace Omega;


void GameWorld::Initialize(size_t capacity)
{
	OMEGAASSERT(!mInitialized, "[GameWorld] -- World already initialized.");
	mGameObjectAllocator = std::make_unique<GameObjectAllocator>(capacity);
	mGameObjectHandlePool = std::make_unique<GameObjectHandlePool>(capacity);

	mInitialized = true;
}

void GameWorld::Terminate()
{
	if (!mInitialized) return;
	mGameObjectAllocator.reset();
	mGameObjectHandlePool.reset();
	mInitialized = false;
}

GameObjectHandle GameWorld::Create(const std::filesystem::path& templateFileName, std::string name)
{
	auto gameObject = GameObjectFactory::Create(*mGameObjectAllocator, templateFileName);
	if (!gameObject)
	{
		LOG("[GameWorld] -- Failed to create game object from template %s.", templateFileName.u8string().c_str());
		return GameObjectHandle();
	}

	// Register with the handle pool
	auto handle = mGameObjectHandlePool->Register(gameObject);

	// Initialize the game object
	gameObject->mWorld = this;
	gameObject->mName = std::move(name);
	gameObject->mHandle = handle;
	gameObject->Initialize();

	mUpdateList.push_back(gameObject);
	return handle;
}

GameObjectHandle GameWorld::Find(const std::string& name)
{
	auto iter = std::find_if(mUpdateList.begin(), mUpdateList.end(), [&name](auto gameObject)
	{
		return gameObject->GetName() == name;
	});

	if (iter != mUpdateList.end())
	{
		return (*iter)->GetHandle();
	}

	return GameObjectHandle();
}


void GameWorld::Update(float deltaTime)
{
	for (size_t i = 0; i < mUpdateList.size(); ++i)
	{
		GameObject* gameObject = mUpdateList[i];
		if (gameObject->GetHandle().IsValid())
		{
			gameObject->Update(deltaTime);
		}
	}
}

void GameWorld::Render()
{
	for (auto gameObject : mUpdateList)
	{
		gameObject->Render();
	}
}

void GameWorld::DebugUI()
{
	for (auto gameObject : mUpdateList)
	{
		gameObject->DebugUI();
	}
}