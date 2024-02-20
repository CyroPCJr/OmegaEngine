#pragma once

namespace Omega::Math::Constants
{
	constexpr const float HalfPi = 1.57079632679f;
	constexpr const float Pi = 3.14159f;
	constexpr const float TwoPi = Pi * 2.0f;
	constexpr const float DegToRad = Pi / 180.0f;
	constexpr const float RadToDeg = 180.0f / Pi;
	constexpr const float Epsilon = std::numeric_limits<float>::epsilon();
}