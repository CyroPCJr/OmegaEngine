#pragma once

#include "SteeringBehavior.h"

namespace AI
{
	enum Deceleration { slow = 3, normal = 2, fast = 1 };

	class ArriveBehaviour :public AI::SteeringBehavior
	{
	public:
		Omega::Math::Vector2 Calculate(AI::Agent& agent) override;
	};

}