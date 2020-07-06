#include "Precompiled.h"
#include "ArriveBehaviour.h"
#include "Agent.h"

using namespace AI;
using namespace Omega::Math;

Vector2 ArriveBehaviour::Calculate(Agent& agent)
{
	Vector2 toTarget = agent.destination - agent.position;
	float distance = Magnitude(toTarget);
	const float slowInRadius = 1000.0f;
	if (distance < slowInRadius)
	{
		toTarget = Normalize(toTarget) * agent.maxSpeed * (distance / slowInRadius);
	}
	else
	{
		toTarget = Normalize(toTarget) * agent.maxSpeed;
	}
	return toTarget - agent.velocity;
	/*if (distance > 0.1f)
	{
		float decel = Deceleration::slow;
		const float decelTweaker = 0.3f;
		float speed = distance / (decel * decelTweaker);
		speed = std::min(speed, agent.maxSpeed);
		X::Math::Vector2 DesiredVelocity = toTarget * speed / distance;
		return DesiredVelocity - agent.velocity;
	}
	return X::Math::Vector2::Zero();*/
}
