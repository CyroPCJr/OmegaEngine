#pragma once

#include "SeekBehaviour.h"

namespace Omega::AI
{
	class SeparationBehaviour :public SeekBehaviour
	{
	public:
		virtual ~SeparationBehaviour() = default;

		Omega::Math::Vector2 Calculate(AI::Agent& agent) override;
	};

}