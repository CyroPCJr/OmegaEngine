#pragma once

#include "SteeringBehavior.h"

namespace Omega::AI
{
	class WallAvoidanceBehaviour :public SteeringBehavior
	{
	public:
		virtual ~WallAvoidanceBehaviour() = default;

		Omega::Math::Vector2 Calculate(AI::Agent& agent) override;
		Omega::Math::Vector2 WallAvoidance(const AI::Agent& agent, Omega::Math::Vector2& destination);

		void ShowDebugDraw(const Agent& agent) override;

		void setDetectionFeelerLength(float length) noexcept { mDetectionFeelerLength = length; }

	private:
		void CreateFeelers(const Agent& agent);

		std::array<Omega::Math::Vector2, 3> mFeelers{0};
		float mDetectionFeelerLength = 100.0f;
	};

}