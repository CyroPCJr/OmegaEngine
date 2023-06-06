#pragma once

#include "Common.h"

// Linear Algebra
#include "Constants.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4.h"
#include "Matrix3.h"
#include "Quaternion.h"
#include "Random.h"
#include "PerlinNoise.h"

// Geometry
#include "Plane.h"
#include "Ray.h"
#include "OBB.h"
#include "AABB.h"
#include "Sphere.h"
#include "Circle.h"
#include "Rect.h"
#include "LineSegment.h"

#include "MetaRegistration.h"

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
	constexpr T Lerp(const T& a, const T& b, float t)
	{
		return a + ((b - a) * t);
	}

	template<class T>
	constexpr T Saturate(const T& val, const T& min, const T& max)
	{
		return Min(Max(val, min), max);
	}

	constexpr float Abs(float value)
	{
		return value >= 0.0f ? value : -value;
	}

	constexpr float Sqr(float value)
	{
		return value * value;
	}

	constexpr bool IsEmpty(const Rect& rect)
	{
		return rect.right <= rect.left || rect.bottom <= rect.top;
	}

#pragma region Vector 2

	constexpr Vector2 PerpendicularLH(const Vector2& v)
	{
		return { -v.y, v.x };
	}

	constexpr Vector2 PerpendicularRH(const Vector2& v)
	{
		return { v.y, -v.x };
	}

	constexpr float Dot(const Vector2& a, const Vector2& b)
	{
		return (a.x * b.x) + (a.y * b.y);
	}

	constexpr float MagnitudeSqr(const Vector2& v)
	{
		return (v.x * v.x) + (v.y * v.y);
	}

	inline float Magnitude(const Vector2& v)
	{
		return sqrt(MagnitudeSqr(v));
	}

	inline float Distance(const Vector2& v1, const Vector2& v2)
	{
		return Magnitude(v1 - v2);
	}

	constexpr float DistanceSqr(const Vector2& v1, const Vector2& v2)
	{
		return MagnitudeSqr(v1 - v2);
	}

	inline Vector2 Normalize(const Vector2& v)
	{
		if (const float lenght = Magnitude(v);
			lenght > 0.0f)
		{
			const float invNorm = 1.0f / lenght;
			return { v * invNorm };
		}
		return v;
	}

	constexpr Vector2 Lerp(const Vector2& v1, const Vector2& v2, float t)
	{
		return v1 + ((v2 - v1) * t);
	}

	inline Vector2 Truncate(const Vector2& v, float max)
	{
		const float lenght = Magnitude(v);
		if (const float i = (lenght != 0.0f) ? max / lenght : 0.0f;
			i < 1.0f)
		{
			return v * i;
		}
		return v;
	}
#pragma endregion

#pragma region Vector 3

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

	inline float Distance(const Vector3& v1, const Vector3& v2)
	{
		return Magnitude(v1 - v2);
	}

	constexpr float DistanceSqr(const Vector3& v1, const Vector3& v2)
	{
		return MagnitudeSqr(v1 - v2);
	}

	inline Vector3 Normalize(const Vector3& v)
	{
		if (const float lenght = Magnitude(v); lenght > 0.0f)
		{
			const float invNorm = 1.0f / lenght;
			return { v * invNorm };
		}
		else
		{
			return { v };
		}
		///OMEGAASSERT(lenght != 0, "Length cannot be zero.");
	}

	constexpr Vector3 TriangleNormal(const Vector3& v1, const Vector3& v2, const Vector3& v3)
	{
		Vector3 edge1 = v2 - v1;
		Vector3 edge2 = v3 - v1;
		Vector3 normal = Cross(edge1, edge2);
		return normal;
	}

