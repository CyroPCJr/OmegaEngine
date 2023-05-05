#include "GameState.h"
#include <ImGui\Inc\imgui.h>

using namespace Omega;
using namespace Omega::AI;
using namespace Omega::Graphics;

using namespace HelloPerception;

void GameState::Initialize()
{
	InitializeWorld();
	mCarrier = std::make_unique<Carrier>(mAIWorld);
	mCarrier->Load();
}

void GameState::Terminate()
{

	// clean up
	mCarrier->Unload();
	mCarrier.reset();	
}
	 
void GameState::Update(float deltaTime)
{
	mAIWorld.Update();
	mCarrier->Update(deltaTime);
}

void GameState::Render()
{
	mCarrier->Render();
}

void GameState::DebugUI()
{
	mAIWorld.DebugDraw();
	SimpleDraw::Render(mCamera);
	// ImGui
	GeneralDebugUI();
}

void GameState::InitializeWorld()
{
	mSettings.partitionGridSize = 100.0f;
	mSettings.worldSize = { static_cast<float>(GraphicsSystem::Get()->GetBackBufferWidth()),
		static_cast<float>(GraphicsSystem::Get()->GetBackBufferHeight()) };
	mAIWorld.Initialize(mSettings);

	mAIWorld.AddObstacles({ { 300.0f,300.0f }, 100.0f });
	mAIWorld.AddObstacles({ { 1000.0f,200.0f }, 80.0f });
	mAIWorld.AddObstacles({ { 500.0f, 100.0f }, 20.0f });

}

void GameState::GeneralDebugUI()
{
	ImGui::Begin("Settings", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::BeginGroup();
	if (ImGui::CollapsingHeader("Debug"), ImGuiTreeNodeFlags_DefaultOpen)
	{
		if (static bool isDebugging = false;
			ImGui::Checkbox("Debug Options", &isDebugging), ImGuiTreeNodeFlags_DefaultOpen)
		{
			mCarrier->SetDebugDraw(isDebugging);
		}

	}
	ImGui::EndGroup();

	ImGui::BeginGroup();
	if (ImGui::CollapsingHeader("Carrier (Steering Behaviours)"), ImGuiTreeNodeFlags_DefaultOpen)
	{
		if (static bool seekDebug = false;
			ImGui::Checkbox("Seek", &seekDebug))
		{
			mCarrier->SwitchBehaviour(Carrier::Behaviours::Seek, seekDebug);
		}
		static bool arriveDebug = false;
		if (ImGui::Checkbox("Arrive", &arriveDebug))
		{
			mCarrier->SwitchBehaviour(Carrier::Behaviours::Arrive, arriveDebug);
		}

		static float radius = 0.0f;
		if (arriveDebug)
		{
			ImGui::SliderFloat("SlowRadius###radius", &radius, 0.0f, 250.0f);
			mCarrier->SetSlowRadius(radius);
		}

		if (static bool avoidDebug = false;
			ImGui::Checkbox("Obstacel Avoidance", &avoidDebug))
		{
			mCarrier->SwitchBehaviour(Carrier::Behaviours::ObstacleAvoidance, avoidDebug);
		}

	}
	ImGui::EndGroup();
	ImGui::End();
}
