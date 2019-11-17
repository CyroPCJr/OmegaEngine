#include <OmegaEngine/Inc/Omega.h>

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Omega::MainApp().AddState<Omega::AppState>("DummyState");

	Omega::MainApp().Run({ "Hello Window", 1280, 720 });
	return 0;
}