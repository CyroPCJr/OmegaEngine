#pragma once

namespace Omega::Math
{

	struct Vector4
	{
		float x, y, z, w;

		constexpr Vector4() noexcept : Vector4{ 0.0f } {};
		constexpr Vector4(float f) noexcept : Vector4{ f,f,f,f } {};
		constexpr Vector4(float x, float y, float z, float w) noexcept : x{ x }, y{ y }, z{ z }, w{ w } {};

		// declaration
		const static Vector4 Zero;
		const static Vector4 One;
		const static Vector4 XAxis;
		const static Vector4 YAxis;
		const static Vector4 ZAxis;

		constexpr Vector4 operator~() const { return { -x, -y ,-z, -w }; }
		// homework: add +,-,* and /
		constexpr Vector4 operator+(const Vector4& v) const { return { x + v.x, y + v.y, z + v.z, w + v.w }; }
		constexpr Vector4 operator-(const Vector4& v) const { return { x - v.x, y - v.y, z - v.z, w - v.w }; }
		constexpr Vector4 operator*(const Vector4& v) const { return { x * v.x, y * v.y, z * v.z, w * v.w }; }
		// multiplity vector by value scalar
		constexpr Vector4 operator*(const float v) const { return { x * v, y * v, z * v, w * v }; }

		inline Vector4 operator/(const float v) const
		{
			OMEGAASSERT(v != 0.0f, "value cannot be zero");
			return { x / v, y / v, z / v, w / v };
		}

		inline Vector4 operator/(const Vector4& v) const
		{
			OMEGAASSERT(v.x != 0.0f && v.y != 0.0f && v.z != 0.0f, "Vector values cannot be zero");
			return { x / v.x, y / v.y, z / v.z, w / v.w };
		}

		// homework: add -=, /=
		constexpr Vector4& operator+=(const Vector4& v)
		{
			x += v.x; y += v.y; z += v.z; w += v.w;
			return *this;
		}

		constexpr Vector4& operator-=(const Vector4& v)
		{
			x -= v.x;  y -= v.y; z -= v.z; w -= v.w;
			return *this;
		}

		constexpr Vector4& operator*=(const Vector4& v)
		{
			x *= v.x;  y *= v.y; z *= v.z; w *= v.w;
			return *this;
		}

		inline Vector4& operator/=(const float v)
		{
			OMEGAASSERT(v != 0.0f, "value cannot be zero");
			x /= v; y /= v; z /= v; w /= v;
			return *this;
		}

		inline Vector4& operator/=(const Vector4& v)
		{
			OMEGAASSERT(v.x != 0.0f && v.y != 0.0f && v.z != 0.0f, "Vector values cannot be zero");
			x /= v.x; y /= v.y; z /= v.z; w /= v.w;
			return *this;
		}

	};

} // namespace Omega::Math