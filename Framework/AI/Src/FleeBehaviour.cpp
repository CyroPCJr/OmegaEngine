#include "Precompiled.h"
#include "FleeBehaviour.h"
#include "Agent.h"

using namespace Omega::AI;
using namespace Omega::Math;

Vector2 FleeBehaviour::Calculate(Agent& agent)
{
	const float panicDistance = 10.0f * 10.0f;
	if (float distance = Magnitude(agent.position - agent.destination); 
		distance == 0.0f || distance > panicDistance)
	{
		return Vector2::Zero;
	}
	return Fleeing(agent, agent.destination);
}

Vector2 FleeBehaviour::Fleeing(Agent& agent, const Vector2& destination)
{
	Vector2 diseredVel = Normalize(agent.position - destination) * agent.maxSpeed;
	return diseredVel - agent.velocity;
}
