#include "Precompiled.h"
#include "ArriveBehaviour.h"
#include "Agent.h"

using namespace AI;
using namespace Omega::Math;

Vector2 ArriveBehaviour::Calculate(Agent& agent)
{
	return Arrive(agent, agent.destination);
}

Vector2 AI::ArriveBehaviour::Arrive(AI::Agent& agent, Omega::Math::Vector2 destination)
{
	Vector2 toTarget = agent.destination - agent.position;
	const float distance = Magnitude(toTarget);
	if (distance > 0.0f)
	{
		float speed = std::min(distance / (deceleration * decelerationTweaker), agent.maxSpeed);
		Vector2 desiredVelocity = toTarget * (speed / distance);
		return desiredVelocity - agent.velocity;
	}
	return Vector2::Zero;
}