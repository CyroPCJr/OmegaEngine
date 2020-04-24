#pragma once

#include "Common.h"
#include "Constants.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4.h"
#include "Quaternion.h"
#include "PerlinNoise.h"

namespace Omega::Math
{
	template<class T>
	constexpr T Min(T a, T b)
	{
		return (a < b) ? a : b;
	}

	template<class T>
	constexpr T Max(T a, T b)
	{
		return (a > b) ? a : b;
	}

	// Three way comparison
	// ref: https://en.cppreference.com/w/cpp/algorithm/clamp

	template<class T>
	constexpr T Clamp(T value, T min, T max)
	{
		return Max(min, Min(max, value));
	}

	template<class T>
	constexpr T Lerp(T a, T b, float t)
	{
		return a + (b - a) * t;
	}

	constexpr float Abs(float value)
	{
		return value >= 0.0f ? value : -value;
	}

	constexpr float Sqr(float value)
	{
		return value * value;
	}

	constexpr float Dot(const Vector3& a, const Vector3& b)
	{
		return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
	}

	constexpr Vector3 Cross(const Vector3& a, const Vector3& b)
	{
		return { (a.y * b.z) - (a.z * b.y),
				((a.z * b.x) - (a.x * b.z)),
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
		const float invNorm = 1.0f / lenght;
		return { v * invNorm };
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

	inline Matrix4 Inverse(const Matrix4& m)
	{
		const float det = Determinant(m);
		const float inverseDet = 1.0f / det;
		Matrix4 matrix;
		return matrix.Adjoint(m) * inverseDet;
	}

	constexpr Vector3 TransformCoord(const Vector3& v, const Matrix4& m)
	{
		const float w = (v.x * m._14) + (v.y * m._24) + (v.z * m._34) + (1.0f * m._44);
		Vector3 vec;
		vec.x = ((m._11 * v.x) + (m._21 * v.y) + (m._31 * v.z) + m._41) / w;
		vec.y = ((m._12 * v.x) + (m._22 * v.y) + (m._32 * v.z) + m._42) / w;
		vec.z = ((m._13 * v.x) + (m._23 * v.y) + (m._33 * v.z) + m._43) / w;
		return vec;
	}

	constexpr Vector3 TransformNormal(const Vector3& v, const Matrix4& m)
	{
		Vector3 vec;
		vec.x = (m._11 * v.x) + (m._21 * v.y) + (m._31 * v.z);
		vec.y = (m._12 * v.x) + (m._22 * v.y) + (m._32 * v.z);
		vec.z = (m._13 * v.x) + (m._23 * v.y) + (m._33 * v.z);
		return vec;
	}

	constexpr Vector3 GetTranslation(const Matrix4& matrix)
	{
		return Vector3(matrix._41, matrix._42, matrix._43);
	}

	constexpr Vector3 GetRight(const Matrix4& matrix)
	{
		return Vector3(matrix._11, matrix._12, matrix._13);
	}

	constexpr Vector3 GetUp(const Matrix4& matrix)
	{
		return Vector3(matrix._21, matrix._22, matrix._23);
	}

	constexpr Vector3 GetForward(const Matrix4& matrix)
	{
		return Vector3(matrix._31, matrix._32, matrix._33);
	}


#pragma region Quaternion Helper Functions

	constexpr float Dot(const Quaternion& from, const Quaternion& to)
	{
		return (from.x * to.x) + (from.y * to.y) + (from.z * to.z) + (from.w * to.w);
	}

	constexpr float MagnitudeSqr(const Quaternion& q)
	{
		return (q.x * q.x) + (q.y * q.y) + (q.z * q.z) + (q.w * q.w);
	}

	inline float Magnitude(const Quaternion& q)
	{
		return sqrtf(MagnitudeSqr(q));
	}

	inline Quaternion Normalize(const Quaternion& q)
	{
		const float length = Magnitude(q);
		OMEGAASSERT(length != 0, "[Quaternion] Length cannot be zero.");
		if (length == 1.0f)
		{
			return q;
		}
		const float invNorm = 1.0f / length;
		return { q * invNorm };
	}

	//Linear Interpolations
	constexpr Quaternion Lerp(const Quaternion& from, const Quaternion& to, float time)
	{
		return (from * (1.0f - time) + (to * time));
	}

	//Spherical Linear Interpolations
	inline Quaternion Slerp(Quaternion& from, Quaternion& to, float time)
	{
		/*
		Reference:
		https://www.euclideanspace.com/maths/algebra/realNormedAlgebra/quaternions/slerp/index.htm
		*/
		// Only unit quaternions are valid rotations.
		// Normalize to avoid undefined behavior.
		/*from = Normalize(from);
		to = Normalize(to);*/

		// Compute the cosine of the angle between the two vectors.
		float angle = Dot(from, to);

		// If the dot product is negative, slerp won't take
		// the shorter path. Note that v1 and -v1 are equivalent when
		// the negation is applied to all four components. Fix by 
		// reversing one quaternion.
		if (angle < 0.0f)
		{
			to = -to;
			angle = -angle;
		}
		else if (angle > 0.9995f)
		{
			return Normalize(Lerp(from, to, time));
		}

		// Since dot is in range [0, angleThreshold], acos is safe
		const float theta = acosf(angle);        // theta_0 = angle between input vectors
		const float inverseSinTheta = 1.0f / sinf(theta);
		const float scale = sinf(theta * (1.0f - time)) * inverseSinTheta;
		const float inverseScale = sinf(theta * time) * inverseSinTheta;
		return (from * scale) + (to * inverseScale);
	}

#pragma endregion
}