#pragma once

namespace Omega::Math
{
	struct LineSegment
	{
		Vector2 to = Vector2::Zero;
		Vector2 from = Vector2::Zero;

		constexpr LineSegment() noexcept :to(), from() {}
		constexpr LineSegment(Vector2 v0, Vector2 v1) noexcept : to(v0), from(v1) {}
	};
}
