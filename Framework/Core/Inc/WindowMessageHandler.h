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
		void Hook(HWND window, Callback cb);
		void Unhook();

		LRESULT ForwardMessage(HWND window, UINT message, WPARAM wParam, LPARAM lParam);

	private:
		HWND mWindow = nullptr;
		Callback mPreviousCallback = nullptr;
	};

}