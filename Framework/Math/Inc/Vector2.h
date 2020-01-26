#pragma once

namespace Omega::Math
{

	struct Vector2
	{
		float x, y;

		constexpr Vector2() noexcept : Vector2{ 0.0f } {};
		constexpr Vector2(float f) noexcept : Vector2{ f,f } {};
		constexpr Vector2(float x, float y) noexcept : x{ x }, y{ y }{};

		// declaration
		const static Vector2 Zero;
		const static Vector2 One;
		const static Vector2 XAxis;
		const static Vector2 YAxis;
		const static Vector2 ZAxis;

		constexpr Vector2 operator~() const { return { -x, -y }; }
		// homework: add +,-,* and /
		constexpr Vector2 operator+(const Vector2& v) const { return { x + v.x, y + v.y }; }
		constexpr Vector2 operator-(const Vector2& v) const { return { x - v.x, y - v.y }; }
		constexpr Vector2 operator*(const Vector2& v) const { return { x * v.x, y * v.y }; }
		// multiplity vector by value scalar
		constexpr Vector2 operator*(const float v) const { return { x * v, y * v }; }

		inline Vector2 operator/(const float v) const
		{
			OMEGAASSERT(v != 0.0f, "value cannot be zero");
			return { x / v, y / v};
		}

		inline Vector2 operator/(const Vector2& v) const
		{
			OMEGAASSERT(v.x != 0.0f && v.y != 0.0f, "Vector values cannot be zero");
			return { x / v.x, y / v.y };
		}

		// homework: add -=, /=
		constexpr Vector2& operator+=(const Vector2& v)
		{
			x += v.x; y += v.y;
			return *this;
		}
		
		constexpr Vector2& operator-=(const Vector2& v)
		{
			x -= v.x;  y -= v.y;
			return *this;
		}
		
		constexpr Vector2& operator*=(const Vector2& v)
		{
			x *= v.x;  y *= v.y;
			return *this;
		}
		
		inline Vector2& operator/=(const float v)
		{
			OMEGAASSERT(v != 0.0f, "value cannot be zero");
			x /= v; y /= v;
			return *this;
		}

		inline Vector2& operator/=(const Vector2& v)
		{
			OMEGAASSERT(v.x != 0.0f && v.y != 0.0f, "Vector values cannot be zero");
			x /= v.x; y /= v.y;
			return *this;
		}

	};

} // namespace Omega::Math