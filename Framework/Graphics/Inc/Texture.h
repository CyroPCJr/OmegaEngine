#pragma once

namespace Omega::Graphics
{

	class Texture
	{
	public:

		Texture() = default;
		~Texture();

		Texture(const Texture&) = delete;
		Texture& operator=(const Texture&) = delete;

		void Initialize(const std::filesystem::path& fileName);
		void Terminate();

		void BindPS(uint32_t slot = 0) const;
		void BindVS(uint32_t slot = 0) const;

		uint32_t GetWidth() const { return mWidth; }
		uint32_t GetHeight() const { return mHeight; }

	private:
		friend class SpriteRenderer;

		ID3D11ShaderResourceView* mShaderResourceView = nullptr;

		uint32_t mWidth = 0;
		uint32_t mHeight = 0;
	};

}