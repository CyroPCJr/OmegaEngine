#pragma once

#include "SteeringBehavior.h"

namespace Omega::AI
{
	class AlignmentBehaviour :public SteeringBehavior
	{
	public:
		virtual ~AlignmentBehaviour() = default;

		Omega::Math::Vector2 Calculate(AI::Agent& agent) override;
	};

}