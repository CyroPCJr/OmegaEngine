#include <OmegaEngine/Inc/Omega.h>

#include "TestState.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Omega::MainApp().AddState<BlueState>("BlueState");
	Omega::MainApp().AddState<RedState>("RedState");
	Omega::MainApp().Run({"Hello DireectX Project", 1280,720});
	return 0;
}