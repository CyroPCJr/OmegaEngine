#pragma once

namespace Omega::Core
{

	/*
	A - ASCII
	W - WIDE
	WCHAR store 16bit
	*/

	class WindowMessageHandler
	{
	public:
		// return function pointer ()
		using Callback = LRESULT(CALLBACK*)(HWND, UINT, WPARAM, LPARAM);
		void Hook(HWND window, Callback cb) noexcept;
		void Unhook() noexcept;

		LRESULT ForwardMessage(HWND window, UINT message, WPARAM wParam, LPARAM lParam) const;

	private:
		HWND mWindow = nullptr;
		Callback mPreviousCallback = nullptr;
	};

}