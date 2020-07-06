#include "Precompiled.h"
#include "HideBehaviour.h"
#include "Agent.h"
#include "AIWorld.h"

using namespace AI;
using namespace Omega::Math;
using namespace Omega::Graphics;

namespace
{
	inline Vector2 GetHidingPosition(const Vector2& obstaclePos,  const float radius, const Vector2& targetPos)
	{
		const float distanceFromBoundary = 30.0f;
		float distanceAway = radius + distanceFromBoundary;
		auto toOrb = Normalize(obstaclePos - targetPos);
		return (toOrb * distanceAway) + obstaclePos;
	}
}

Vector2 HideBehaviour::Calculate(Agent & agent)
{
	// Access the worl throught the agent
	auto world = &agent.world;
	auto obstList = world->GetObstacles();

	if (obstList.size() <= 0)
	{
		return Vector2::Zero;
	}

	float minDistance = std::numeric_limits<float>::infinity();
	Circle mClosestObstacle;
	for (const auto& obstacle : obstList)
	{
		Vector2 hiddindSpot = GetHidingPosition(obstacle.center, obstacle.radius, agent.position);
		SimpleDraw::AddScreenLine(agent.position, hiddindSpot, Colors::Blue);
		float distance = Magnitude(hiddindSpot - agent.position);
		if (distance < minDistance)
		{
			minDistance = distance;
			mClosestObstacle.center = hiddindSpot + obstacle.radius;
		}
	}

	if (minDistance == std::numeric_limits<float>::infinity())
	{
		// Flee formula
		Vector2 diseredVel = Normalize(agent.position - agent.threat->destination) * agent.maxSpeed;
		return diseredVel - agent.velocity;
	}
	agent.destination = mClosestObstacle.center;
	SimpleDraw::AddScreenLine(agent.position, agent.destination, Colors::Green);
	// Seek formula
	Vector2 diseredVel = Normalize(agent.destination - agent.position) * agent.maxSpeed;
	return diseredVel - agent.velocity;
}