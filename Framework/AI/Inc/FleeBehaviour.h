#pragma once

#include "SteeringBehavior.h"

namespace Omega::AI
{

	class FleeBehaviour : public SteeringBehavior
	{
	public:
		virtual ~FleeBehaviour() = default;
		Omega::Math::Vector2 Calculate(Agent& agent) override;
		void ShowDebugDraw(const Agent& agent) override;
	protected:
		Omega::Math::Vector2 Fleeing(Agent& agent, const Omega::Math::Vector2& destination);
	private:
		const float mPanicDistance = 100.0f * 100.0f;
	};

}
