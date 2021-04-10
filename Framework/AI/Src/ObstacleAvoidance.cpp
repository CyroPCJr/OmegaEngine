#include "Precompiled.h"
#include "ObstacleAvoidance.h"
#include "Agent.h"
#include "AIWorld.h"

using namespace AI;
using namespace Omega::Math;

Vector2 ObstacleAvoidance::Calculate(Agent & agent)
{
	Vector2 ahead = agent.position +agent.velocity*agent.maxSpeed;
	Vector2 ahead2 = ahead * 0.5f;

	const auto mostThreatening = CheckObstacleAhead(ahead, ahead2, agent);
	Vector2 avoidance = Vector2::Zero;

	avoidance = ahead - mostThreatening.center;
	avoidance = Normalize(avoidance);
	avoidance *= agent.maxSpeed;
	
	return avoidance - agent.velocity;
}

Circle ObstacleAvoidance::CheckObstacleAhead(const Vector2& ahead, const Vector2& ahead2, const Agent& agent) const
{
	Circle obstacle{};
	// Access the worl throught the agent
	auto world = &agent.world;
	for (auto& obs : world->GetObstacles())
	{
		bool isCollide = lineIntersectsCircle(ahead, ahead2, obs);
		if (isCollide ||
			Magnitude(agent.position - obs.center) < Magnitude(agent.position - obstacle.center))
		{
			obstacle = obs;
		}
	}
	return obstacle;
}

bool ObstacleAvoidance::lineIntersectsCircle(const Vector2 & ahead, const Vector2 & ahead2, const Circle& obstacle) const
{
	// distance between center obstacle and look ahead in agent
	const float distanceAhead =  Magnitude(obstacle.center - ahead);
	const float distanceAhead2 = Magnitude(obstacle.center - ahead2);

	return (distanceAhead <= obstacle.radius) || (distanceAhead2 <= obstacle.radius);
}
