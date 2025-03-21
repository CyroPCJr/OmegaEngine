#include "Precompiled.h"
#include "SeparationBehaviour.h"	
#include "Agent.h"

using namespace Omega::AI;
using namespace Omega::Math;

Vector2 SeparationBehaviour::Calculate(Agent& agent)
{
	Vector2 totalForce;
	for (const auto& neighbor: agent.neighbors)
	{
		const auto neighborToAgent = agent.position - neighbor->position;
		if (const auto distanceToAgent = Magnitude(neighborToAgent); 
			distanceToAgent <= std::numeric_limits<float>::epsilon())
		{
			totalForce += agent.heading * agent.maxSpeed;
		}
		else
		{
			const auto separationDirection = neighborToAgent / distanceToAgent;
			const auto separationForce = agent.maxSpeed * (1.0f - Min(distanceToAgent, 100.0f) / 100.0f);
			totalForce += separationDirection * separationForce;
		}
	}
	return totalForce;
}
