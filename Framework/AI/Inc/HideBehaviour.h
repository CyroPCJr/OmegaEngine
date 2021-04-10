#pragma once

#include "SteeringBehavior.h"

namespace AI
{
	class HideBehaviour :public AI::SteeringBehavior
	{
	public:
		virtual ~HideBehaviour() = default;

		Omega::Math::Vector2 Calculate(AI::Agent& agent) override;

		void ShowDebugDraw(const Agent& agent) override;

	private: 
		Omega::Math::Vector2 GetHidingPosition(const Omega::Math::Vector2& obstaclePos, const float radius, const Omega::Math::Vector2& targetPos);

		Omega::Math::Vector2 mHidingSpot = Omega::Math::Vector2::Zero;
	};
}