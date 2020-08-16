#include "GameState.h"

#include <ImGui/Inc/imgui.h>

using namespace Omega::Graphics;
using namespace Omega::Input;
using namespace Omega::Math;
using namespace Omega::Physics;

void GameState::Initialize()
{
	GraphicsSystem::Get()->SetClearColor(Colors::Black);

	mCamera.SetNearPlane(0.1f);
	mCamera.SetFarPlane(300.0f);
	mCamera.SetPosition({ 0.0f, 10.0f, -30.0f });
	mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });
	mWorld.Initialize(100);
	mWorld.Create("../../Assets/Templates/tallBox.json", "Cyro");
	mWorld.Create("../../Assets/Templates/longBox.json", "Cyro");
	mWorld.Create("../../Assets/Templates/fatBox.json", "Cyro");
}

void GameState::Terminate()
{
	mWorld.Terminate();
}

void GameState::Update(float deltaTime)
{
	auto inputSystem = InputSystem::Get();

	const float kMoveSpeed = inputSystem->IsKeyDown(KeyCode::LSHIFT) ? 100.0f : 10.0f;
	const float kTurnSpeed = 1.0f;

	if (inputSystem->IsKeyDown(KeyCode::W))
	{
		mCamera.Walk(kMoveSpeed * deltaTime);
	}

	if (inputSystem->IsKeyDown(KeyCode::S))
	{
		mCamera.Walk(-kMoveSpeed * deltaTime);
	}
	if (inputSystem->IsKeyDown(KeyCode::D))
	{
		mCamera.Strafe(kMoveSpeed * deltaTime);
	}
	if (inputSystem->IsKeyDown(KeyCode::A))
	{
		mCamera.Strafe(-kMoveSpeed * deltaTime);
	}
	if (inputSystem->IsMouseDown(MouseButton::RBUTTON))
	{
		mCamera.Yaw(inputSystem->GetMouseMoveX() * kTurnSpeed * deltaTime);
		mCamera.Pitch(inputSystem->GetMouseMoveY() * kTurnSpeed * deltaTime);
	}

	mWorld.Update(deltaTime);
}

void GameState::Render()
{
	mWorld.Render();

	SimpleDraw::AddGroundPlane(30.0f);
	SimpleDraw::Render(mCamera);
}

void GameState::DebugUI()
{
	mWorld.DebugUI();
}