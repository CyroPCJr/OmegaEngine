#pragma once

namespace Omega::Math
{

	struct Vector3
	{
		float x, y, z;

		constexpr Vector3() noexcept : Vector3{ 0.0f } {};
		constexpr Vector3(float f) noexcept : Vector3{ f,f,f } {};
		constexpr Vector3(float x, float y, float z) noexcept : x{ x }, y{ y }, z{ z } {};

		// declaration
		const static Vector3 Zero;
		const static Vector3 One;
		const static Vector3 XAxis;
		const static Vector3 YAxis;
		const static Vector3 ZAxis;

		constexpr Vector3 operator~() const { return { -x, -y ,-z }; }
		// homework: add +,-,* and /
		constexpr Vector3 operator+(const Vector3& v) const { return { x + v.x, y + v.y, z + v.z }; }
		constexpr Vector3 operator-(const Vector3& v) const { return { x - v.x, y - v.y, z - v.z }; }
		constexpr Vector3 operator*(const Vector3& v) const { return { x * v.x, y * v.y, z * v.z }; }
		// multiplity vector by value scalar
		constexpr Vector3 operator*(const float v) const { return { x * v, y * v, z * v }; }

		inline Vector3 operator/(const float v) const
		{
			OMEGAASSERT(v != 0.0f, "value cannot be zero");
			return { x / v, y / v, z / v };
		}

		inline Vector3 operator/(const Vector3& v) const
		{
			OMEGAASSERT(v.x != 0.0f && v.y != 0.0f && v.z != 0.0f, "Vector values cannot be zero");
			return { x / v.x, y / v.y, z / v.z };
		}

		// homework: add -=, /=
		constexpr Vector3& operator+=(const Vector3& v)
		{
			x += v.x; y += v.y; z += v.z;
			return *this;
		}

		constexpr Vector3& operator-=(const Vector3& v)
		{
			x -= v.x;  y -= v.y; z -= v.z;
			return *this;
		}

		constexpr Vector3& operator*=(const Vector3& v)
		{
			x *= v.x;  y *= v.y; z *= v.z;
			return *this;
		}

		inline Vector3& operator/=(const float v)
		{
			OMEGAASSERT(v != 0.0f, "value cannot be zero");
			x /= v; y /= v; z /= v;
			return *this;
		}

		inline Vector3& operator/=(const Vector3& v)
		{
			OMEGAASSERT(v.x != 0.0f && v.y != 0.0f && v.z != 0.0f, "Vector values cannot be zero");
			x /= v.x; y /= v.y; z /= v.z;
			return *this;
		}

	};

} // namespace Omega::Math