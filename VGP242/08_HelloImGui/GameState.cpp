#include "GameState.h"
#include <ImGui/Inc/imgui.h>

using namespace Omega::Graphics;
using namespace Omega::Input;
using namespace Omega::Math;

void GameState::Initialize()
{
	mCamera.SetPosition({ 0.0f, 0.0f, -5.0f });
	mCamera.SetDirection({ 0.0f, 0.0f, 1.0f });

	SimpleDraw::StaticInitialize();
}

void GameState::Terminate()
{

}

void GameState::Update(float deltaTime)
{
	const float kMoveSpeed = 100.05f;
	const float kTurnSpeed = 0.5f;

	auto inputSystem = InputSystem::Get();
	if (inputSystem->IsKeyDown(KeyCode::W))
	{
		mCamera.Walk(kMoveSpeed * deltaTime);
	}

	if (inputSystem->IsKeyDown(KeyCode::S))
	{
		mCamera.Walk(-kMoveSpeed * deltaTime);
	}

	mCamera.Yaw(inputSystem->GetMouseMoveX() * kTurnSpeed * deltaTime);
	mCamera.Pitch(inputSystem->GetMouseMoveY() * kTurnSpeed * deltaTime);

	SimpleDraw::AddLine({ 0.0f, 0.0f, 0.0f }, { 10.0f, 10.0f, 10.0f }, Colors::Blue);
	//mRotation += deltaTime;	
}

void GameState::Render()
{
	SimpleDraw::Render(mCamera);
}

void GameState::DebugUI()
{
	ImGui::ShowDemoWindow();
}