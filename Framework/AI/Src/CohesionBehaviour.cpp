#include "Precompiled.h"
#include "CohesionBehaviour.h"
#include "Agent.h"

using namespace AI;
using namespace Omega::Math;

Vector2 CohesionBehaviour::Calculate(Agent& agent)
{
	Vector2 averagePosition = agent.position;
	for (const auto& neighbor : agent.neighbors)
	{
		averagePosition += neighbor->position;
	}

	if (const float size = static_cast<float>(agent.neighbors.size());
		size > 0.0f)
	{
		Vector2 centerOfMass = averagePosition / (size + 1.0f);
		return Seek(agent, centerOfMass);
	}
	else
	{
		return Vector2::Zero;
	}
}