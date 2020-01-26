#pragma once

namespace Omega::Graphics {

	class Texture
	{
	public:
		void Initialize(const std::filesystem::path& fileName);
		void Terminate();

		void BindPS(uint32_t slot = 0) const;
		void BindVS(uint32_t slot = 0) const;

	private:
		ID3D11ShaderResourceView* mShaderResourceView = nullptr;
	};

} // namespace Omega::Graphics