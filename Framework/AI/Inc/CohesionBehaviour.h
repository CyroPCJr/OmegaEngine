#pragma once

#include "SeekBehaviour.h"

namespace AI
{
	class CohesionBehaviour :public AI::SeekBehaviour
	{
	public:
		virtual ~CohesionBehaviour() = default;

		Omega::Math::Vector2 Calculate(AI::Agent& agent) override;
	};

}