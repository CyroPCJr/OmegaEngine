#include "Precompiled.h"
#include "AlignmentBehaviour.h"
#include "Agent.h"

using namespace AI;
using namespace Omega::Math;

Vector2 AlignmentBehaviour::Calculate(Agent& agent)
{
	Vector2 averageHeading = agent.heading;
	for (auto& neighbor : agent.neighbors)
	{
		averageHeading += neighbor->heading;
	}
	averageHeading /= (agent.neighbors.size() + 1.0f);
	return averageHeading - agent.heading;
}