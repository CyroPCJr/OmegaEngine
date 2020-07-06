#include "Precompiled.h"
#include "EvadeBehaviour.h"
#include "Agent.h"

using namespace AI;
using namespace Omega::Math;


Vector2 EvadeBehaviour::Calculate(Agent & agent)
{
	Vector2 toEvader = agent.threat->position - agent.position;

	const float differenceDistance = Magnitude(toEvader);
	float distanceAhead = differenceDistance / agent.maxSpeed;

	agent.destination = agent.threat->position + agent.threat->velocity * distanceAhead;

	// Flee formula
	Vector2 diseredVel = Normalize(agent.position - agent.destination) * agent.maxSpeed;
	return diseredVel - agent.velocity;
}
