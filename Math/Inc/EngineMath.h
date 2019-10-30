#pragma once

#include "Common.h"

#include "Vector3.h"
#include "Matrix4.h"

namespace Omega::Math
{

	constexpr float Dot(const Vector3& a, const Vector3& b)
	{
		return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
	}

	constexpr Vector3 Cross(const Vector3& a, const Vector3& b)
	{
		return { (a.y * b.z) - (a.z * b.y),
				-((a.z * b.x) - (a.x * b.z)),
				 (a.x * b.y) - (a.y * b.x) };
	}

	constexpr float MagnitudeSqr(const Vector3& v)
	{
		return (v.x * v.x) + (v.y * v.y) + (v.z * v.z);
	}

	inline float Magnitude(const Vector3& v)
	{
		return sqrtf(MagnitudeSqr(v));
	}

	inline Vector3 Normalize(const Vector3& v)
	{
		const float lenght = Magnitude(v);
		OMEGAASSERT(lenght != 0, "Length cannot be zero.");
		return { v / lenght };
	}

	inline Matrix4 Transpose(const Matrix4& m)
	{
		/*
		 _11, _12, _13, _14;
		 _21, _22, _23, _24;
		 _31, _32, _33, _34;
		 _41, _42, _43, _44;


		 _11, _21, _31, _41;
		 _12, _22, _32, _42;
		 _13, _23, _33, _43;
		 _14, _24, _34, _44;
		
		*/
		Matrix4 result;
		result._11 = m._11;
		result._12 = m._21;
		result._13 = m._31;
		result._14 = m._41;

		result._21 = m._12;
		result._22 = m._22;
		result._23 = m._32;
		result._24 = m._42;

		result._31 = m._13;
		result._32 = m._23;
		result._33 = m._33;
		result._34 = m._43;

		result._41 = m._14;
		result._42 = m._24;
		result._43 = m._34;
		result._44 = m._44;
		return result;
	}

	constexpr float Determinant(const Matrix4& m)
	{
		/*
		m00	m01	m02	m03
		m10	m11	m12	m13
		m20	m21	m22	m23
		m30	m31	m32	m33


		_11, _12, _13, _14;
		 _21, _22, _23, _24;
		 _31, _32, _33, _34;
		 _41, _42, _43, _44;
		
		*/
		//const float det = (m._14 * m._23 * m._32*m._41) - (m._13*m.)
		///*m03* m12* m21* m30*/ - m02 * m13 * m21 * m30 - m03 * m11 * m22 * m30 + m01 * m13 * m22 * m30 +
		//m02 * m11 * m23 * m30 - m01 * m12 * m23 * m30 - m03 * m12 * m20 * m31 + m02 * m13 * m20 * m31 +
		//m03 * m10 * m22 * m31 - m00 * m13 * m22 * m31 - m02 * m10 * m23 * m31 + m00 * m12 * m23 * m31 +
		//m03 * m11 * m20 * m32 - m01 * m13 * m20 * m32 - m03 * m10 * m21 * m32 + m00 * m13 * m21 * m32 +
		//m01 * m10 * m23 * m32 - m00 * m11 * m23 * m32 - m02 * m11 * m20 * m33 + m01 * m12 * m20 * m33 +
		//m02 * m10 * m21 * m33 - m00 * m12 * m21 * m33 - m01 * m10 * m22 * m33 + m00 * m11 * m22 * m33;



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