#include "Precompiled.h"
#include "PerceptionModule.h"
#include "Agent.h"

using namespace Omega::AI;
using namespace Omega::Core;

PerceptionModule::PerceptionModule(Agent & agent, ImportanceCalculator importanceCalculator)
	: mAgent(agent)
	, mCalculator(std::move(importanceCalculator))
{}

void PerceptionModule::Update(float deltaTime)
{
	for (auto&[name, sensor] : mSensors)
	{
		sensor->Update(mAgent, mMemory, deltaTime);
	}

	// Remove any records older than memory span
	for (auto iter = mMemory.begin(); iter != mMemory.end();)
	{
		if (iter->lastRecordedTime + mMemorySpan < TimeUtil::GetTime())
		{
			iter = mMemory.erase(iter);
		}
		else
		{
			iter++;
		}
	}

	// Calculator importance on new records
	for (auto& m : mMemory)
	{
		mCalculator(mAgent, m);
	}

	// Sort records by importance
	mMemory.sort([](const MemoryRecord& a, const MemoryRecord& b)
	{
		return a.importance > b.importance;
	});
}
