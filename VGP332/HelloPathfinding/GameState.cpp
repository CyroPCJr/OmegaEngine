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
	mTileMap.Render();
}

void GameState::Render()
{
	mTileMap.Render();
}

void GameState::DebugUI()
{
	SimpleDraw::Render(mCamera);
	mTileMap.DebugUI();
}