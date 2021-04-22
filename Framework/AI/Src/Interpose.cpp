#include "Precompiled.h"
#include "Interpose.h"
#include "Agent.h"

using namespace Omega::AI;
using namespace Omega::Math;

//TODO: Still need more test
Vector2 Interpose::Calculate(Agent& agent)
{
	Agent* agentA = nullptr;
	Agent* agentB = nullptr;
	for (size_t i = 0, neighborSize = agent.neighbors.size();
		(neighborSize > 2) && i < neighborSize; ++i)
	{
		agentA = agent.neighbors[0];
		agentB = agent.neighbors[1];
	}
	if (agentA && agentB)
	{
		Vector2 midPoint = (agentA->position + agentB->position) * 0.5f;
		float timeToReachMidPoint = Distance(agent.position, midPoint) / agent.maxSpeed;

		const Vector2 agentAPos = agentA->position + agentA->velocity * timeToReachMidPoint;
		const Vector2 agentBPos = agentB->position + agentB->velocity * timeToReachMidPoint;

		midPoint = (agentAPos + agentBPos) * 0.5f;

		return Arrive(agent, midPoint);
	}
	else
	{
		return Vector2::Zero;
	}

}
