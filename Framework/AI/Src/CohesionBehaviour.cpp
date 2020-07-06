#include "Precompiled.h"
#include "CohesionBehaviour.h"
#include "Agent.h"

using namespace AI;
using namespace Omega::Math;

Vector2 CohesionBehaviour::Calculate(Agent& agent)
{
	Vector2 averagePosition = agent.position;
	for (auto& neighbor : agent.neighbors)
	{
		averagePosition += neighbor->position;
	}
	averagePosition /= (agent.neighbors.size() + 1.0f);
	// Seek formula
	//return (X::Math::Normalize(averagePosition - agent.position)*agent.maxSpeed) - agent.velocity;
	return averagePosition - agent.position;
}