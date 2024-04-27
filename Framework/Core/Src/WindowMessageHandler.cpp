#include "Precompiled.h"
#include "WindowMessageHandler.h"

#include "DebugUtil.h"

using namespace Omega::Core;

void WindowMessageHandler::Hook(HWND window, Callback cb) noexcept
{
	mWindow = window;
	mPreviousCallback = (Callback)GetWindowLongPtrA(window, GWLP_WNDPROC);
	SetWindowLongPtrA(window, GWLP_WNDPROC, (LONG_PTR)cb);
}

void WindowMessageHandler::Unhook() noexcept
{
	SetWindowLongPtrA(mWindow, GWLP_WNDPROC, (LONG_PTR)mPreviousCallback);
	mWindow = nullptr;
}

LRESULT WindowMessageHandler::ForwardMessage(HWND window, UINT message, WPARAM wParam, LPARAM lParam) const
{
	OMEGAASSERT(mPreviousCallback, "[WindowMessageHandler] No callback is hooked.");
	return CallWindowProcA((WNDPROC)mPreviousCallback, window, message, wParam, lParam);
}