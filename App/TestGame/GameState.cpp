#include "GameState.h"

#include <ImGui/Inc/imgui.h>

using namespace Omega;
using namespace Omega::Graphics;
using namespace Omega::Input;
using namespace Omega::Math;
using namespace Omega::Physics;

void GameState::Initialize()
{
	GraphicsSystem::Get()->SetClearColor(Colors::Black);

	mCameraService = mWorld.AddService<CameraService>();
	mWorld.Initialize(100);

	auto& camera = mCameraService->GetActiveCamera();
	camera.SetNearPlane(0.1f);
	camera.SetFarPlane(300.0f);
	camera.SetPosition({ 0.0f, 10.0f, -30.0f });
	camera.SetLookAt({ 0.0f, 0.0f, 0.0f });

	/*mWorld.Create("../../Assets/Templates/tallBox.json", "Cyro");
	mWorld.Create("../../Assets/Templates/longBox.json", "Cyro");
	mWorld.Create("../../Assets/Templates/fatBox.json", "Cyro");*/
	mWorld.Create({ "../../Assets/Templates/tallBox.json",
		"../../Assets/Templates/longBox.json",
		"../../Assets/Templates/fatBox.json" }, "Cyro");
		//mWorld.Create("../../Assets/Templates/test.json", "Test");
}

void GameState::Terminate()
{
	mWorld.Terminate();
}

void GameState::Update(float deltaTime)
{
	const auto inputSystem = InputSystem::Get();

	const float kMoveSpeed = inputSystem->IsKeyDown(KeyCode::LSHIFT) ? 100.0f : 10.0f;
	constexpr float kTurnSpeed = 1.0f;
	const float moveDelta = kMoveSpeed * deltaTime;

	auto& camera = mCameraService->GetActiveCamera();

	if (inputSystem->IsKeyDown(KeyCode::W))
	{
		camera.Walk(moveDelta);
	}

	if (inputSystem->IsKeyDown(KeyCode::S))
	{
		camera.Walk(-moveDelta);
	}
	if (inputSystem->IsKeyDown(KeyCode::D))
	{
		camera.Strafe(moveDelta);
	}
	if (inputSystem->IsKeyDown(KeyCode::A))
	{
		camera.Strafe(-moveDelta);
	}
	if (inputSystem->IsMouseDown(MouseButton::RBUTTON))
	{
		const float mouseXDelta = static_cast<float>(inputSystem->GetMouseMoveX()) * moveDelta;
		const float mouseYDelta = static_cast<float>(inputSystem->GetMouseMoveY()) * moveDelta;
		camera.Yaw(mouseXDelta);
		camera.Pitch(mouseYDelta);
	}

	mWorld.Update(deltaTime);
}

void GameState::Render()
{
	mWorld.Render();

	SimpleDraw::AddGroundPlane(30.0f);
	SimpleDraw::Render(mCameraService->GetActiveCamera());
}

void GameState::DebugUI()
{
	mWorld.DebugUI();
}