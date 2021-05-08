#include "GameState.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ PSTR szCmdLine, _In_ int iCmdShow)
{
	Omega::App app;
	app.AddState<GameState>("GameState");	
	app.Run({"VGP334 - Hello Physics", 1280,720});
	return 0;
}