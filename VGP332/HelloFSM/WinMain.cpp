#include "GameState.h"
#include <OmegaEngine\Inc\Omega.h>

using namespace FSM; // Finite State Machine

//reference to fixes warning C28251
//https://www.codeproject.com/Tips/5257987/How-to-Compile-Legacy-Win32-Programs-in-Visual-Stu
//
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ PSTR szCmdLine, _In_ int iCmdShow)
{
	Omega::MainApp().AddState<GameState>("GameState");
	Omega::MainApp().Run({ "VGP332 - Hello FSM", 1280,720 });
	return 0;
}

