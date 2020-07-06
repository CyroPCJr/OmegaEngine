#pragma once

#include "SteeringBehavior.h"

namespace AI
{
	class HideBehaviour :public AI::SteeringBehavior
	{
	public:
		Omega::Math::Vector2 Calculate(AI::Agent& agent) override;
	};
}