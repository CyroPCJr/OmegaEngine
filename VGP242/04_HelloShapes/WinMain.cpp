#include <OmegaEngine/Inc/Omega.h>

#include "Shapes.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Omega::MainApp().AddState<HearShape>("HeartShape");
	Omega::MainApp().Run({"Hello Shapes Project", 1280,720});
	return 0;
}