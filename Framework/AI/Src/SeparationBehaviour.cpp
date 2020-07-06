#include "Precompiled.h"
#include "SeparationBehaviour.h"	
#include "Agent.h"

using namespace AI;
using namespace Omega::Math;

//TODO: ask for Peter about this behaviour
Vector2 SeparationBehaviour::Calculate(Agent& agent)
{
	Vector2 totalForce;
	for (auto& neighbor: agent.neighbors)
	{
		auto neighborToAgent = agent.position - neighbor->position;
		auto distanceToAgent = Magnitude(neighborToAgent);
		if (distanceToAgent <= 0.0f)
		{
			totalForce += agent.heading * agent.maxSpeed;
		}
		else
		{
			auto separationDirection = neighborToAgent / distanceToAgent;
			auto separationForce = agent.maxSpeed * (1.0f - Min(distanceToAgent, 100.0f) / 100.0f);
			totalForce += separationDirection * separationDirection;
		}
	}
	return totalForce;
}
