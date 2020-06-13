#include "GameState.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Omega::MainApp().AddState<GameState>("GameState");	
	Omega::MainApp().Run({"VGP334 - Hello FABRIK", 1280,720});
	return 0;
}