#include <OmegaEngine/Inc/Omega.h>

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Omega::AppConfig appConfig;
	appConfig.appName = "Hello Window";
	appConfig.windowWidth = 1280;
	appConfig.windowHeight = 720;

	Omega::MainApp().Run(appConfig);  
	return 0;
}