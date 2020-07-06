#pragma once

namespace Omega::Math
{

	struct Rect
	{
		struct { float left, top; };
		struct { float right, bottom; };

		constexpr Rect() : Rect{ 0.0f, 0.0f, 1.0f, 1.0f } {}
		constexpr Rect(float left, float top, float right, float bottom) : left{ left }, top{ top }, right{ right }, bottom{ bottom } {}
	};

}