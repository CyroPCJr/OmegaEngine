#pragma once

#include "SteeringBehavior.h"

namespace AI
{
	class SeparationBehaviour :public AI::SteeringBehavior
	{
	public:
		virtual ~SeparationBehaviour() = default;

		Omega::Math::Vector2 Calculate(AI::Agent& agent) override;
	};

}