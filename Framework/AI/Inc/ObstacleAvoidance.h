#pragma once

#include "SteeringBehavior.h"

namespace Omega::AI
{
	class ObstacleAvoidance :public SteeringBehavior
	{
	public:
		virtual ~ObstacleAvoidance() = default;

		Omega::Math::Vector2 Calculate(Agent& agent) override;
		void ShowDebugDraw(const Agent& agent);
	private:

		float boxExtention = 85.0f;
		float brakingWeight = 2.8f;
		float sideForceScale = 2.0f;

		float mProjectionBoxLength = 0.0f;
	};
}