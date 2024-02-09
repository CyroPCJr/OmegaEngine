#pragma once

namespace Omega::Math
{
	struct Sphere
	{
		Vector3 center = Vector3::Zero;
		float radius = 1.0f;

		constexpr Sphere() noexcept = default;
		constexpr Sphere(float x, float y, float z, float radius) noexcept : center(x, y, z), radius(radius) {}
		constexpr Sphere(const Vector3& center, float radius) noexcept : center(center), radius(radius) {}
	};
}