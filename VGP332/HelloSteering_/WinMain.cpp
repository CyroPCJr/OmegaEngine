#include "Carrier.h"
#include "Interceptor.h"
#include "TileMap.h"
#include "AIWorld.h"

#include <XEngine.h>

using namespace Steering;
using namespace AI;

constexpr int maxInterceptor = 3;

AI::AIWorld::Settings mSettings;

AI::AIWorld mAIWorld;

std::vector<std::unique_ptr<Carrier>> mCarrierList;
std::vector<std::unique_ptr<Interceptor>> mInterceptorList;

void GameInit()
{
	mSettings.partitionGridSize = 100.0f;
	mSettings.worldSize = { static_cast<float>(X::GetScreenWidth()), static_cast<float>(X::GetScreenHeight()) };
	mAIWorld.Initialize(mSettings);
	mAIWorld.AddObstacles({ { 300.0,300.0f }, 100.0f });
	mAIWorld.AddObstacles({ { 1000.0,200.0f }, 80.0f });
	mAIWorld.AddObstacles({ { 500.0, 100.0f }, 20.0f });

	auto carrier = mCarrierList.emplace_back(std::make_unique<Carrier>(mAIWorld)).get();
	carrier->Load();

	for (size_t i = 0; i < maxInterceptor; ++i)
	{
		auto interceptor = mInterceptorList.emplace_back(std::make_unique<Interceptor>(mAIWorld)).get();
		interceptor->Load();
		interceptor->position = { X::RandomFloat(0, mSettings.worldSize.x), X::RandomFloat(0, mSettings.worldSize.y) };
		interceptor->threat = carrier;
	}

}

void GameCleanup()
{
	for (const auto& carrier : mCarrierList)
	{
		carrier->Unload();
	}

	for (const auto& inter : mInterceptorList)
	{
		inter->Unload();
	}
}

bool GameLoop(float deltaTime)
{
	mAIWorld.Update();
	mAIWorld.DebugDraw();

	for (const auto& carrier : mCarrierList)
	{
		carrier->Update(deltaTime);
		carrier->Render();
	}

	for (const auto& inter : mInterceptorList)
	{
		inter->Update(deltaTime);
		inter->Render();
	}

	return X::IsKeyPressed(X::Keys::ESCAPE);
}

int WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	X::Start("xconfig.json");
	GameInit();
	X::Run(GameLoop);
	GameCleanup();
	X::Stop();
	return 0;
}

/*
HOMEWORK

Create different behaviours
Seek, Flee, Arrive and Wander(if is possible)

21/02/2020
HOMEWORK
Wander, hide and obstacle avoid


Notes in class 20/02/2020

Physics Engine
--------------------
1) World Representation
	- Proxy shapes (AABB, OBB, Sphere, Capule, etc)
	- Particles ( i.e. point mass)
	- Ca be hierarchical
	- can have constraints (e.g joints)
2) Simulation
	- For object motion
	- Applies physics formaulas (e.g kinematics)
3) COllision Detection
	- Math/Geometry
	- can be hierachical (e.g. spatial partitioning, compound shapes)
4) Collisiton Resolution
	- Physics formaulas
	- Preserves rules of physics (e.g Newton's Laws, Energy/Momentum conservation)

*/