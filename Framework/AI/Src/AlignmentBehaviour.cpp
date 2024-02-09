#include "Precompiled.h"
#include "AlignmentBehaviour.h"
#include "Agent.h"

using namespace Omega::AI;
using namespace Omega::Math;
using namespace Omega::Graphics;

Vector2 AlignmentBehaviour::Calculate(Agent& agent)
{
	Vector2 averageHeading = agent.heading;
	for (const auto& neighbor : agent.neighbors)
	{
		averageHeading += neighbor->heading;
	}
	averageHeading /= agent.neighbors.size() + 1.0f;
	averageHeading -= agent.heading;
	return averageHeading * 50.0f;
}

void AlignmentBehaviour::ShowDebugDraw(const Agent& agent)
{
	Vector2 feelerLength = agent.position + 50.0f * agent.heading;
	SimpleDraw::AddScreenLine(agent.position, feelerLength, Colors::DarkOrange);
}
