#pragma once

#include "SteeringBehavior.h"

namespace Omega::AI
{
	class ArriveBehaviour :public SteeringBehavior
	{
	public:
		virtual ~ArriveBehaviour() = default;

		Omega::Math::Vector2 Calculate(AI::Agent& agent) override;
		Omega::Math::Vector2 Arrive(const AI::Agent& agent, const Omega::Math::Vector2& destination) const;

		void ShowDebugDraw(const Agent& agent) override;
		void SetSlowRadius(float radius) noexcept { mSlowRadius = radius; }
	private:
		float mSlowRadius = 100.0f;
	};

}