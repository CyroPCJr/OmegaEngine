#pragma once

namespace Omega::Core
{
	class Window final
	{
	public:
		Window() noexcept = default;
		// copy ctor
		Window(const Window&) = delete;
		// copy assignment
		Window& operator=(const Window&) = delete;
		// move ctor
		Window(const Window&&) = delete;
		// move assignment
		Window& operator=(Window&&) = delete;

		void Initialize(HINSTANCE instance, LPCSTR appName, uint32_t width, uint32_t height);
		void Terminate() noexcept;
		void ProcessMessage() noexcept;

		constexpr HWND GetWindow() const noexcept { return mWindow; }
		constexpr bool IsActive() const { return mActive; }
	private:
		std::string mAppName;
		HINSTANCE mInstance = nullptr;
		HWND mWindow = nullptr;
		bool mActive = false;
		char mPadding[3]{};
	};
}