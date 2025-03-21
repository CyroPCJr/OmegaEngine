#pragma once

#include "SeekBehaviour.h"

namespace Omega::AI
{
	class WanderBehaviour :public SeekBehaviour
	{
	public:
		virtual ~WanderBehaviour() = default;

		struct Settings
		{
			float jitter = 10.0f;
			float radius = 40.0f;
			float distance = 40.0f;
		};

		Omega::Math::Vector2 Calculate(Agent& agent) override;
		void SetSettings(const Settings& settings) noexcept { mSettings = settings; }

		void ShowDebugDraw([[maybe_unused]] const Agent& agent) override;
	private:
		Settings mSettings;
		Omega::Math::Vector2 mLocalTarget = Omega::Math::Vector2::Zero;
		Omega::Math::Vector2 mCircleProjection = Omega::Math::Vector2::Zero;
		Omega::Math::Vector2 mCircleJitter = Omega::Math::Vector2::Zero;
	};
}