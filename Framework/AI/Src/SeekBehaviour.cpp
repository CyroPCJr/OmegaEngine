#include "Precompiled.h"
#include "SeekBehaviour.h"
#include "Agent.h"

using namespace AI;
using namespace Omega::Math;

Vector2 SeekBehaviour::Calculate(Agent& agent)
{
	Vector2 diseredVel = Normalize(agent.destination - agent.position) * agent.maxSpeed;
	return diseredVel - agent.velocity;
}
