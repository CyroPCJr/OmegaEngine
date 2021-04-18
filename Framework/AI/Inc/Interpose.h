#pragma once

#include "ArriveBehaviour.h"

namespace AI 
{
	class Interpose : public AI::ArriveBehaviour
	{
	public:
		virtual ~Interpose() = default;

		Omega::Math::Vector2 Calculate(AI::Agent& agent) override;
	};

}