#pragma once

#include "Common.h"

namespace Omega::AI
{
	class Agent;

	class SteeringBehavior
	{
	public:
		SteeringBehavior() = default;
		virtual ~SteeringBehavior() = default;

		virtual Omega::Math::Vector2 Calculate(Agent& agent) = 0;
		virtual void ShowDebugDraw(const Agent& agent) {};

		inline void SetActive(bool active) { mActive = active; }
		inline bool IsActive() const { return mActive; }

	private:
		bool mActive = false;
	};
}