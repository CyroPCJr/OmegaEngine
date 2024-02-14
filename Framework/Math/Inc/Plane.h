#pragma once

namespace Omega::Math
{
	struct Plane
	{
		Vector3 n = Vector3::YAxis;
		float d = 0.0f;

		constexpr explicit Plane(const Vector3& v, float _d) noexcept : n(v), d(_d) {};
	};
}