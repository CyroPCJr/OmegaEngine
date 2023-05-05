#include "Precompiled.h"
#include "SeekBehaviour.h"
#include "Agent.h"

using namespace Omega::AI;
using namespace Omega::Math;
using namespace Omega::Graphics;

Vector2 SeekBehaviour::Calculate(Agent& agent)
{
	return Seek(agent, agent.destination);
}

void SeekBehaviour::ShowDebugDraw(const Agent& agent)
{
	SimpleDraw::AddScreenLine(agent.position, agent.destination, Colors::Green);
	SimpleDraw::AddScreenCircle({ agent.destination, 10.0f }, Colors::Blue);
}

Vector2 SeekBehaviour::Seek(Agent& agent, const Vector2& destination)
{
	Vector2 diseredVel = Normalize(destination - agent.position) * agent.maxSpeed;
	return diseredVel - agent.velocity;
}


