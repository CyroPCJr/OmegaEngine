#pragma once

#include "SteeringBehavior.h"

namespace AI
{

	class FleeBehaviour: public AI::SteeringBehavior
	{
	public:
		virtual ~FleeBehaviour() = default;
		Omega::Math::Vector2 Calculate(Agent& agent) override;
	protected:
		Omega::Math::Vector2 Fleeing(Agent & agent, const Omega::Math::Vector2& destination);
	};

}
