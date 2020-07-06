#include "Precompiled.h"
#include "FleeBehaviour.h"
#include "Agent.h"

using namespace AI;
using namespace Omega::Math;

//TODO: need to test this function again.
Vector2 FleeBehaviour::Calculate(Agent& agent)
{
	const float panicDistance = 100.0f*100.0f;
	Vector2 diff = agent.position - agent.destination;
	float distance = Magnitude(diff);

	if (distance == 0.0f || distance > panicDistance)
	{
		return Vector2::Zero;
	}

	Vector2 diseredVel = Normalize(agent.position - agent.destination) * agent.maxSpeed;
	return diseredVel - agent.velocity;
}
