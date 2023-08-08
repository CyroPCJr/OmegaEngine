#pragma once

#include "FleeBehaviour.h"

namespace Omega::AI
{
	class EvadeBehaviour :public FleeBehaviour
	{
	public:
		~EvadeBehaviour() = default;

		Omega::Math::Vector2 Calculate(AI::Agent& agent) override;

		void ShowDebugDraw(const Agent& agent) override;
	};
}