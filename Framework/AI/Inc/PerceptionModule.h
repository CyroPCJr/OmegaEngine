#pragma once

#include "MemoryRecord.h"
#include "Sensor.h"

namespace Omega::AI
{
	class Agent;

	using ImportanceCalculator = std::function<void(const Agent&, MemoryRecord&)>;

	class PerceptionModule
	{
	public:
		explicit PerceptionModule(Agent& agent, ImportanceCalculator importanceCalculator);

		template<class SensorType>
		SensorType* AddSensor(std::string name)
		{
			auto[iter, success] = mSensors.try_emplace(std::move(name), nullptr);
			if (success)
			{
				iter->second = std::make_unique<SensorType>();
			}
			return static_cast<SensorType*>(iter->second.get());
		}

		template<class SensorType>
		SensorType* GetSensor(const std::string& name)
		{
			auto iter = mSensors.find(name);
			return iter != mSensors.end() ? static_cast<SensorType*>(iter->second.get()) : nullptr;
		}

		void Update(float deltaTime);

		void SetMemorySpan(float memorySpan) { mMemorySpan = memorySpan; }

		const MemoryRecords& GetMemoryRecords() const { return mMemory; }

	private:
		using SensorMap = std::unordered_map<std::string, std::unique_ptr<Sensor>>;

		Agent& mAgent;
		SensorMap mSensors;
		MemoryRecords mMemory;
		ImportanceCalculator mCalculator;
		float mMemorySpan = 0.0f; // how long does the agent remember things
	};

}