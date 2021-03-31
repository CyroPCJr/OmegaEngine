#include "Precompiled.h"
#include "TextureManager.h"

using namespace Omega::Graphics;

namespace
{
	std::unique_ptr<TextureManager> sTextureManager = nullptr;
}

void TextureManager::StaticInitialize(const std::filesystem::path& root)
{
	OMEGAASSERT(sTextureManager == nullptr, "[TextureManager] Manager already initialized!");
	sTextureManager = std::make_unique<TextureManager>();
	sTextureManager->SetRootPath(root);
}

void TextureManager::StaticTerminate()
{
	if (sTextureManager != nullptr)
	{
		sTextureManager->Clear();
		sTextureManager.reset();
	}
}

TextureManager* TextureManager::Get()
{
	OMEGAASSERT(sTextureManager != nullptr, "[TextureManager] No instance registered.");
	return sTextureManager.get();
}

TextureManager::~TextureManager()
{
	OMEGAASSERT(mInventory.empty(), "[TextureManager] Clear() must be called to clean up.");
}

TextureId TextureManager::Load(const std::filesystem::path& fileName, bool isUseRootPath)
{
	std::filesystem::path fullName = mRootPath;
	fullName = (isUseRootPath) ? fullName / fileName : fileName;

	std::hash<std::string> hasher;
	TextureId hash = hasher(fullName.u8string());
	auto [iter, successful] = mInventory.insert({ hash , nullptr });
	if (successful)
	{
		std::unique_ptr<Texture> texture = std::make_unique<Texture>();
		texture->Initialize(fullName);
		iter->second = std::move(texture);
	}

	return hash;
}

void TextureManager::Clear()
{
	for (auto& [id, texture] : mInventory)
	{
		if (texture)
		{
			texture->Terminate();
			texture.reset();
		}
	}
	mInventory.clear();
}

void TextureManager::BindVS(TextureId id, uint32_t slot)
{
	if (Texture* texture = GetTexture(id); texture)
	{
		texture->BindVS(slot);
	}
}

void TextureManager::BindPS(TextureId id, uint32_t slot)
{
	if (Texture* texture = GetTexture(id); texture)
	{
		texture->BindPS(slot);
	}
}

Texture* Omega::Graphics::TextureManager::GetTexture(TextureId id)
{
	if (auto iter = mInventory.find(id);
		iter != mInventory.end())
	{
		return iter->second.get();
	}
	return nullptr;
}
