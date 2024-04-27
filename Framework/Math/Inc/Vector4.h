#pragma once

namespace Omega::Math
{

	struct Vector4
	{
		float x = 0.0f;
		float y = 0.0f; 
		float z = 0.0f;
		float w = 0.0f;

		constexpr Vector4() noexcept : Vector4(0.0f) {};
		constexpr Vector4(float f) noexcept : Vector4(f, f, f, f) {};
		constexpr Vector4(float x, float y, float z, float w) noexcept : x(x), y(y), z(z), w(w) {};

		// declaration
		const static Vector4 Zero;
		const static Vector4 One;
		const static Vector4 XAxis;
		const static Vector4 YAxis;
		const static Vector4 ZAxis;

		constexpr Vector4 operator~() const { return { -x, -y ,-z, -w }; }

		constexpr Vector4 operator+(const Vector4& v) const { return { x + v.x, y + v.y, z + v.z, w + v.w }; }
		constexpr Vector4 operator-(const Vector4& v) const { return { x - v.x, y - v.y, z - v.z, w - v.w }; }
		constexpr Vector4 operator*(const Vector4& v) const { return { x * v.x, y * v.y, z * v.z, w * v.w }; }
		constexpr Vector4 operator/(const Vector4& v) const { return { x / v.x, y / v.y, z / v.z, w / v.w }; }

		// multiplity vector by value scalar
		constexpr Vector4 operator*(const float v) const { return { x * v, y * v, z * v, w * v }; }
		friend constexpr Vector4 operator*(float v, const Vector4& vec) { return { vec.x * v, vec.y * v, vec.z * v, vec.w * v  }; }
		constexpr Vector4 operator/(const float v) const { return { x / v, y / v, z / v, w / v }; }

		// Assignment operators
		constexpr Vector4& operator+=(const Vector4& v) { x += v.x; y += v.y; z += v.z; w += v.w; return *this; }
		constexpr Vector4& operator-=(const Vector4& v) { x -= v.x;  y -= v.y; z -= v.z; w -= v.w; return *this; }
		constexpr Vector4& operator*=(const Vector4& v) { x *= v.x;  y *= v.y; z *= v.z; w *= v.w; return *this; }
		constexpr Vector4& operator/=(const float v) { x /= v; y /= v; z /= v; w /= v; return *this; }
		constexpr Vector4& operator/=(const Vector4& v) { x /= v.x; y /= v.y; z /= v.z; w /= v.w; return *this; }

		// Comparison operators
		constexpr bool operator==(const Vector4& v) const { return (x == v.x) && (y == v.y) && (z == v.z) && (w == v.w); }
		constexpr bool operator!=(const Vector4& v) const { return (x != v.x) || (y != v.y) || (z != v.z) || (w != v.w); }

	};

} // namespace Omega::Math