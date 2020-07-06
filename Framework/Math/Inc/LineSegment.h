#pragma once

namespace Omega::Math
{
	struct LineSegment
	{
		Vector2 from = Vector2::Zero;
		Vector2 to = Vector2::Zero;

		LineSegment() :to(), from() {}
		LineSegment(float x0, float y0, float x1, float y1) : to(), from() {}
		LineSegment(Vector2 v0, Vector2 v1) : to(v0), from(v1) {}
	};
}
