#pragma once

namespace Omega::Math
{
	struct LineSegment
	{
		Vector2 from = Vector2::Zero;
		Vector2 to = Vector2::Zero;

		constexpr LineSegment() noexcept = default;
		constexpr LineSegment(float fromX, float fromY, float toX, float toY) noexcept :from(fromX, fromY), to(toX, toY) {}
		constexpr LineSegment(const Vector2& v0, const Vector2& v1) noexcept : from(v0), to(v1) {}

	};
}
