#include "Precompiled.h"
#include "PursuitBehaviour.h"
#include "Agent.h"

using namespace AI;
using namespace Omega::Math;

Vector2 PursuitBehaviour::Calculate(AI::Agent& agent)
{
	Vector2 toEvader = agent.threat->position - agent.position;

	const float differenceDistance = Magnitude(toEvader);
	float distanceAhead = differenceDistance / agent.maxSpeed;

	agent.destination = agent.threat->position + agent.threat->velocity * distanceAhead;

	// Seek formula
	auto desiredVelocity = Normalize(agent.destination - agent.position) * agent.maxSpeed;
	return desiredVelocity - agent.velocity;
}