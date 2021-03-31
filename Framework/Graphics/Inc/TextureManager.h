#pragma once
#include "TextureTypes.h"
#include "Texture.h"

namespace Omega::Graphics
{
	class TextureManager
	{
	public:
		static void StaticInitialize(const std::filesystem::path& root);
		static void StaticTerminate();
		static TextureManager* Get();
	public:
		TextureManager() = default;
		~TextureManager();

		TextureManager(const TextureManager&) = delete;
		TextureManager& operator=(const TextureManager&) = delete;

		inline void SetRootPath(const std::filesystem::path& path) { mRootPath = path; }

		TextureId Load(const std::filesystem::path& fileName, bool isUseRootPath = true);
		void Clear();

		void BindVS(TextureId id, uint32_t slot = 0);
		void BindPS(TextureId id, uint32_t slot = 0);

		Texture* GetTexture(TextureId id);

	private:
		std::filesystem::path mRootPath;
		std::unordered_map<TextureId, std::unique_ptr<Texture>> mInventory;
	};

}