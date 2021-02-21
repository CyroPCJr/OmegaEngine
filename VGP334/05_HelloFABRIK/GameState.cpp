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
	mCamera.SetPosition({ 0.0f, 1.0f, -5.0f });
	mCamera.SetLookAt({ 0.0f, 1.0f, 0.0f });

	const int numBones = 5;
	const float boneLength = 1.0f;
	mPoints.reserve(numBones + 1);
	mPoints.push_back(Vector3::Zero);
	for (size_t i = 1; i < mPoints.capacity(); ++i)
	{
		mPoints.push_back(mPoints.back() + Vector3{ 0.0f, boneLength, 0.0f });
	}
	mTarget = mPoints.back();
	mVecFrames.reserve(mMaxFrameSize);
}

void GameState::Terminate()
{
}

void GameState::Update(float deltaTime)
{
	auto inputSystem = InputSystem::Get();

	const float kMoveSpeed = inputSystem->IsKeyDown(KeyCode::LSHIFT) ? 100.0f : 10.0f;
	const float kTurnSpeed = 1.0f;

	// control camera
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

	// control the target
	if (inputSystem->IsKeyDown(KeyCode::UP))
	{
		mTarget.y += kMoveSpeed * deltaTime;
	}
	else if (inputSystem->IsKeyDown(KeyCode::DOWN))
	{
		mTarget.y -= kMoveSpeed * deltaTime;
	}
	if (inputSystem->IsKeyDown(KeyCode::RIGHT))
	{
		mTarget.x += kMoveSpeed * deltaTime;
	}
	else if (inputSystem->IsKeyDown(KeyCode::LEFT))
	{
		mTarget.x -= kMoveSpeed * deltaTime;
	}

	AnimationUtil::RunFABRIK(mPoints, mTarget);
}

void GameState::Render()
{
	for (size_t i = 0; i + 1 < mPoints.size(); ++i)
	{
		SimpleDraw::AddLine(mPoints[i], mPoints[i + 1], Colors::Green);
		if (i + 1 != mPoints.size())
		{
			SimpleDraw::AddSphere(mPoints[i + 1], 0.1f, 4, 8, Colors::Cyan);
		}
	}
	SimpleDraw::AddAABB({ mTarget, { 0.2f, 0.2f, 0.2f } }, Colors::Red);

	SimpleDraw::AddGroundPlane(30.0f);
	SimpleDraw::AddTransform(Matrix4::Identity);
	SimpleDraw::Render(mCamera);
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
	if (frameSize > mMaxFrameSize) //Max seconds to show
	{
		for (size_t i = 1; i < frameSize; ++i)
		{
			mVecFrames[i - 1] = mVecFrames[i];
		}
		mVecFrames[frameSize - 1] = fps;
	}
	else
	{
		mVecFrames.push_back(fps);
	}
	ImGui::PlotLines("", &mVecFrames[0], frameSize, 0, NULL, 0.0f, 300.0f, ImVec2(250, 30));
}
