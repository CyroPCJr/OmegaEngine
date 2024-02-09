#pragma once

#include "ArriveBehaviour.h"

namespace Omega::AI
{
	class PathFollowingBehaviour final :public ArriveBehaviour
	{
	public:
		virtual ~PathFollowingBehaviour() = default;

		Omega::Math::Vector2 Calculate(AI::Agent& agent) override;

		void ShowDebugDraw(const Agent& agent) override;

		void SetPaths(const std::vector<Omega::Math::Vector2>& paths);

	private:

		Omega::Math::Vector2 PredictFutureLoc(const Omega::AI::Agent& agent) const;
		void FollowPath(AI::Agent& agent);

		Omega::Math::Vector2 GetNormalPoint(const Omega::Math::Vector2& predictionLocation, const Omega::Math::Vector2& pointA, const Omega::Math::Vector2& pointB);

		std::vector<Omega::Math::Vector2> mPaths;
		const float mSwitchPointDistance = 200.0f;
	};

}