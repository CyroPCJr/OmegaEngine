//#include "TileMap.h"
//#include <XEngine.h>
//
//TileMap tileMap;
//
//void GameInit()
//{
//	tileMap.Load();
//}
//
//void GameCleanup()
//{
//	tileMap.UnLoad();
//}
//
//bool GameLoop(float deltaTime)
//{
//	tileMap.Update(deltaTime);
//	tileMap.Render();
//	return X::IsKeyPressed(X::Keys::ESCAPE);
//}
//
//int WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
//{
//	X::Start("xconfig.json");
//	GameInit();
//	X::Run(GameLoop);
//	GameCleanup();
//	X::Stop();
//	return 0;
//}

#include "GameState.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Omega::MainApp().AddState<GameState>("GameState");
	Omega::MainApp().Run({ "VGP332 - Hello Pathfinding", 1280,720 });
	return 0;
}