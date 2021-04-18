#pragma once

#include "SteeringBehavior.h"

namespace AI
{
	enum class Deceleration { slow = 3, normal = 2, fast = 1 };

	class ArriveBehaviour :public AI::SteeringBehavior
	{
	public:
		virtual ~ArriveBehaviour() = default;

		Omega::Math::Vector2 Calculate(AI::Agent& agent) override;
		Omega::Math::Vector2 Arrive(AI::Agent& agent, Omega::Math::Vector2 destination);

		void ShowDebugDraw(const Agent& agent) override;

		inline void SetSlowRadius(float radius) { mSlowRadius = radius; }
	private:
		float mSlowRadius = 100.0f;
		/*const float decelerationTweaker = 0.3f;
		const int deceleration = 3;*/
	};

}