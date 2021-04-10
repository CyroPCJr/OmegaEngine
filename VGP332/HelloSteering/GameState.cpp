#include "GameState.h"

#include <ImGui\Inc\imgui.h>

using namespace Steering;
using namespace Omega;
using namespace Omega::Math;
using namespace Omega::Graphics;
using namespace AI;

void GameState::Initialize()
{
	SettingInit();

	for (size_t i = 0; i < maxInterceptor; ++i)
	{
		auto interceptor = mInterceptorList.emplace_back(std::make_unique<Interceptor>(mAIWorld)).get();
		interceptor->Load();
		interceptor->position = { Random::RandomFloat(0, mSettings.worldSize.x), Random::RandomFloat(0, mSettings.worldSize.y) };
		//	interceptor->threat = mCarrier;
	}
}

void GameState::Terminate()
{
	for (const auto& interceptor : mInterceptorList)
	{
		interceptor->Unload();
	}
}

void GameState::Update(float deltaTime)
{
	mAIWorld.Update();
	for (const auto& interceptor : mInterceptorList)
	{
		interceptor->Update(deltaTime);
	}
}

void GameState::Render()
{
	for (const auto& interceptor : mInterceptorList)
	{
		interceptor->Render();
	}
}

void GameState::DebugUI()
{
	mAIWorld.DebugDraw();
	SimpleDraw::Render(mCamera);
	GeneralDebugUI();

}

void GameState::SettingInit()
{
	mSettings.partitionGridSize = 100.0f;
	mSettings.worldSize = { static_cast<float>(GraphicsSystem::Get()->GetBackBufferWidth()),
		static_cast<float>(GraphicsSystem::Get()->GetBackBufferHeight()) };
	mAIWorld.Initialize(mSettings);
	mAIWorld.AddObstacles({ { 300.0,300.0f }, 100.0f });
	mAIWorld.AddObstacles({ { 1000.0,200.0f }, 80.0f });
	mAIWorld.AddObstacles({ { 500.0, 100.0f }, 20.0f });

	mAIWorld.AddWalls({ { 1000.0f, 50.f }, { 150.0f,100.0f } });
}

void GameState::GeneralDebugUI()
{
	ImGui::Begin("Settings", nullptr, ImGuiWindowFlags_NoResize);
	ImGui::BeginGroup();
	if (ImGui::CollapsingHeader("Debug"), ImGuiTreeNodeFlags_DefaultOpen)
	{
		static bool isDebugging = false;
		if (ImGui::Checkbox("Debug Options", &isDebugging), ImGuiTreeNodeFlags_DefaultOpen)
		{
			for (auto& enemy : mInterceptorList)
			{
				enemy->isDebugShowDraw = isDebugging;
			}

			//mCarrier->isDebugShowDraw = isDebugging;
		}
	}
	ImGui::EndGroup();
	ImGui::End();
}
