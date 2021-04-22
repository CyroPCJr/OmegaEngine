#include "Precompiled.h"
#include "SteeringModule.h"

using namespace Omega::AI;
using namespace Omega::Math;

SteeringModule::SteeringModule(Agent& agent)
	: mAgent(agent)
{}

Vector2 SteeringModule::Calculate()
{
	Vector2 total;
	for (const auto& [name, behavior] : mBehaviors)
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
	for (const auto& [name, behavior] : mBehaviors)
	{
		if (behavior->IsActive())
		{
			behavior->ShowDebugDraw(mAgent);
		}
	}
}

