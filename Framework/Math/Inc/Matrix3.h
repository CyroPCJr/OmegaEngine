#pragma once

namespace Omega::Math
{
	struct Matrix3
	{
		union
		{
			struct  // row + collum subscripts
			{
				float _11, _12, _13;
				float _21, _22, _23;
				float _31, _32, _33;
			};
			std::array<float, 9>v;
		};

		const static Matrix3 Identity;
		const static Matrix3 Zero;

		static Matrix3 Translation(float x, float y) { return { 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, x, y, 1.0f }; }
		static Matrix3 Translation(const Vector2& v) { return { 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, v.x, v.y, 1.0f }; }
		static Matrix3 Rotation(float rad)
		{
			const float cos = cosf(rad);
			const float sin = sinf(rad);
			return { cos, sin, 0.0f, -sin, cos, 0.0f, 0.0f, 0.0f, 1.0f };
		}
		static Matrix3 Scaling(float s) { return { s, 0.0f, 0.0f, 0.0f, s, 0.0f, 0.0f, 0.0f, 1.0f }; }
		static Matrix3 Scaling(float sx, float sy) { return { sx, 0.0f, 0.0f, 0.0f, sy, 0.0f, 0.0f, 0.0f, 1.0f }; }
		static Matrix3 Scaling(const Vector2& s) { return { s.x, 0.0f, 0.0f, 0.0f, s.y, 0.0f, 0.0f, 0.0f, 1.0f }; }

		Matrix3 operator-() const
		{
			return {
				-_11, -_12, -_13,
				-_21, -_22, -_23,
				-_31, -_32, -_33 };
		}

		Matrix3 operator+(const Matrix3& rhs) const
		{
			return {
				_11 + rhs._11, _12 + rhs._12, _13 + rhs._13,
				_21 + rhs._21, _22 + rhs._22, _23 + rhs._23,
				_31 + rhs._31, _32 + rhs._32, _33 + rhs._33 };
		}

		Matrix3 operator-(const Matrix3& rhs) const
		{
			return {
				_11 - rhs._11, _12 - rhs._12, _13 - rhs._13,
				_21 - rhs._21, _22 - rhs._22, _23 - rhs._23,
				_31 - rhs._31, _32 - rhs._32, _33 - rhs._33 };
		}

		Matrix3 operator*(const Matrix3& rhs) const
		{
			return {
				(_11 * rhs._11) + (_12 * rhs._21) + (_13 * rhs._31),
				(_11 * rhs._12) + (_12 * rhs._22) + (_13 * rhs._32),
				(_11 * rhs._13) + (_12 * rhs._23) + (_13 * rhs._33),

				(_21 * rhs._11) + (_22 * rhs._21) + (_23 * rhs._31),
				(_21 * rhs._12) + (_22 * rhs._22) + (_23 * rhs._32),
				(_21 * rhs._13) + (_22 * rhs._23) + (_23 * rhs._33),

				(_31 * rhs._11) + (_32 * rhs._21) + (_33 * rhs._31),
				(_31 * rhs._12) + (_32 * rhs._22) + (_33 * rhs._32),
				(_31 * rhs._13) + (_32 * rhs._23) + (_33 * rhs._33) };
		}

		Matrix3 operator*(float s) const
		{
			return {
				_11 * s, _12 * s, _13 * s,
				_21 * s, _22 * s, _23 * s,
				_31 * s, _32 * s, _33 * s };
		}

		Matrix3 operator/(float s) const
		{
			return {
				_11 / s, _12 / s, _13 / s,
				_21 / s, _22 / s, _23 / s,
				_31 / s, _32 / s, _33 / s };
		}

		Matrix3 operator+=(const Matrix3& rhs)
		{
			_11 += rhs._11; _12 += rhs._12; _13 += rhs._13;
			_21 += rhs._21; _22 += rhs._22; _23 += rhs._23;
			_31 += rhs._31; _32 += rhs._32; _33 += rhs._33;
			return *this;
		}

	};
}