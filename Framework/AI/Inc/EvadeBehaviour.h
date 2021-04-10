#pragma once

#include "FleeBehaviour.h"

namespace AI
{
	class EvadeBehaviour :public AI::FleeBehaviour
	{
	public:
		virtual ~EvadeBehaviour() = default;

		Omega::Math::Vector2 Calculate(AI::Agent& agent) override;

		void ShowDebugDraw(const Agent& agent) override;
	};
}