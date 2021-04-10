#include "GameState.h"

using namespace PathFinding;
using namespace Omega::Graphics;

void GameState::Initialize()
{
	mTileMap.Load();
}

void GameState::Terminate()
{
	mTileMap.UnLoad();
}

void GameState::Update(float deltaTime)
{
	mTileMap.Update(deltaTime);
}

void GameState::Render()
{
	mTileMap.Render();
}

void GameState::DebugUI()
{
	//TODO: Why the simple draw render works here instead Gamestate::reder ?
	SimpleDraw::Render(mCamera);
	mTileMap.DebugUI();
}