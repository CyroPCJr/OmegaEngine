#pragma once

namespace Omega::Math
{

	struct Vector2
	{
		float x = 0.0f;
		float y = 0.0f;

		constexpr Vector2() noexcept = default;
		constexpr Vector2(float f) noexcept : Vector2(f, f) {};
		constexpr Vector2(float x, float y) noexcept : x(x), y(y) {};

		// declaration
		const static Vector2 Zero;
		const static Vector2 One;
		const static Vector2 XAxis;
		const static Vector2 YAxis;
		const static Vector2 ZAxis;

		constexpr Vector2 operator~() const { return { -x, -y }; }

		constexpr Vector2 operator+(const Vector2& v) const { return { x + v.x, y + v.y }; }
		constexpr Vector2 operator-(const Vector2& v) const { return { x - v.x, y - v.y }; }
		constexpr Vector2 operator*(const Vector2& v) const { return { x * v.x, y * v.y }; }
		//constexpr Vector2 operator*(float val, const Vector2& v) const { return { x * v.x, y * v.y }; }
		constexpr Vector2 operator/(const Vector2& v) const { return { x / v.x, y / v.y }; }

		// multiplity vector by value scalar
		constexpr Vector2 operator*(const float v) const { return { x * v, y * v }; }
		friend constexpr Vector2 operator*(float v, const Vector2& vec) { return { vec.x * v, vec.y * v }; }
		constexpr Vector2 operator/(const float v) const { return { x / v, y / v }; }

		// Assignment operators
		constexpr Vector2& operator+=(const Vector2& v) { x += v.x; y += v.y; return *this; }
		constexpr Vector2& operator-=(const Vector2& v) { x -= v.x;  y -= v.y; return *this; }
		constexpr Vector2& operator*=(const Vector2& v) { x *= v.x;  y *= v.y; return *this; }
		constexpr Vector2& operator/=(const float v) { x /= v; y /= v; return *this; }
		constexpr Vector2& operator/=(const Vector2& v) { x /= v.x; y /= v.y; return *this; }
		constexpr Vector2& operator=(const float f) { x = f; y = f; return *this; }

		// Comparison operators
		constexpr bool operator==(const Vector2& v) const { return (x == v.x) && (y == v.y); }
		constexpr bool operator!=(const Vector2& v) const { return (x != v.x) || (y != v.y); }
	};

} // namespace Omega::Math