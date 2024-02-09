#include "Precompiled.h"
#include "FleeBehaviour.h"
#include "Agent.h"

using namespace Omega::AI;
using namespace Omega::Math;
using namespace Omega::Graphics;

Vector2 FleeBehaviour::Calculate(Agent& agent)
{	
	if (const float distance = DistanceSqr(agent.position, agent.destination); distance > mPanicDistance)
	{
		return Vector2::Zero;
	}
	return Fleeing(agent, agent.destination);
}

void FleeBehaviour::ShowDebugDraw(const Agent& agent)
{
	SimpleDraw::AddScreenCircle({ agent.position, mPanicDistance }, Colors::BlueViolet);
	SimpleDraw::AddScreenLine(agent.position, agent.destination, Colors::Green);
}

Vector2 FleeBehaviour::Fleeing(Agent& agent, const Vector2& destination)
{
	Vector2 diseredVel = Normalize(agent.position - destination) * agent.maxSpeed;
	return diseredVel - agent.velocity;
}
