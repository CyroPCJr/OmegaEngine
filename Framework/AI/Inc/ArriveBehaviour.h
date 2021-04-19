#pragma once

#include "SteeringBehavior.h"

namespace AI
{
	class ArriveBehaviour :public AI::SteeringBehavior
	{
	public:
		virtual ~ArriveBehaviour() = default;

		Omega::Math::Vector2 Calculate(AI::Agent& agent) override;
		Omega::Math::Vector2 Arrive(const AI::Agent& agent, const Omega::Math::Vector2& destination);

		void ShowDebugDraw(const Agent& agent) override;
		inline void SetSlowRadius(float radius) { mSlowRadius = radius; }
	private:
		float mSlowRadius = 100.0f;
	};

}