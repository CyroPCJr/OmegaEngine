#include "Precompiled.h"
#include "CohesionBehaviour.h"
#include "Agent.h"

using namespace AI;
using namespace Omega::Math;

Vector2 CohesionBehaviour::Calculate(Agent& agent)
{
	//TODO: need to rewritte, fixing
	Vector2 averagePosition = agent.position;
	for (const auto& neighbor : agent.neighbors)
	{
		averagePosition += neighbor->position;
	}

	if (const float size = static_cast<float>(agent.neighbors.size());
		size > 0.0f)
	{
		auto target = averagePosition / size;
		return (target == agent.position) ? 
			(agent.heading * agent.maxSpeed) : 
			Seek(agent, target);
	}
	else
	{
		return Vector2::Zero;
	}
}