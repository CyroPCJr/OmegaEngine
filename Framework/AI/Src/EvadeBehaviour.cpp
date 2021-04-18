#include "Precompiled.h"
#include "EvadeBehaviour.h"
#include "Agent.h"

using namespace AI;
using namespace Omega::Math;
using namespace Omega::Graphics;

Vector2 EvadeBehaviour::Calculate(Agent & agent)
{
	if (!agent.threat)
	{
		return Vector2::Zero;
	}

	const Vector2 toPursuer = agent.threat->position - agent.position;
	const float lookAheadTime = Magnitude(toPursuer) / (agent.maxSpeed + Magnitude(agent.threat->velocity));

	return Fleeing(agent, agent.threat->position + agent.threat->velocity * lookAheadTime);
}

void EvadeBehaviour::ShowDebugDraw(const Agent& agent)
{
	SimpleDraw::AddScreenCircle(agent.position, 3.0f, Colors::Red);
	SimpleDraw::AddScreenCircle(agent.threat->position, 3.0f, Colors::Blue);
	SimpleDraw::AddScreenLine(agent.position, agent.threat->position, Colors::Green);
}