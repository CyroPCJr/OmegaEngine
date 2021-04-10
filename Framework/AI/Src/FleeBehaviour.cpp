#include "Precompiled.h"
#include "FleeBehaviour.h"
#include "Agent.h"

using namespace AI;
using namespace Omega::Math;

Vector2 FleeBehaviour::Calculate(Agent& agent)
{
	const float panicDistance = 10.0f * 10.0f;
	float distance = Magnitude(agent.position - agent.destination);

	if (distance == 0.0f || 
		distance > panicDistance)
	{
		return Vector2::Zero;
	}
	return Fleeing(agent, agent.destination);
}

Vector2 AI::FleeBehaviour::Fleeing(Agent& agent, const Vector2& destination)
{
	Vector2 diseredVel = Normalize(agent.position - destination) * agent.maxSpeed;
	return diseredVel - agent.velocity;
}
