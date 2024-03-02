#pragma once
// reference: https://learn.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-4-c4201?view=msvc-170
#pragma warning(disable : 4201)

namespace Omega::Math
{
	struct Matrix4;

	struct Quaternion
	{
		union
		{
			struct
			{
				float x, y, z, w;
			};

		};

		constexpr Quaternion() noexcept : x(0.0f), y(0.0f), z(0.0f), w(1.0f) {}
		constexpr Quaternion(float t_x, float t_y, float t_z, float t_w) noexcept : x(t_x), y(t_y), z(t_z), w(t_w) {}
		constexpr Quaternion(const Vector3& t_vec, float t_w) noexcept : x(t_vec.x), y(t_vec.y), z(t_vec.z), w(t_w) {}

		const static Quaternion Zero;
		const static Quaternion Identity;

		static Quaternion RotationAxis(const Vector3& axis, float rad);
		static Quaternion RotationMatrix(const Matrix4& matrix);
		static Quaternion RotationLook(const Vector3& direction, const Vector3& up = Vector3::YAxis);
		static Quaternion RotationFromTo(const Vector3& from, const Vector3& to);

#pragma region operator overloading

		constexpr Quaternion operator-() const
		{
			return { -x, -y, -z,-w };
		}

		constexpr Quaternion operator+(const Quaternion& rhs) const
		{
			return { x + rhs.x, y + rhs.y, z + rhs.z,w + rhs.w };
		}

		constexpr Quaternion operator-(const Quaternion& rhs) const
		{
			return { x - rhs.x, y - rhs.y, z - rhs.z,w - rhs.w };
		}

		constexpr Quaternion operator*(float scalar) const
		{
			return { x * scalar, y * scalar, z * scalar, w * scalar };
		}

		constexpr Quaternion operator*(const Quaternion& rhs) const
		{
			Quaternion q;
			q.w = (w * rhs.w) - (x * rhs.x) - (y * rhs.y) - (z * rhs.z);
			q.x = (w * rhs.x) + (x * rhs.w) + (y * rhs.z) - (z * rhs.y);
			q.y = (w * rhs.y) - (x * rhs.z) + (y * rhs.w) + (z * rhs.x);
			q.z = (w * rhs.z) + (x * rhs.y) - (y * rhs.x) + (z * rhs.w);
			return q;
		}

		constexpr Quaternion& operator*=(const Quaternion& rhs)
		{
			Quaternion q;
			q.w = (w * rhs.w) - (x * rhs.x) - (y * rhs.y) - (z * rhs.z);
			q.x = (w * rhs.x) + (x * rhs.w) + (y * rhs.z) - (z * rhs.y);
			q.y = (w * rhs.y) - (x * rhs.z) + (y * rhs.w) + (z * rhs.x);
			q.z = (w * rhs.z) + (x * rhs.y) - (y * rhs.x) + (z * rhs.w);

			x = q.x; y = q.y; z = q.z; w = q.w;
			return *this;
		}

		constexpr Quaternion operator*=(float scalar)
		{
			return { x *= scalar, y *= scalar, z *= scalar, w *= scalar };
		}

		constexpr bool operator==(const Quaternion& rhs) const
		{
			return (x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w);
		}

		constexpr bool operator!=(const Quaternion& rhs) const
		{
			return !(*this == rhs);
		}

#pragma endregion

		constexpr Quaternion Conjugate()
		{
			return { -x, -y,-z, w };
		}

	};
}
