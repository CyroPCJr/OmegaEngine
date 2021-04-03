#include "GameState.h"
#include "Cat.h"

#include <ImGui\Inc\imgui.h>

using namespace FSM;
using namespace Omega::Graphics;

void GameState::Initialize()
{
	GraphicsSystem::Get()->SetClearColor(Colors::Black);
	mCat.Load();
}

void GameState::Terminate()
{
	mCat.UnLoad();
}

void GameState::Update(float deltaTime)
{
	mCat.Update(deltaTime);
}

void GameState::Render()
{


}

void GameState::DebugUI()
{

}