#include "GameState.h"

#include <ImGui\Inc\imgui.h>

using namespace Steering;
using namespace Omega;
using namespace Omega::Math;
using namespace Omega::Graphics;
using namespace Omega::AI;

void GameState::Initialize()
{
	SettingInit();

	mCarrier = std::make_unique<Carrier>(mAIWorld);
	mCarrier->Load();

	for (size_t i = 0; i < maxInterceptor; ++i)
	{
		auto interceptor = mInterceptorList.emplace_back(std::make_unique<Interceptor>(mAIWorld)).get();
		interceptor->Load();
		interceptor->position = { Random::RandomFloat(0, mSettings.worldSize.x), Random::RandomFloat(0, mSettings.worldSize.y) };
		interceptor->threat = mCarrier.get();
	}

}

void GameState::Terminate()
{
	for (const auto& interceptor : mInterceptorList)
	{
		interceptor->Unload();
	}

	mCarrier->Unload();
	mCarrier.reset();
}

void GameState::Update(float deltaTime)
{
	mAIWorld.Update();
	for (const auto& interceptor : mInterceptorList)
	{
		interceptor->Update(deltaTime);
	}

	mCarrier->Update(deltaTime);
}

void GameState::Render()
{
	for (const auto& interceptor : mInterceptorList)
	{
		interceptor->Render();
	}
	mCarrier->Render();
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
	/*mAIWorld.AddObstacles({ { 300.0f,300.0f }, 100.0f });
	mAIWorld.AddObstacles({ { 1000.0f,200.0f }, 80.0f });
	mAIWorld.AddObstacles({ { 500.0f, 100.0f }, 20.0f });

	mAIWorld.AddWalls({ { 1000.0f, 50.f }, { 150.0f,100.0f } });*/

	std::vector<Vector2> paths;
	paths.push_back({ 300.0f, 500.0f });
	paths.push_back({ paths.back().y, 100.0f });
	paths.push_back({ paths.back().y, 50.0f });
	paths.push_back({ paths.back().y, 150.0f });
	mAIWorld.AddPaths(paths);
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
			for (auto& enemy : mInterceptorList)
			{
				enemy->isDebugShowDraw = isDebugging;
			}

			mCarrier->isDebugShowDraw = isDebugging;
		}

	}

	if (ImGui::CollapsingHeader("Interceptor (Group Behaviours)"))
	{
		if (static bool alignmentDebug = false;
			ImGui::Checkbox("Alignment", &alignmentDebug))
		{
			for (const auto& inter : mInterceptorList)
			{
				inter->SwitchBehaviour(Interceptor::Behaviours::Alignment, alignmentDebug);
			}
		}

		if (static bool cohesionDebug = false;
			ImGui::Checkbox("Cohesion", &cohesionDebug))
		{
			for (const auto& inter : mInterceptorList)
			{
				inter->SwitchBehaviour(Interceptor::Behaviours::Cohesion, cohesionDebug);
			}
		}

		if (static bool separationDebug = false;
			ImGui::Checkbox("Separation", &separationDebug))
		{
			for (const auto& inter : mInterceptorList)
			{
				inter->SwitchBehaviour(Interceptor::Behaviours::Separation, separationDebug);
			}
		}
	}

	if (ImGui::CollapsingHeader("Interceptor (Steering Behaviours)"))
	{
		if (static bool evadeDebug = false;
			ImGui::Checkbox("Evade", &evadeDebug))
		{
			for (const auto& inter : mInterceptorList)
			{
				inter->SwitchBehaviour(Interceptor::Behaviours::Evade, evadeDebug);
			}
		}

		if (static bool fleeDebug = false;
			ImGui::Checkbox("Flee", &fleeDebug))
		{
			for (const auto& inter : mInterceptorList)
			{
				inter->SwitchBehaviour(Interceptor::Behaviours::Flee, fleeDebug);
			}
		}

		if (static bool hideDebug = false;
			ImGui::Checkbox("Hide", &hideDebug))
		{
			for (const auto& inter : mInterceptorList)
			{
				inter->SwitchBehaviour(Interceptor::Behaviours::Hide, hideDebug);
			}
		}

		if (static bool avoidanceDebug = false;
			ImGui::Checkbox("Obstacle Avoidance", &avoidanceDebug))
		{
			for (const auto& inter : mInterceptorList)
			{
				inter->SwitchBehaviour(Interceptor::Behaviours::ObstacleAvoidance, avoidanceDebug);
			}
		}

		if (static bool pursuitDebug = false;
			ImGui::Checkbox("Pursuit", &pursuitDebug))
		{
			for (const auto& inter : mInterceptorList)
			{
				inter->SwitchBehaviour(Interceptor::Behaviours::Pursuit, pursuitDebug);
			}
		}

		if (static bool wanderingDebug = false;
			ImGui::Checkbox("Wandering", &wanderingDebug))
		{
			for (const auto& inter : mInterceptorList)
			{
				inter->SwitchBehaviour(Interceptor::Behaviours::Wandering, wanderingDebug);
			}
		}

		if (static bool interposeDebug = false;
			ImGui::Checkbox("Interpose", &interposeDebug))
		{
			for (const auto& inter : mInterceptorList)
			{
				inter->SwitchBehaviour(Interceptor::Behaviours::Interpose, interposeDebug);
			}
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

		static float slowRadius = 0.0f;
		if (arriveDebug)
		{
			ImGui::SliderFloat("SlowRadius###radius", &slowRadius, 0.0f, 250.0f);
			mCarrier->SetSlowRadius(slowRadius);
		}

		if (static bool avoidDebug = false;
			ImGui::Checkbox("Obstacel Avoidance", &avoidDebug))
		{
			mCarrier->SwitchBehaviour(Carrier::Behaviours::ObstacleAvoidance, avoidDebug);
		}

		if (static bool wallAvoidanceDebug = false;
			ImGui::Checkbox("Wall Avoidance", &wallAvoidanceDebug))
		{
			mCarrier->SwitchBehaviour(Carrier::Behaviours::WallAvoidance, wallAvoidanceDebug);
		}

		if (static bool pathFollowingDebug = false;
			ImGui::Checkbox("Path Following", &pathFollowingDebug))
		{
			mCarrier->SwitchBehaviour(Carrier::Behaviours::PathFollowing, pathFollowingDebug);
		}

	}
	ImGui::EndGroup();
	ImGui::End();

}