#pragma endregion


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

	constexpr float Determinant(const Matrix3& m)
	{
		float det = 0.0f;
		det = (m._11 * (m._22 * m._33 - m._23 * m._32));
		det -= (m._12 * (m._21 * m._33 - m._23 * m._31));
		det += (m._13 * (m._21 * m._32 - m._22 * m._31));
		return det;
	}

	constexpr float Determinant(const Matrix4& m)
	{
		const float cofactor1 = m._11 * ((m._22 * ((m._33 * m._44) - (m._34 * m._43))) - ((m._23 * ((m._32 * m._44) - (m._34 * m._42)))) + ((m._24 * ((m._32 * m._43) - (m._33 * m._42)))));
		const float cofactor2 = m._12 * ((m._21 * ((m._33 * m._44) - (m._34 * m._43))) - ((m._23 * ((m._31 * m._44) - (m._34 * m._41)))) + ((m._24 * ((m._31 * m._43) - (m._33 * m._41)))));
		const float cofactor3 = m._13 * ((m._21 * ((m._32 * m._44) - (m._34 * m._42))) - ((m._22 * ((m._31 * m._44) - (m._34 * m._41)))) + ((m._24 * ((m._31 * m._42) - (m._32 * m._41)))));
		const float cofactor4 = m._14 * ((m._21 * ((m._32 * m._43) - (m._33 * m._42))) - ((m._22 * ((m._31 * m._43) - (m._33 * m._41)))) + ((m._23 * ((m._31 * m._42) - (m._32 * m._41)))));
		float det = cofactor1 - cofactor2 + cofactor3 - cofactor4;
		return det;
	}

	inline Matrix3 Inverse(const Matrix3& m)
	{
		const float det = Determinant(m);
		const float inverseDet = 1.0f / det;
		Matrix3 matrix{};
		return matrix.Adjoint(m) * inverseDet;
	}

	inline Matrix4 Inverse(const Matrix4& m)
	{
		const float det = Determinant(m);
		const float inverseDet = 1.0f / det;
		Matrix4 matrix{};
		return matrix.Adjoint(m) * inverseDet;
	}

	constexpr Vector2 TransformCoord(const Vector2& v, const Matrix3& m)
	{
		return { v.x * m._11 + v.y * m._21 + m._31,
				 v.x * m._12 + v.y * m._22 + m._32 };
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

	constexpr Vector2 TransformNormal(const Vector2& v, const Matrix3& m)
	{
		Vector2 vec;
		vec.x = (v.x * m._11) + (v.y * m._21);
		vec.y = (v.x * m._12) + (v.y * m._22);
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
		return { matrix._41, matrix._42, matrix._43 };
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

	constexpr Vector3 GetLook(const Matrix4& m)
	{
		return Vector3{ m._14, m._24, m._34 };
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
		OMEGAASSERT(length != 0.0f, "[Quaternion] Length cannot be zero.");
		if (length == 1.0f)
		{
			return q;
		}
		const float invNorm = 1.0f / length;
		return { q * invNorm };
	}

	inline Quaternion LerpUnclamped(const Quaternion& from, const Quaternion& to, float time)
	{
		Quaternion quaternion;
		if (Dot(from, to) >= 0.0f)
		{
			quaternion = from * (1.0f - time) + to * time;
		}
		else
		{
			quaternion = from * (1.0f - time) - to * time;
		}
		return Normalize(quaternion);
	}

	//Linear Interpolations
	inline Quaternion Lerp(const Quaternion& from, const Quaternion& to, float time)
	{
		// bck
		// return (from * (1.0f - time) + (to * time));
		if (time < 0.f) return Normalize(from);
		else if (time > 1.f) return Normalize(to);
		return LerpUnclamped(from, to, time);
	}

	/// <summary>
	/// Spherical Linear Interpolation 
	/// </summary>
	/// <param name="from"></param>
	/// <param name="to"></param>
	/// <param name="time"></param>
	/// <returns></returns>
	Quaternion SlerpUnclamped(const Quaternion& from, const Quaternion& to, float time);

	//Spherical Linear Interpolations
	Quaternion Slerp(const Quaternion& from, const Quaternion& to, float time);

#pragma endregion

#pragma region Geometric Helpers

	bool Intersect(const Ray& ray, const Plane& plane, float& distance);
	bool IsContained(const Vector3& point, const AABB& aabb);
	bool IsContained(const Vector3& point, const OBB& obb);
	bool GetContactPoint(const Ray& ray, const OBB& obb, Vector3& point, Vector3& normal);

	bool PointInRect(const Vector2& point, const Rect& rect);
	bool PointInCircle(const Vector2& point, const Circle& circle);

	bool Intersect(const LineSegment& a, const LineSegment& b);
	bool Intersect(const Circle& c0, const Circle& c1);
	bool Intersect(const Rect& r0, const Rect& r1);

	bool Intersect(const Circle& c, const LineSegment& l, Vector2* closestPoint = nullptr);
	bool Intersect(const LineSegment& l, const Circle& c);

	bool Intersect(const Circle& c, const Rect& r);
	bool Intersect(const Rect& r, const Circle& c);

#pragma endregion

}