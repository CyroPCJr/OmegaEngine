#pragma once

namespace Omega::Math
{
	struct AABB
	{
		Vector3 center = Vector3::Zero;
		Vector3 extend = Vector3::One;

		constexpr AABB() noexcept = default;
		constexpr AABB(const Vector3& center, const Vector3& extend) noexcept : center(center), extend(extend) {}

		constexpr const Vector3 Min() const { return center - extend; }
		constexpr const Vector3 Max() const { return center + extend; }

		constexpr AABB FromMinMax(const Vector3& min, const Vector3& max)
		{
			return { (min + max) * 0.5f, (max - min) * 0.5f };
		}
	};
}