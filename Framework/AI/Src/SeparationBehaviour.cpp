#include "Precompiled.h"
#include "SeparationBehaviour.h"	
#include "Agent.h"

using namespace AI;
using namespace Omega::Math;

//TODO: ask for Peter about this behaviour
//TODO: double check in this behaviour
Vector2 SeparationBehaviour::Calculate(Agent& agent)
{
	Vector2 totalForce;
	for (const auto& neighbor: agent.neighbors)
	{
		const auto neighborToAgent = agent.position - neighbor->position;
		const auto distanceToAgent = Magnitude(neighborToAgent);
		if (distanceToAgent <= std::numeric_limits<float>::epsilon())
		{
			totalForce += agent.heading * agent.maxSpeed;
		}
		else
		{
			const auto separationDirection = neighborToAgent / distanceToAgent;
			const auto separationForce = agent.maxSpeed * (1.0f - Min(distanceToAgent, 100.0f) / 100.0f);
			totalForce += separationDirection * separationDirection;
		}
	}
	return totalForce;
}
