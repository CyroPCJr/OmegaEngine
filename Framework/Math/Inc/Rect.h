#pragma once

namespace Omega::Math
{

	struct Rect
	{
		float left = 0.0f;
		float top = 0.0f;
		float right = 0.0f;
		float bottom = 0.0f;

		constexpr Rect() noexcept : Rect(0.0f, 0.0f, 1.0f, 1.0f) {}
		constexpr Rect(float left, float top, float right, float bottom) noexcept : left(left), top(top), right(right), bottom(bottom) {}
	};

}