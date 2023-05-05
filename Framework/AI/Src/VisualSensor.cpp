#include "Precompiled.h"
#include "VisualSensor.h"

#include "MemoryRecord.h"
#include "Agent.h"
#include "AIWorld.h"

using namespace Omega::AI;
using namespace Omega::Core;

void VisualSensor::Update(Agent& agent, MemoryRecords& memory, float deltaTime)
{
	const auto neighbor = agent.world.GetNeighborhood({ agent.position, agent.radius }, agent.GetTypeId());
	for (const auto& neighbor : neighbor)
	{

		if (Math::Distance(neighbor->position, agent.position) > viewRange)
		{
			continue;
		}

		if (Math::Dot(Math::Normalize(neighbor->position - agent.position), agent.heading) < cosf(viewAngle))
		{
			continue;
		}

		if (!agent.world.HasLineOfSight(agent.position, neighbor->position))
		{
			continue;
		}

		MemoryRecord& record = FindOrCreate(memory, neighbor->GetTypeId());
		record.properties["lastSeenPosition"/*Any property to save specific*/] = neighbor->position; // Save vector2 for wher the entity was
		record.lastRecordedTime = TimeUtil::GetTime();
	}
}
