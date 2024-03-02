#pragma once

namespace Omega::Math
{
	struct Plane
	{
		Vector3 n{ Vector3::YAxis };
		float d{ 0.0f };

		constexpr Plane(const Vector3& t_v, float t_d) noexcept : n(t_v), d(t_d) {};
	};
}