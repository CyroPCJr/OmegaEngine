#pragma once

namespace Omega::Math
{
	struct Circle
	{
		Vector2 center = Vector2::Zero;
		float radius = 1.0f;

		constexpr Circle() noexcept {}
		constexpr Circle(const Vector2& center, float radius) noexcept : center(center), radius(radius) {}
		constexpr Circle(float x, float y, float radius) noexcept : center(x, y), radius(radius) {}
		
	};
}
