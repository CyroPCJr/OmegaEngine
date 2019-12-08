#pragma once


namespace Omega::Graphics
{
	class PixelShader
	{
	public:
		void Initialize();
		void Terminate();

		void Bind();
	private:
		ID3D11PixelShader* mPixelShader = nullptr;
	};
}