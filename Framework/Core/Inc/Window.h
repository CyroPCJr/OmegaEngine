#pragma once

namespace Omega::Core
{

	class Window
	{
	public:
		Window() = default;

		void Initialize(HINSTANCE instance, LPCSTR appName, uint32_t width, uint32_t height);
		void Terminate();
		void ProcessMessage();

		HWND GetWindow() const { return mWindow; }
		bool IsActive() const { return mActive; }
	private:
		HINSTANCE mInstance{ nullptr };
		HWND mWindow { nullptr};
		std::string mAppName;

		bool mActive{false};
	};
}