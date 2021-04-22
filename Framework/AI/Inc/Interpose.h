#pragma once

#include "ArriveBehaviour.h"

namespace Omega::AI
{
	class Interpose : public ArriveBehaviour
	{
	public:
		virtual ~Interpose() = default;

		Omega::Math::Vector2 Calculate(AI::Agent& agent) override;
	};

}