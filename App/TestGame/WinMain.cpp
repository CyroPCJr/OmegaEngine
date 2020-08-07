#include "GameState.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Omega::MainApp().AddState<GameState>("TestGame");	
	Omega::MainApp().Run({"Test Game", 1280,720});
	return 0;
}