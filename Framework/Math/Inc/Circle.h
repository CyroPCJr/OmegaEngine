#pragma once

namespace Omega::Math
{
	struct Circle
	{
		Vector2 center;
		float radius;

		Circle() : center(0.0f, 0.0f), radius(1.0f) {}
		Circle(const Vector2& center, float radius) : center(center), radius(radius) {}
		Circle(float x, float y, float radius) : center(x, y), radius(radius) {}
	};
}
