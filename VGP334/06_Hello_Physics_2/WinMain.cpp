#include "GameState.h"

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
	Omega::AppConfig config{ "Physics 2.0" };
	Omega::App& app = Omega::MainApp();
	app.AddState<GameState>("GameState");
	app.Run(config);
	return 0;
}