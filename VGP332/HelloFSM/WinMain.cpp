
#include "Cat.h"
#include <XEngine.h>

FSM::Cat cat;

void GameInit()
{
	cat.Load();
}

void GameCleanup()
{
	cat.UnLoad();
}

bool GameLoop(float deltaTime)
{
	cat.Update(deltaTime);
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