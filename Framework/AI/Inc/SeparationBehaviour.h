#pragma once

#include "SeekBehaviour.h"

namespace AI
{
	class SeparationBehaviour :public AI::SeekBehaviour
	{
	public:
		virtual ~SeparationBehaviour() = default;

		Omega::Math::Vector2 Calculate(AI::Agent& agent) override;
	};

}