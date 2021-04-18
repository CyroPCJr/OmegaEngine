#include "Precompiled.h"
#include "ArriveBehaviour.h"
#include "Agent.h"

using namespace AI;
using namespace Omega::Math;
using namespace Omega::Graphics;

Vector2 ArriveBehaviour::Calculate(Agent& agent)
{
	return Arrive(agent, agent.destination);
}

Vector2 AI::ArriveBehaviour::Arrive(AI::Agent& agent, Omega::Math::Vector2 destination)
{
	Vector2 desiredVelocity = destination - agent.position;
	const float distance = Magnitude(desiredVelocity);

	//if (distance > 0.0f)
	//{
	//	float speed = std::min(distance / (deceleration * decelerationTweaker), agent.maxSpeed);
	//	Vector2 desiredVelocity = desiredVelocity * speed/ distance;
	//	return desiredVelocity - agent.velocity;
	//}
	//return Vector2::Zero;
	if (distance < mSlowRadius)
	{
		// Inside the slowing area
		desiredVelocity = Normalize(desiredVelocity) * (distance / mSlowRadius);
	}
	else
	{
		// Outside the slowing area
		desiredVelocity = Normalize(desiredVelocity) * agent.maxSpeed;
	}
	return (desiredVelocity - agent.velocity) * agent.mass * (mSlowRadius / distance);
}

void ArriveBehaviour::ShowDebugDraw(const Agent& agent)
{
	SimpleDraw::AddScreenCircle({ agent.destination, mSlowRadius }, Colors::SlateGray);
}
