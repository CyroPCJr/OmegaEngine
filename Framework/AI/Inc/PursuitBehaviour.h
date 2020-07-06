#pragma once

#include "SteeringBehavior.h"

namespace AI
{
	class PursuitBehaviour :public AI::SteeringBehavior
	{
	public:
		Omega::Math::Vector2 Calculate(AI::Agent& agent) override;
	};

}