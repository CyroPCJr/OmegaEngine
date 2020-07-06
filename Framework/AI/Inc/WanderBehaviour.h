#pragma once

#include "SteeringBehavior.h"

namespace AI
{
	class WanderBehaviour :public AI::SteeringBehavior
	{
	public:

		struct Settings
		{
			float jitter = 10.0f;
			float radius = 40.0f;
			float distance = 40.0f;
		};

		Omega::Math::Vector2 Calculate(AI::Agent& agent) override;
		void SetSettings(Settings settings) { mSettings = settings; }
	private:
		Omega::Math::Vector2 mLocalTarget = Omega::Math::Vector2::Zero;
		Settings mSettings;
	};
}