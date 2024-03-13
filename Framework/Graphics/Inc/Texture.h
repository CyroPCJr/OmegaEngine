#pragma once

namespace Omega::Graphics
{

	class Texture final
	{
	public:
		
		explicit Texture(const std::filesystem::path& fileName);
		~Texture() noexcept = default;

		Texture(const Texture&) = delete;
		Texture& operator=(const Texture&) = delete;

		Texture(Texture&&) = default;
		Texture& operator=(Texture&&) = default;

		void BindPS(uint32_t slot = 0u) const;
		void BindVS(uint32_t slot = 0u) const;

		constexpr uint32_t GetWidth() const noexcept { return mWidth; }
		constexpr uint32_t GetHeight() const noexcept { return mHeight; }
		ID3D11ShaderResourceView* GetShaderResourceView() const noexcept { return mShaderResourceView.Get(); }

	private:
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mShaderResourceView;
		uint32_t mWidth{ 0u };
		uint32_t mHeight{ 0u };
	};

}