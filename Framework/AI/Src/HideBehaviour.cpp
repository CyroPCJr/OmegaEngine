#include "Precompiled.h"
#include "HideBehaviour.h"
#include "Agent.h"
#include "AIWorld.h"

using namespace Omega::AI;
using namespace Omega::Math;
using namespace Omega::Graphics;

namespace
{
	inline Vector2 GetHidingPosition(const Vector2& obstaclePos, const float radius,
		const Vector2& targetPos)
	{
		const float distanceFromBoundary = 30.0f;
		const float distanceAway = radius + distanceFromBoundary;
		const auto toOrb = Normalize(obstaclePos - targetPos);
		return (toOrb * distanceAway) + obstaclePos;
	}
}

Vector2 HideBehaviour::Calculate(Agent& agent)
{
	if (!agent.threat)
	{
		return Vector2::Zero;
	}
	// Access the world throught the agent
	const auto& obstList = agent.world.GetObstacles();
	if (obstList.size() <= 0u)
	{
		return Vector2::Zero;
	}

	float minDistance = std::numeric_limits<float>::max();
	for (const auto& obstacle : obstList)
	{
		Vector2 hiddindSpot = GetHidingPosition(obstacle.center, obstacle.radius, agent.threat->position);
		float distance = DistanceSqr(hiddindSpot, agent.position);
		if (distance < minDistance)
		{
			minDistance = distance;
			mClosestObstacle = hiddindSpot;
		}
	}

	if (minDistance == std::numeric_limits<float>::max())
	{
		// Flee formula
		Vector2 diseredVel = Normalize(agent.position - agent.threat->destination) * agent.maxSpeed;
		return diseredVel - agent.velocity;
	}
	agent.destination = mClosestObstacle;

	return Arrive(agent, agent.destination);
}

void HideBehaviour::ShowDebugDraw(const Agent& agent)
{
	SimpleDraw::AddScreenLine(agent.position, mClosestObstacle, Colors::Blue);
	SimpleDraw::AddScreenLine(agent.position, agent.destination, Colors::Green);
}
