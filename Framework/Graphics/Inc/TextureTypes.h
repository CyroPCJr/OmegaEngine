#pragma once

namespace Omega::Graphics
{
	using TextureId = std::size_t;

	enum class Pivot
	{
		TopLeft,
		Top,
		TopRight,
		Left,
		Center,
		Right,
		BottomLeft,
		Bottom,
		BottomRight
	};

	enum class Flip
	{
		None,
		Horizontal,
		Vertical,
		Both
	};

}