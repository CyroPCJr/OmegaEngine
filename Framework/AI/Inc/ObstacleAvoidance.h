#pragma once

#include "SteeringBehavior.h"

namespace AI
{
	class ObstacleAvoidance :public SteeringBehavior
	{
	public:
		virtual ~ObstacleAvoidance() = default;

		Omega::Math::Vector2 Calculate(Agent& agent) override;
	private:
		Omega::Math::Circle CheckObstacleAhead(const Omega::Math::Vector2& ahead, const Omega::Math::Vector2& ahead2, const Agent& agent) const;

		bool lineIntersectsCircle(const Omega::Math::Vector2& ahead, const Omega::Math::Vector2& ahead2, const Omega::Math::Circle& obstacle) const;
	};
}