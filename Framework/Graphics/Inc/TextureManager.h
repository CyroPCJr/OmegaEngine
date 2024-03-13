#pragma once
#include "TextureTypes.h"
#include "Texture.h"

namespace Omega::Graphics
{
	class TextureManager final
	{
	public:
		explicit TextureManager(const std::filesystem::path& pathRoot)
			: mRootPath{ pathRoot } {}

		~TextureManager();

		TextureManager(const TextureManager&) = delete;
		TextureManager& operator=(const TextureManager&) = delete;

		TextureManager(TextureManager&&) = default;
		TextureManager& operator=(TextureManager&&) = default;

		TextureId Load(const std::filesystem::path& fileName, bool isUseRootPath = true);
		void Clear() noexcept;

		void BindVS(TextureId id, uint32_t slot = 0u);
		void BindPS(TextureId id, uint32_t slot = 0u);

		Texture* GetTexture(TextureId id);

	private:
		std::unordered_map<TextureId, std::unique_ptr<Texture>> mInventory;
		std::filesystem::path mRootPath;
	};

}