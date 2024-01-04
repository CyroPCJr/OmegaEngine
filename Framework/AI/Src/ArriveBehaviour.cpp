#include "Precompiled.h"
#include "ArriveBehaviour.h"
#include "Agent.h"

using namespace Omega::AI;
using namespace Omega::Math;
using namespace Omega::Graphics;

Vector2 ArriveBehaviour::Calculate(Agent& agent)
{
	return Arrive(agent, agent.destination);
}

Vector2 ArriveBehaviour::Arrive(const Agent& agent, const Omega::Math::Vector2& destination) const
{
	Vector2 desiredVelocity = destination - agent.position;
	const float distance = Magnitude(desiredVelocity);
	desiredVelocity = Normalize(desiredVelocity);
	if (distance < mSlowRadius)
	{
		// Inside the slowing area
		desiredVelocity *= (distance / mSlowRadius);
	}
	else
	{
		// Outside the slowing area
		desiredVelocity *= agent.maxSpeed;
	}
	return (desiredVelocity - agent.velocity) * (mSlowRadius / distance);
}

void ArriveBehaviour::ShowDebugDraw(const Agent& agent)
{
	SimpleDraw::AddScreenCircle({ agent.destination, mSlowRadius }, Colors::SlateGray);
}
