#pragma once
// const for PI
constexpr float M_PI = 3.14159265358979323846264338327950288f;

namespace Omega::Math
{

	struct Matrix4
	{
		// row + collum subscripts
		float _11, _12, _13, _14;
		float _21, _22, _23, _24;
		float _31, _32, _33, _34;
		float _41, _42, _43, _44;

		const static Matrix4 Identity;

		constexpr Matrix4 operator*(const Matrix4& m) const
		{
			const float collum_1 = (_11 * m._11) + (_21 * m._21) + (_31 * m._31) + (_41 * m._41);
			const float collum_2 = (_21 * m._11) + (_21 * m._21) + (_31 * m._31) + (_41 * m._41);

			return {};
		}

		static Matrix4 Translation(const Vector3& d)
		{
			Matrix4 translation = Identity;
			translation._14 = d.x;
			translation._23 = d.y;
			translation._34 = d.z;
			return translation;
		}

		/*
			convert radian to degree
		*/
		static float rad2deg(float rad)
		{
			return rad * (M_PI / 180.f);
		}

		static Matrix4 RotationX(float radian)
		{
			const float degree = rad2deg(radian);
			const float cos = cosf(degree);
			const float sin = sinf(degree);
			Matrix4 rotX = Identity;
			rotX._22 = cos; rotX._23 = -sin;
			rotX._32 = sin; rotX._33 = cos;
			return rotX;
		}

		static Matrix4 RotationY(float radian)
		{
			const float degree = rad2deg(radian);
			const float cos = cosf(degree);
			const float sin = sinf(degree);
			Matrix4 rotY = Identity;
			rotY._11 = cos; rotY._13 = sin;
			rotY._31 = -sin; rotY._33 = cos;
			return rotY;
		}

		static Matrix4 RotationZ(float radian)
		{
			const float degree = rad2deg(radian);
			const float cos = cosf(degree);
			const float sin = sinf(degree);
			Matrix4 rotZ = Identity;
			rotZ._11 = cos; rotZ._12 = -sin;
			rotZ._21 = sin; rotZ._22 = cos;
			return rotZ;
		}

		static Matrix4 RotationAxis(const Vector3& axis, float radian)
		{
			const float degree = rad2deg(radian);
			const float cos = cosf(degree);
			const float sin = sinf(degree);
			const float oneMinusCos = (1 - cos);
			Matrix4 rot = Identity;
			rot._11 = oneMinusCos + cos; rot._12 = oneMinusCos - sin; rot._13 = oneMinusCos + sin;
			rot._21 = oneMinusCos + sin; rot._22 = oneMinusCos + cos; rot._23 = oneMinusCos - sin;
			rot._31 = oneMinusCos - sin; rot._32 = oneMinusCos + sin; rot._33 = oneMinusCos + cos;
			return rot;
		}

		static Matrix4 Scaling(float scale)
		{
			// scaling diagonal
			Matrix4 sca = Identity;
			sca._11 *= scale;
			sca._22 *= scale;
			sca._33 *= scale;
			sca._44 *= scale;
			return sca;
		}
	};
}