#pragma once

#include "SteeringBehavior.h"

namespace Omega::AI
{
	class SeekBehaviour :public SteeringBehavior
	{
	public:
		virtual ~SeekBehaviour() = default;

		Omega::Math::Vector2 Calculate(AI::Agent& agent) override;

		void ShowDebugDraw(const Agent& agent) override;
	protected:
		Omega::Math::Vector2 Seek(Agent& agent, const Omega::Math::Vector2& destination);
	};

}