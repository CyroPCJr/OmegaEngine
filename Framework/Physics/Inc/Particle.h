#pragma once

#include "Common.h"

namespace Omega::Physics
{
	struct Particle final
	{
		Math::Vector3 position = Math::Vector3::Zero;
		Math::Vector3 lastPosition = Math::Vector3::Zero;
		Math::Vector3 acceleration = Math::Vector3::Zero;
		float radius{ 1.0f };
		float invMass{ 1.0f };
		float bounce{ 1.0f };

		void SetPosition(const Math::Vector3& pos) noexcept
		{
			// position == lastPosition = no motion
			position = pos;
			lastPosition = pos;
		}

		void SetVelocity(const Math::Vector3& vel) noexcept
		{
			lastPosition = position - vel;
		}
	};
}