#include "GameState.h"

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
	Omega::AppConfig config{ "TestGame" };
	Omega::App& app = Omega::MainApp();
	app.AddState<GameState>(config.appName);
	app.Run(config);
	return 0;
}