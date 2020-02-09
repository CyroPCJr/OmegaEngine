#pragma once


namespace Omega::Graphics
{
	class PixelShader
	{
	public:
		void Initialize(const std::filesystem::path& filePath, const char* shaderName = "PS");
		void Terminate();

		void Bind() const;
	private:
		ID3D11PixelShader* mPixelShader = nullptr;
	};
}