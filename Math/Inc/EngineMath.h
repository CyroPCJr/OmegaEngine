#pragma once

#include "Common.h"

#include "Vector3.h"
#include "Matrix4.h"

namespace Omega::Math
{

	constexpr float Dot(const Vector3& a, const Vector3& b)
	{
		return (a.x*b.x) + (a.y*b.y) + (a.z*b.z);
	}

	constexpr Vector3 Cross(const Vector3& a, const Vector3& b)
	{
		const float i = (a.y*b.z) - (a.z*b.y);
		const float j = (a.z*b.x) - (a.x*b.z);
		const float k = (a.x*b.y) - (a.y*b.x);
		return { i,j,k };
	}

	constexpr float MagnitudeSqr(const Vector3& v)
	{
		return (v.x *v.x) + (v.y*v.y) + (v.z*v.z);
	}

	inline float Magnitude(const Vector3& v)
	{
		return sqrt(MagnitudeSqr(v));
	}

	inline Vector3 Normalize(const Vector3& v)
	{
		return 0.0f;
	}


	constexpr Matrix4 Transpose(const Matrix4& m)
	{
		return {};
	}

	constexpr Matrix4 Determinant(const Matrix4& m)
	{
		return {};
	}

	constexpr Matrix4 Inverse(const Matrix4& m)
	{
		return {};
	}

	constexpr Matrix4 TransformCoord(const Matrix4& v, const Matrix4& m)
	{
		return {};
	}

	constexpr Matrix4 TransformNormal(const Matrix4& v, const Matrix4& m)
	{
		return {};
	}

} // namespace Omega::Math