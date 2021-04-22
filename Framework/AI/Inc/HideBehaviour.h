#pragma once

#include "ArriveBehaviour.h"

namespace Omega::AI
{
	class HideBehaviour :public ArriveBehaviour
	{
	public:
		virtual ~HideBehaviour() = default;

		Omega::Math::Vector2 Calculate(AI::Agent& agent) override;

		void ShowDebugDraw(const Agent& agent) override;

	private: 
		Omega::Math::Vector2 mClosestObstacle = Omega::Math::Vector2::Zero;
	};
}