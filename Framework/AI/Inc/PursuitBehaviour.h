#pragma once

#include "SeekBehaviour.h"

namespace Omega::AI
{
	class PursuitBehaviour : public SeekBehaviour
	{
	public:
		virtual ~PursuitBehaviour() = default;

		Omega::Math::Vector2 Calculate(AI::Agent& agent) override;
		void ShowDebugDraw(const Agent& agent) override;

	private:
		float TurnAroundTime(const AI::Agent& agent, const Omega::Math::Vector2& targetPosition);

		Omega::Math::Vector2 mTargetDebug = Omega::Math::Vector2::Zero;
	};

}