#pragma once

#include "SeekBehaviour.h"

namespace AI
{
	class PursuitBehaviour : public AI::SeekBehaviour
	{
	public:
		virtual ~PursuitBehaviour() = default;

		Omega::Math::Vector2 Calculate(AI::Agent& agent) override;
	};

}