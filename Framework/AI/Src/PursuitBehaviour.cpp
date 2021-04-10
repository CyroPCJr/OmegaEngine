#include "Precompiled.h"
#include "PursuitBehaviour.h"
#include "Agent.h"

using namespace AI;
using namespace Omega::Math;

Vector2 PursuitBehaviour::Calculate(AI::Agent& agent)
{
	const Vector2 toEvader = agent.threat->position - agent.position;
	const float differenceDistance = Magnitude(toEvader);
	const float distanceAhead = differenceDistance / agent.maxSpeed;
	const Vector2 destination = agent.threat->position + agent.threat->velocity * distanceAhead;
	return Seek(agent, destination);
}