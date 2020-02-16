#pragma once

namespace Omega::Graphics
{

	class RenderTarget
	{
	public:
		enum class Format
		{
			RGBA_U8,
			RGBA_F16,
			RGBA_U32,
			R_F16,
			R_S32
		};

		RenderTarget() = default;
		~RenderTarget();

		RenderTarget(const RenderTarget&) = delete;
		RenderTarget& operator=(const RenderTarget&) = delete;

		void Initialize(uint32_t width, uint32_t height, Format fomat);
		void Terminate();

		void BeginRender();
		void EndRender();

		void BindPS(uint32_t slot);
		void UnBindPS(uint32_t slot);

	private:
		ID3D11ShaderResourceView* mShaderResourceView = nullptr;
		ID3D11RenderTargetView* mRenderTargetView = nullptr;
		ID3D11DepthStencilView* mDepthStencilView = nullptr;
		D3D11_VIEWPORT mViewPort;
		D3D11_MAPPED_SUBRESOURCE mSubResource;
	};
}