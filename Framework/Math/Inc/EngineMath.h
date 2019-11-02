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


	/*
	Original:
		 _11, _12, _13, _14;
		 _21, _22, _23, _24;
		 _31, _32, _33, _34;
		 _41, _42, _43, _44;

	Transpose:
		 _11, _21, _31, _41;
		 _12, _22, _32, _42;
		 _13, _23, _33, _43;
		 _14, _24, _34, _44;

		*/
	constexpr Matrix4 Transpose(const Matrix4& m)
	{
		Matrix4 result{};
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
		float cofactor1 = m._11 * ((m._22 * ((m._33 * m._44) - (m._34 * m._43))) - ((m._23 * ((m._32 * m._44) - (m._34 * m._42)))) + ((m._24 * ((m._32 * m._43) - (m._33 * m._42)))));
		float cofactor2 = m._12 * ((m._21 * ((m._33 * m._44) - (m._34 * m._43))) - ((m._23 * ((m._31 * m._44) - (m._34 * m._41)))) + ((m._24 * ((m._31 * m._43) - (m._33 * m._41)))));
		float cofactor3 = m._13 * ((m._21 * ((m._32 * m._44) - (m._34 * m._42))) - ((m._22 * ((m._31 * m._44) - (m._34 * m._41)))) + ((m._24 * ((m._31 * m._42) - (m._32 * m._41)))));
		float cofactor4 = m._14 * ((m._21 * ((m._32 * m._43) - (m._33 * m._42))) - ((m._22 * ((m._31 * m._43) - (m._33 * m._41)))) + ((m._23 * ((m._31 * m._42) - (m._32 * m._41)))));
		float det = cofactor1 - cofactor2 + cofactor3 - cofactor4;
		return det;
	}

	constexpr Matrix4 Inverse(const Matrix4& m)
	{
		const float det = Determinant(m);
		const float inverseDet = 1.f / det;
		Matrix4 matrix
		{

		};
		return matrix;
	}

	constexpr Vector3 TransformCoord(const Vector3& v, const Matrix4& m)
	{
		Vector3 vec;
		vec.x = (m._11*v.x) + (m._21*v.y) + (m._31*v.z) + m._41;
		vec.y = (m._12*v.x) + (m._22*v.y) + (m._32*v.z) + m._42;
		vec.z = (m._13*v.x) + (m._23*v.y) + (m._33*v.z) + m._43;
		return vec;
	}

	constexpr Vector3 TransformNormal(const Vector3& v, const Matrix4& m)
	{
		Vector3 vec;
		vec.x = (m._11*v.x) + (m._21*v.y) + (m._31*v.z);
		vec.y = (m._12*v.x) + (m._22*v.y) + (m._32*v.z);
		vec.z = (m._13*v.x) + (m._23*v.y) + (m._33*v.z);
		return vec;
	}

} // namespace Omega::Math