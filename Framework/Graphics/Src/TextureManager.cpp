#include "Precompiled.h"
#include "TextureManager.h"

using namespace Omega::Graphics;

TextureManager::~TextureManager()
{
	Clear();
	OMEGAASSERT(mInventory.empty(), "[TextureManager] Clear() must be called to clean up.");
}

TextureId TextureManager::Load(const std::filesystem::path& fileName, bool isUseRootPath)
{
	std::filesystem::path fullName = mRootPath;
	fullName = (isUseRootPath) ? fullName / fileName : fileName;

	std::hash<std::string> hasher;
	const TextureId hash = hasher(fullName.u8string());
	auto [iter, successful] = mInventory.insert({ hash , nullptr });
	if (successful)
	{
		iter->second = std::move(std::make_unique<Texture>(fullName));
	}

	return hash;
}

void TextureManager::Clear() noexcept
{
	for (auto& [id, texture] : mInventory)
	{
		if (texture)
		{
			texture.reset();
		}
	}
	mInventory.clear();
}

void TextureManager::BindVS(TextureId id, uint32_t slot)
{
	if (const Texture* texture = GetTexture(id); texture)
	{
		texture->BindVS(slot);
	}
}

void TextureManager::BindPS(TextureId id, uint32_t slot)
{
	if (const Texture* texture = GetTexture(id); texture)
	{
		texture->BindPS(slot);
	}
}

Texture* TextureManager::GetTexture(TextureId id)
{
	if (auto iter = mInventory.find(id);
		iter != mInventory.end())
	{
		return iter->second.get();
	}
	return nullptr;
}
