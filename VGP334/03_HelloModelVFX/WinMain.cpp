#include "GameState.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ PSTR szCmdLine, _In_ int iCmdShow)
{
	Omega::MainApp().AddState<GameState>("GameState");	
	Omega::MainApp().Run({"VGP334 - Hello Model VFX", 1280,720});
	return 0;
}