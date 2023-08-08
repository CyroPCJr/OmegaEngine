#pragma once

#include "Sensor.h"

namespace Omega::AI
{

	class Agent;

	class VisualSensor : public Sensor
	{
	public:
		void Update(Agent& agent, MemoryRecords& memory, [[maybe_unused]] float deltaTime) override;

		float viewRange = 100.0f;
		float viewAngle = 45.0f;
	};

}