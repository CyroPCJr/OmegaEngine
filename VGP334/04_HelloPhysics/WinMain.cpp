#include "GameState.h"

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
	Omega::App app;
	app.AddState<GameState>("GameState");
	app.Run({ "VGP334 - Hello Physics" });
	return 0;
}