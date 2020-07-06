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

	auto mostThreatening = CheckObstacleAhead(ahead, ahead2, agent);
	Vector2 avoidance = Vector2::Zero;

	avoidance = ahead - mostThreatening.center;
	avoidance = Normalize(avoidance);
	avoidance *= agent.maxSpeed;
	//}
	//else {
	//	avoidance.scaleBy(0); // nullify the avoidance force
	//}
	return avoidance - agent.velocity;
}

Circle ObstacleAvoidance::CheckObstacleAhead(const Vector2& ahead, const Vector2& ahead2, Agent& agent)
{
	Circle obstacle;
	// Access the worl throught the agent
	auto world = &agent.world;
	auto obstList = world->GetObstacles();

	for (const auto& obs : obstList)
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

bool ObstacleAvoidance::lineIntersectsCircle(const Vector2 & ahead, const Vector2 & ahead2, Circle obstacle)
{
	// distance between center obstacle and look ahead in agent
	const float distanceAhead =  Magnitude(obstacle.center - ahead);
	const float distanceAhead2 = Magnitude(obstacle.center - ahead2);

	return (distanceAhead <= obstacle.radius) || (distanceAhead2 <= obstacle.radius);
}
