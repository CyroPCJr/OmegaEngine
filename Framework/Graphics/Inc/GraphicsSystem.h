#pragma once

#include "Colors.h"

namespace Omega::Graphics {

	class Omega::Core::FpsHelper;

	class GraphicsSystem final
	{
	public:
		static void StaticInitialize(HWND window, bool fullscreen);
		static void StaticTerminate();
		static std::optional<std::reference_wrapper<GraphicsSystem>> Get();

	public:
		GraphicsSystem() = default;
		~GraphicsSystem();

		GraphicsSystem(const GraphicsSystem&) = delete;
		GraphicsSystem& operator=(const GraphicsSystem&) = delete;

		GraphicsSystem(GraphicsSystem&&) = delete;
		GraphicsSystem& operator=(GraphicsSystem&&) = delete;

		void Initialize(HWND window, bool fullscreen);
		void Terminate();

		void BeginRender(Omega::Core::FpsHelper& funcBeginFrame);
		void EndRender(Omega::Core::FpsHelper& funcEndFrame) const;

		void ToggleFullscreen();
		void Resize(uint32_t width, uint32_t height);

		void ResetRenderTarget();
		void ResetViewport();

		void SetClearColor(const Color& clearColor) noexcept { mClearColor = clearColor; }
		void SetVSync(bool vSync) noexcept { mVSync = vSync ? 1u : 0u; }

		uint32_t GetBackBufferWidth() const noexcept;
		uint32_t GetBackBufferHeight() const noexcept;

	private:
		static LRESULT CALLBACK GraphicsSystemMessageHandler(HWND window, UINT message, WPARAM wParam, LPARAM lParam);

		friend ID3D11Device* GetDevice();
		friend ID3D11DeviceContext* GetContext();

		void SetupRenderTargetView();

		// memory device pointer
		ID3D11Device* mD3DDevice = nullptr;
		ID3D11DeviceContext* mImmediateContext = nullptr;

		// Interface DirectX Graphics Infrastructure
		IDXGISwapChain* mSwapChain = nullptr;
		ID3D11RenderTargetView* mRenderTargetView = nullptr;

		ID3D11Texture2D* mDepthStencilBuffer = nullptr;
		ID3D11DepthStencilView* mDepthStencilView = nullptr;

		DXGI_SWAP_CHAIN_DESC mSwapChainDesc{};
		D3D11_VIEWPORT mViewport{};

		Color mClearColor{ Colors::White };
		UINT mVSync{ 1u };
	};

}