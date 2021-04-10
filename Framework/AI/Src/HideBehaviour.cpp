#include "Precompiled.h"
#include "HideBehaviour.h"
#include "Agent.h"
#include "AIWorld.h"

using namespace AI;
using namespace Omega::Math;
using namespace Omega::Graphics;

Vector2 HideBehaviour::Calculate(Agent& agent)
{
	// Access the worl throught the agent
	auto world = &agent.world;
	auto& obstList = world->GetObstacles();

	if (obstList.size() <= 0)
	{
		return Vector2::Zero;
	}

	float minDistance = std::numeric_limits<float>::infinity();
	Circle mClosestObstacle;
	for (const auto& obstacle : obstList)
	{
		mHidingSpot = GetHidingPosition(obstacle.center, obstacle.radius, agent.position);
		float distance = Magnitude(mHidingSpot - agent.position);
		if (distance < minDistance)
		{
			minDistance = distance;
			mClosestObstacle.center = mHidingSpot + obstacle.radius;
		}
	}

	if (minDistance == std::numeric_limits<float>::infinity())
	{
		// Flee formula
		Vector2 diseredVel = Normalize(agent.position - agent.threat->destination) * agent.maxSpeed;
		return diseredVel - agent.velocity;
	}
	agent.destination = mClosestObstacle.center;

	// Seek formula
	Vector2 diseredVel = Normalize(agent.destination - agent.position) * agent.maxSpeed;
	return diseredVel - agent.velocity;
}

void AI::HideBehaviour::ShowDebugDraw(const Agent& agent)
{
	SimpleDraw::AddScreenLine(agent.position, mHidingSpot, Colors::Blue);
	SimpleDraw::AddScreenLine(agent.position, agent.destination, Colors::Green);
}

Vector2 HideBehaviour::GetHidingPosition(const Vector2& obstaclePos,
	const float radius, const Vector2& targetPos)
{
	const float distanceFromBoundary = 30.0f;
	float distanceAway = radius + distanceFromBoundary;
	auto toOrb = Normalize(obstaclePos - targetPos);
	return (toOrb * distanceAway) + obstaclePos;
}
