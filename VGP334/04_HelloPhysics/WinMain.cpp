#include "GameState.h"

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE,
	_In_ PSTR, _In_ int)
{
	Omega::App app;
	app.AddState<GameState>("GameState");	
	app.Run({"VGP334 - Hello Physics", 1280,720});
	return 0;
}