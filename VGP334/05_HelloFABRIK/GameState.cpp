#include "GameState.h"

#include <ImGui/Inc/imgui.h>

using namespace Omega::Graphics;
using namespace Omega::Input;
using namespace Omega::Math;
using namespace Omega::Physics;

void GameState::Initialize()
{
	GraphicsSystem::Get()->get().SetClearColor(Colors::Black);

	mCameraService.Initialize();
	Camera& camera = mCameraService.GetActiveCamera();

	camera.SetNearPlane(0.1f);
	camera.SetFarPlane(300.0f);
	camera.SetPosition({ 0.0f, 1.0f, -5.0f });
	camera.SetLookAt({ 0.0f, 1.0f, 0.0f });

	constexpr int numBones = 5;
	constexpr float boneLength = 1.0f;
	mPoints.reserve(numBones + 1u);
	mPoints.emplace_back(Vector3::Zero);
	for (size_t i{ 1 }; i < mPoints.capacity(); ++i)
	{
		mPoints.emplace_back(mPoints.back() + Vector3{ 0.0f, boneLength, 0.0f });
	}
	mTarget = mPoints.back();
	mVecFrames.reserve(MAX_FRAME);
}

void GameState::Terminate()
{
	mCameraService.Terminate();
}

void GameState::Update(float deltaTime)
{
	const auto& inputSystem = InputSystem::Get()->get();
	
	Camera& camera = mCameraService.GetActiveCamera();
	
	const float kMoveSpeed = inputSystem.IsKeyDown(KeyCode::LSHIFT) ? 100.0f : 10.0f;
	const float movementSpeed = kMoveSpeed * deltaTime;

	// control camera
	if (inputSystem.IsKeyDown(KeyCode::W))
	{
		camera.Walk(movementSpeed);
	}
	if (inputSystem.IsKeyDown(KeyCode::S))
	{
		camera.Walk(-movementSpeed);
	}
	if (inputSystem.IsKeyDown(KeyCode::D))
	{
		camera.Strafe(movementSpeed);
	}
	if (inputSystem.IsKeyDown(KeyCode::A))
	{
		camera.Strafe(-movementSpeed);
	}

	if (inputSystem.IsMouseDown(MouseButton::RBUTTON))
	{
		constexpr float kTurnSpeed = 1.0f;

		camera.Yaw(static_cast<float>(inputSystem.GetMouseMoveX()) * kTurnSpeed * deltaTime);
		camera.Pitch(static_cast<float>(inputSystem.GetMouseMoveY()) * kTurnSpeed * deltaTime);
	}

	// control the target
	if (inputSystem.IsKeyDown(KeyCode::UP))
	{
		mTarget.y += movementSpeed;
	}
	else if (inputSystem.IsKeyDown(KeyCode::DOWN))
	{
		mTarget.y -= movementSpeed;
	}
	if (inputSystem.IsKeyDown(KeyCode::RIGHT))
	{
		mTarget.x += movementSpeed;
	}
	else if (inputSystem.IsKeyDown(KeyCode::LEFT))
	{
		mTarget.x -= movementSpeed;
	}

	AnimationUtil::RunFABRIK(mPoints, mTarget);
}

void GameState::Render()
{
	const size_t totalSize = mPoints.size();
	for (size_t i{ 0 }; i + 1u < totalSize; ++i)
	{
		const Vector3 points = mPoints.at(i + 1);
		SimpleDraw::AddLine(mPoints.at(i), points, Colors::Green);
		if (i + 1u != totalSize)
		{
			SimpleDraw::AddSphere(points, 0.1f, 4, 8, Colors::Cyan);
		}
	}
	SimpleDraw::AddAABB({ mTarget, { 0.2f, 0.2f, 0.2f } }, Colors::Red);

	SimpleDraw::AddGroundPlane(30.0f);
	SimpleDraw::AddTransform(Matrix4::Identity);
	const Camera& camera = mCameraService.GetActiveCamera();
	SimpleDraw::Render(camera);
}

void GameState::DebugUI()
{
	ImGui::Begin("Physics", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	DrawCounterFramesUI(true);
	ImGui::End();
}

void GameState::DrawCounterFramesUI(bool active)
{
	if (!active) return;

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	float fps = ImGui::GetIO().Framerate; //Get frames
	const size_t frameSize = mVecFrames.size();
	if (frameSize > MAX_FRAME) //Max seconds to show
	{
		for (size_t i = 1; i < frameSize; ++i)
		{
			mVecFrames.at(i - 1u) = mVecFrames.at(i);
		}
		mVecFrames.at(frameSize - 1) = fps;
	}
	else
	{
		mVecFrames.push_back(fps);
	}
	ImGui::PlotLines("", &mVecFrames.at(0), MAX_FRAME, 0, NULL, 0.0f, 300.0f, ImVec2(250, 30));
}