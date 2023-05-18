#pragma once

namespace Omega::Math
{
	struct AABB
	{
		Vector3 center = Vector3::Zero;
		Vector3 extend = Vector3::One;

		constexpr const Vector3 Min() const { return center - extend; }
		constexpr const Vector3 Max() const { return center + extend; }
	};
}