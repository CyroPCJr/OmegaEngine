#include "Precompiled.h"
#include "SteeringModule.h"

using namespace AI;
using namespace Omega::Math;

SteeringModule::SteeringModule(Agent& agent)
	: mAgent(agent)
{}

Vector2 SteeringModule::Calculate()
{
	Vector2 total;
	for (auto& [name, behavior] : mBehaviors)
	{
		if (behavior->IsActive())
		{
			total += behavior->Calculate(mAgent);
		}
	}
	return total;
}

void SteeringModule::ShowDebugDraw() const
{
	for (auto& [name, behavior] : mBehaviors)
	{
		if (behavior->IsActive())
		{
			behavior->ShowDebugDraw(mAgent);
		}
	}
}

