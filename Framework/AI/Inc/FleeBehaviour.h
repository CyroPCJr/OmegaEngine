#pragma once

#include "SteeringBehavior.h"

namespace AI
{

	class FleeBehaviour: public AI::SteeringBehavior
	{
	public:
		Omega::Math::Vector2 Calculate(Agent& agent) override;
	};

}
