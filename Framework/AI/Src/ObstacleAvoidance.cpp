#include "Precompiled.h"
#include "ObstacleAvoidance.h"
#include "Agent.h"
#include "AIWorld.h"

using namespace Omega::AI;
using namespace Omega::Math;
using namespace Omega::Graphics;

Vector2 ObstacleAvoidance::Calculate(Agent& agent)
{
	AIWorld::Obstacles worldObstacles = agent.world.GetObstacles();
	mProjectionBoxLength = boxExtention + (Magnitude(agent.velocity) / agent.maxSpeed) + boxExtention;

	Matrix3 agentWorldToLocal = Inverse(agent.LocalToWorld());
	Circle* closestObstacle = nullptr;
	Vector2 localPositionObstacle = Vector2::Zero;
	float closestDistanceObstacles = std::numeric_limits<float>::max();

	for (auto& obstacle : worldObstacles)
	{
		// if the distance of the obstacle is greater then the box projection loop again to next obstacle
		if (Distance(obstacle.center, agent.position) - obstacle.radius > mProjectionBoxLength)
		{
			continue;
		}

		//calculate this obstacle's position in local space
		if (auto localPosition = TransformCoord(obstacle.center, agentWorldToLocal); 
			localPosition.y >= 0)
		{
			float expandeRadius = obstacle.radius + agent.radius;
			if (Abs(localPosition.x) < expandeRadius)
			{
				const float sqrExpandeRadius = sqrt((expandeRadius * expandeRadius) - (localPosition.x * localPosition.x));
				float intersectionY = localPosition.y - sqrExpandeRadius;
				if (intersectionY <= 0.0f)
				{
					intersectionY = localPosition.y + sqrExpandeRadius;
				}

				if (intersectionY < closestDistanceObstacles)
				{
					closestDistanceObstacles = intersectionY;
					closestObstacle = &obstacle;
					localPositionObstacle = localPosition;
				}
			}
		}
	}

	if (closestObstacle)
	{
		Matrix3 agentLocalWorld = agent.LocalToWorld();
		float multiplier = sideForceScale + (mProjectionBoxLength - localPositionObstacle.y) / mProjectionBoxLength;
		Vector2 steeringforce;
		steeringforce.x = (closestObstacle->radius - localPositionObstacle.x) * multiplier;
		steeringforce.y = (closestObstacle->radius - localPositionObstacle.y) * brakingWeight;

		return TransformNormal(steeringforce, agentLocalWorld);
	}
	return Vector2::Zero;
}

void ObstacleAvoidance::ShowDebugDraw(const Agent& agent)
{
	Matrix3 localToWorld = agent.LocalToWorld();
	const float agentLocalRadius = agent.radius * 10.0f;

	Vector2 debugBoxTopLeftWorld = TransformCoord({ agentLocalRadius ,0.0f }, localToWorld);
	Vector2 debugBoxTopRightWorld = TransformCoord({ agentLocalRadius, mProjectionBoxLength }, localToWorld);
	Vector2 debugBoxBottonLeftWorld = TransformCoord({ -agentLocalRadius,0.0f }, localToWorld);
	Vector2 debugBoxBottonRightWorld = TransformCoord({ -agentLocalRadius,  mProjectionBoxLength }, localToWorld);

	auto whiteBox = Colors::White;

	SimpleDraw::AddScreenLine(debugBoxTopLeftWorld, debugBoxTopRightWorld, whiteBox);
	SimpleDraw::AddScreenLine(debugBoxBottonLeftWorld, debugBoxBottonRightWorld, whiteBox);
	SimpleDraw::AddScreenLine(debugBoxTopLeftWorld, debugBoxBottonLeftWorld, whiteBox);
	SimpleDraw::AddScreenLine(debugBoxTopRightWorld, debugBoxBottonRightWorld, whiteBox);
}