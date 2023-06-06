#pragma once

namespace Omega::Math
{

	struct Vector3
	{
		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;

		constexpr Vector3() noexcept : Vector3(0.0f) {};
		constexpr Vector3(float f) noexcept : Vector3(f, f, f) {};
		constexpr Vector3(float x, float y, float z) noexcept : x(x), y(y), z(z) {};

		// declaration
		const static Vector3 Zero;
		const static Vector3 One;
		const static Vector3 XAxis;
		const static Vector3 YAxis;
		const static Vector3 ZAxis;

		constexpr Vector3 operator-() const { return { -x, -y ,-z }; }
		constexpr Vector3 operator+(const Vector3& v) const { return { x + v.x, y + v.y, z + v.z }; }
		constexpr Vector3 operator-(const Vector3& v) const { return { x - v.x, y - v.y, z - v.z }; }
		constexpr Vector3 operator*(const Vector3& v) const { return { x * v.x, y * v.y, z * v.z }; }

		// multiplity vector by value scalar
		constexpr Vector3 operator*(const float v) const { return { x * v, y * v, z * v }; }
		constexpr Vector3 operator/(const float v) const { return { x / v, y / v, z / v }; }

		// Assignment operators
		constexpr Vector3 operator/(const Vector3& v) const { return { x / v.x, y / v.y, z / v.z }; }
		constexpr Vector3& operator+=(const Vector3& v) { x += v.x; y += v.y; z += v.z; return *this; }
		constexpr Vector3& operator-=(const Vector3& v) { x -= v.x;  y -= v.y; z -= v.z; return *this; }
		constexpr Vector3& operator*=(const Vector3& v) { x *= v.x;  y *= v.y; z *= v.z; return *this; }
		constexpr Vector3& operator/=(const float v) { x /= v; y /= v; z /= v; return *this; }
		constexpr Vector3& operator/=(const Vector3& v) { x /= v.x; y /= v.y; z /= v.z; return *this; }

		// Comparison operators
		constexpr bool operator==(const Vector3& v) const { return (x == v.x) && (y == v.y) && (z == v.z); }
		constexpr bool operator!=(const Vector3& v) const { return (x != v.x) || (y != v.y) || (z != v.z); }

	};

}