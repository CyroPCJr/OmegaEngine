#pragma once

#include "SteeringBehavior.h"

namespace AI
{
	class AlignmentBehaviour :public AI::SteeringBehavior
	{
	public:
		Omega::Math::Vector2 Calculate(AI::Agent& agent) override;
	};

}