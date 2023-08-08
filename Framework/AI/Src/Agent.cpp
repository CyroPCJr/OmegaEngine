#include "Precompiled.h"
#include "Agent.h"

using namespace Omega::AI;

Agent::Agent(AIWorld & world, uint32_t typeId) noexcept
	: Entity(world, typeId)
{}
