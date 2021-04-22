#pragma once

#include "SeekBehaviour.h"

namespace Omega::AI
{
	class CohesionBehaviour :public SeekBehaviour
	{
	public:
		virtual ~CohesionBehaviour() = default;

		Omega::Math::Vector2 Calculate(AI::Agent& agent) override;
	};

}