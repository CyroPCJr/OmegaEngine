#pragma once

#include "SteeringBehavior.h"

namespace AI
{
	class ObstacleAvoidance :public SteeringBehavior
	{
	public:
		Omega::Math::Vector2 Calculate(Agent& agent) override;
	private:
		Omega::Math::Circle CheckObstacleAhead(const Omega::Math::Vector2& ahead, const Omega::Math::Vector2& ahead2, Agent& agent);

		bool lineIntersectsCircle(const Omega::Math::Vector2& ahead, const Omega::Math::Vector2& ahead2, Omega::Math::Circle obstacle);
	};
}