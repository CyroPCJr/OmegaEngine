#pragma once

namespace Omega::Math::Constants
{
	constexpr float HalfPi = 1.57079632679f;
	constexpr float Pi = 3.14159f;
	constexpr float TwoPi = Pi * 2.0f;
	constexpr float DegToRad = Pi / 180.0f;
	constexpr float RadToDeg = 180.0f / Pi;
	constexpr float Epsilon = std::numeric_limits<float>::epsilon();
}