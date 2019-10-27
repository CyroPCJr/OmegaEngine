#pragma once

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
			return {};
		}

		static Matrix4 Translation(const Vector3& d)
		{
			return {};
		}

		static Matrix4 RotationX(float radian);
		static Matrix4 RotationY(float radian);
		static Matrix4 RotationZ(float radian);
		static Matrix4 RotationAxis(const Vector3& axis, float radian);
		static Matrix4 Scaling(float scale); 
	};
}