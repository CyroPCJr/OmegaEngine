#include "Precompiled.h"
#include "SeekBehaviour.h"
#include "Agent.h"

using namespace Omega::AI;
using namespace Omega::Math;

Vector2 SeekBehaviour::Calculate(Agent& agent)
{
	return Seek(agent, agent.destination);
}

Vector2 SeekBehaviour::Seek(Agent& agent, const Vector2& destination)
{
	Vector2 diseredVel = Normalize(destination - agent.position) * agent.maxSpeed;
	return diseredVel - agent.velocity;
}
