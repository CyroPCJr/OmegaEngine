#include <OmegaEngine/Inc/Omega.h>

#include "GameState.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Omega::MainApp().AddState<GameState>("GameState");	
	Omega::MainApp().Run({"Hello DireectX Project", 1280,720});
	return 0;
}