#include "GameState.h"

//reference to fixes warning C28251
//https://www.codeproject.com/Tips/5257987/How-to-Compile-Legacy-Win32-Programs-in-Visual-Stu
//
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ PSTR szCmdLine, _In_ int iCmdShow)
{
	Omega::MainApp().AddState<FSM::GameState>("GameState");
	Omega::MainApp().Run({ "VGP332 - Hello FSM", 1280,720 });
	return 0;
}