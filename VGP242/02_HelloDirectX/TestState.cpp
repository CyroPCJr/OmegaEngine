#include "TestState.h"

using namespace Omega::Graphics;
using namespace Omega::Input;

void RedState::Initialize()
{
	GraphicsSystem::Get()->SetClearColor(Colors::Red);
}

void RedState::Update(float deltaTime)
{
	if (InputSystem::Get()->IsKeyPressed(KeyCode::SPACE))
	{
		Omega::MainApp().ChangeState("BlueState");
	}
}

void BlueState::Initialize()
{
	GraphicsSystem::Get()->SetClearColor(Colors::Blue);
}

void BlueState::Update(float deltaTime)
{
	if (InputSystem::Get()->IsKeyPressed(KeyCode::SPACE))
	{
		Omega::MainApp().ChangeState("RedState");
	}
}