#include "Precompiled.h"
#include "Window.h"

using namespace Omega;
using namespace Omega::Core;

namespace
{
	static LRESULT CALLBACK WndProc(HWND handle, UINT message, WPARAM wparam, LPARAM lParam) noexcept
	{
		if (message == WM_DESTROY)
		{
			PostQuitMessage(0);
			return 0;
		}
		return DefWindowProcA(handle, message, wparam, lParam);
	}
}

void Window::Initialize(HINSTANCE instance, LPCSTR appName, uint32_t width, uint32_t height) noexcept
{
	mInstance = instance;
	mAppName = appName;
	// 3 step to create window
	// 1) Register a "Window Class' with a Win32
	// 2) Create Window instance of that class type
	// 3) Retrive/dispatch/handle messages for this window
	// Register class
	WNDCLASSEXA classInfo{};
	classInfo.cbSize = sizeof(WNDCLASSEXA);
	classInfo.style = CS_HREDRAW | CS_VREDRAW;
	classInfo.lpfnWndProc = WndProc;
	classInfo.hInstance = instance;
	classInfo.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	classInfo.hCursor = LoadCursor(nullptr, IDC_ARROW);
	classInfo.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
	classInfo.lpszClassName = appName;
	classInfo.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
	RegisterClassExA(&classInfo);


	//  Compute the correct window dimension
	RECT rc = { 0l,0l, {width}, {height} };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	const int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	const int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	const int winWidth = (rc.right - rc.left);
	const int winHeight = (rc.bottom - rc.top);
	const int posX = (screenWidth - winWidth) >> 1;
	const int posY = (screenHeight - winHeight) >> 1;

	// Create Window
	mWindow = CreateWindowA(appName, appName, WS_OVERLAPPEDWINDOW, posX, posY, winWidth, winHeight, nullptr, nullptr, instance, nullptr);

	ShowWindow(mWindow, SW_SHOWNORMAL);
	SetCursorPos(screenHeight >> 1, screenHeight >> 1);
	mActive = (mWindow != nullptr);
}

void Window::Terminate()
{
	DestroyWindow(mWindow);
	UnregisterClassA(std::string(mAppName).c_str(), mInstance);

	mWindow = nullptr;
	mInstance = nullptr;
}

void Core::Window::ProcessMessage() noexcept
{
	MSG msg{};
	while (PeekMessageA(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessageA(&msg);
		if (WM_QUIT == msg.message)
		{
			mActive = false;
		}
	}
}