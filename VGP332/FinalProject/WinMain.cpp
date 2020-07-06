#include "MainGame.h"
#include <XEngine.h>

FinalProject::MainGame mainGame;

void GameInit()
{
	mainGame.Initialize();
}

void GameCleanup()
{
	mainGame.Terminate();
}

bool GameLoop(float deltaTime)
{
	mainGame.Update(deltaTime);
	return X::IsKeyPressed(X::Keys::ESCAPE);
}

int WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	X::Start("xconfig.json");
	GameInit();
	X::Run(GameLoop);
	GameCleanup();
	X::Stop();
	return 0;
}