#include "Precompiled.h"
#include "EngineMath.h"

using namespace Omega::Math;

const Vector2 Vector2::Zero{ 0.0f, 0.0f };
const Vector2 Vector2::One{ 1.0f, 1.0f };
const Vector2 Vector2::XAxis{ 1.0f, 0.0f };
const Vector2 Vector2::YAxis{ 0.0f, 1.0f };

const Vector3 Vector3::Zero{ 0.0f };
const Vector3 Vector3::One{ 1.0f };
const Vector3 Vector3::XAxis{ 1.0f, 0.0f,0.0f };
const Vector3 Vector3::YAxis{ 0.0f, 1.0f,0.0f };
const Vector3 Vector3::ZAxis{ 0.0f, 0.0f,1.0f };

const Matrix4 Matrix4::Identity{ 1.0f, 0.0f, 0.0f, 0.0f,
								 0.0f, 1.0f, 0.0f, 0.0f,
								 0.0f, 0.0f, 1.0f, 0.0f,
								 0.0f, 0.0f, 0.0f, 1.0f };

const Quaternion Quaternion::Zero{ 0.0f , 0.0f, 0.0f ,0.0f };
const Quaternion Quaternion::Identity{ 0.0f , 0.0f, 0.0f ,1.0f };


Matrix4 Matrix4::RotationAxis(const Vector3& axis, float rad)
{
	const float cos = cosf(rad);
	const float sin = sinf(rad);
	const float oneMinusCos = (1.0f - cos);
	Matrix4 rot = Identity;
	Vector3 axisNormalied = Normalize(axis);

	rot._11 = (axisNormalied.x * axisNormalied.x) * oneMinusCos + cos;
	rot._12 = (axisNormalied.x * axisNormalied.y) * oneMinusCos + (axisNormalied.z * sin);
	rot._13 = (axisNormalied.x * axisNormalied.z) * oneMinusCos - (axisNormalied.y * sin);

	rot._21 = (axisNormalied.y * axisNormalied.x) * oneMinusCos - (axisNormalied.z * sin);
	rot._22 = (axisNormalied.y * axisNormalied.y) * oneMinusCos + cos;
	rot._23 = (axisNormalied.y * axisNormalied.z) * oneMinusCos + (axisNormalied.x * sin);

	rot._31 = (axisNormalied.z * axisNormalied.x) * oneMinusCos + (axisNormalied.y * sin);
	rot._32 = (axisNormalied.z * axisNormalied.y) * oneMinusCos - (axisNormalied.x * sin);
	rot._33 = (axisNormalied.z * axisNormalied.z) * oneMinusCos + cos;
	return rot;
}

Matrix4 Matrix4::RotationQuaternion(const Quaternion& q)
{
	return
	{
		1.0f - (2.0f * q.y * q.y) - (2.0f * q.z * q.z),
		(2.0f * q.x * q.y) + (2.0f * q.z * q.w),
		(2.0f * q.x * q.z) - (2.0f * q.y * q.w),
		0.0f,

		(2.0f * q.x * q.y) - (2.0f * q.w * q.z),
		1.0f - (2.0f * q.x * q.x) - (2.0f * q.z * q.z),
		(2.0f * q.y * q.z) + (2.0f * q.w * q.x),
		0.0f,

		(2.0f * q.x * q.z) + (2.0f * q.w * q.y),
		(2.0f * q.y * q.z) - (2.0f * q.w * q.x),
		1.0f - (2.0f * q.x * q.x) - (2.0f * q.y * q.y),
		0.0f,

		0.0f, 0.0f, 0.0f, 1.0f
	};
}

Quaternion Quaternion::RotationAxis(const Vector3& axis, float rad)
{
	const float halfAngle = rad * 0.5f;
	const float s = sinf(halfAngle);
	const Vector3 normalize = Normalize(axis);
	return { normalize.x * s, normalize.y * s, normalize.z * s, cosf(halfAngle) };
}

Quaternion Quaternion::RotationMatrix(const Matrix4& m)
{
	/*
	Reference:
	https://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/index.htm
	*/

	Matrix4 matrix = Transpose(m);

	const float trace = matrix._11 + matrix._22 + matrix._33;
	if (trace > 0.0f)
	{
		const float s = 0.5f / sqrtf(trace + 1.0f);
		return { (matrix._32 - matrix._23) * s,
				(matrix._13 - matrix._31) * s,
				(matrix._21 - matrix._12) * s,
				0.25f / s };
	}
	else
	{
		if ((matrix._11 > matrix._22) && (matrix._11 > matrix._33))
		{
			const float s = 2.0f * sqrtf(1.0f + matrix._11 - matrix._22 - matrix._33);
			return { 0.25f * s,
					(matrix._12 + matrix._21) / s,
					(matrix._13 + matrix._31) / s,
					(matrix._32 - matrix._23) / s };
		}
		else if (matrix._22 > matrix._33)
		{
			const float s = 2.0f * sqrtf(1.0f + matrix._22 - matrix._11 - matrix._33);
			return { (matrix._12 + matrix._21) / s,
					 0.25f * s,
					(matrix._23 + matrix._32) / s,
					(matrix._13 - matrix._31) / s };
		}
		else
		{
			const float s = 2.0f * sqrtf(1.0f + matrix._33 - matrix._11 - matrix._22);
			return { (matrix._13 + matrix._31) / s,
					 (matrix._23 + matrix._32) / s,
					 0.25f * s,
					(matrix._21 - matrix._12) / s };
		}

	}
}

Quaternion Quaternion::RotationLook(const Vector3& direction, const Vector3& up)
{
	Vector3 forward = Normalize(direction);
	Vector3 orth = Normalize(Cross(up, forward)); // real up
	Vector3 right = Cross(forward, orth);
	Matrix4 m
	{
		orth.x,	orth.y, orth.z, 0.0f,
		right.x, right.y, right.z, 0.0f,
		forward.x, forward.y, forward.z, 0.0f,
		0.0f,0
	};
	return RotationMatrix(m);
}

Quaternion Quaternion::RotationFromTo(Vector3 from, Vector3 to)
{
	from = Normalize(from);
	to = Normalize(to);

	float cosTheta = Dot(from, to);
	Vector3 rotationAxis;
	if (cosTheta >= 1.0f) // If dot == 1, vectors are the same
	{
		return Quaternion::Identity;
	}
	else if (cosTheta < -1.0f + 0.001f)
	{
		// special case when vectors in opposite directions:
		// there is no "ideal" rotation axis
		// So guess one; any will do as long as it's perpendicular to start
		rotationAxis = Cross(Vector3::ZAxis, from);

		if (Magnitude(rotationAxis) < 0.01)
		{
			// bad luck, they were parallel, try again!
			rotationAxis = Cross(Vector3::XAxis, from);
		}
		rotationAxis = Normalize(rotationAxis);
		return Quaternion::RotationAxis(rotationAxis, 180.0f);
	}

	rotationAxis = Cross(from, to);

	const float s = sqrtf((1.0f + cosTheta) * 2.0f);
	const float invs = 1.0f / s;

	return { rotationAxis.x * invs,
			rotationAxis.y * invs,
			rotationAxis.z * invs,
			s * 0.5f };
}

Quaternion Omega::Math::Slerp(Quaternion& from, Quaternion& to, float time)
{
	/*
	//	Reference:
	//	https://www.euclideanspace.com/maths/algebra/realNormedAlgebra/quaternions/slerp/index.htm
	//	*/
	float angle = Dot(from, to);

	/* If the dot product is negative, slerp won't take
	 the shorter path. Note that v1 and -v1 are equivalent when
	 the negation is applied to all four components. Fix by
	 reversing one quaternion.*/
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

bool Omega::Math::Intersect(const Ray& ray, const Plane& plane, float& distance)
{
	const float orgDotN = Dot(ray.origin, plane.n);
	const float dirDotN = Dot(ray.direction, plane.n);

	// Check if ray is parallel to the plane
	if (Abs(dirDotN) < 0.0001f)
	{
		if (Abs(orgDotN - plane.d) < 0.0001f)
		{
			distance = 0.0f;
			return true;
		}
		else
		{
			return false;
		}
	}

	// Compute distance
	distance = (plane.d - orgDotN) / dirDotN;
	return true;

}

bool Omega::Math::IsContained(const Vector3& point, const AABB& aabb)
{
	auto min = aabb.Min();
	auto max = aabb.Max();
	if ((point.x < min.x) || (point.x > max.x) ||
		(point.y < min.y) || (point.y > max.y) ||
		(point.z < min.z) || (point.y > max.z))
	{
		return false;
	}
	return true;
}

bool Omega::Math::IsContained(const Vector3& point, const OBB& obb)
{
	// Compute the world-to-local matrices
	Math::Matrix4 matTrans = Math::Matrix4::Translation(obb.center);
	Math::Matrix4 matRot = Math::Matrix4::RotationQuaternion(obb.rot);
	Math::Matrix4 matScale = Math::Matrix4::Scaling(obb.extend);
	Math::Matrix4 toWorld = matScale * matRot * matTrans;
	Math::Matrix4 toLocal = Inverse(toWorld);

	// Transform the point into the OBB's local space
	Vector3 localPoint = TransformCoord(point, toLocal);
	
	// Test against local AABB
	return IsContained(localPoint, AABB{ Vector3::Zero, Vector3::One });
}

bool Omega::Math::GetContactPoint(const Ray& ray, const OBB& obb, Vector3& point, Vector3& normal)
{
	// Compute the local-to-world/world-to-local matrices
	Matrix4 matTrans = Matrix4::Translation(obb.center);
	Matrix4 matRot = Matrix4::RotationQuaternion(obb.rot);
	Matrix4 matWorld = matRot * matTrans;
	Matrix4 matWorldInv = Inverse(matWorld);

	// Transform the ray into the OBB's local space
	Vector3 org = TransformCoord(ray.origin, matWorldInv);
	Vector3 dir = TransformNormal(ray.direction, matWorldInv);
	Ray localRay{ org, dir };

	Plane planes[] =
	{
		{ {  0.0f,  0.0f, -1.0f }, obb.extend.z },
		{ {  0.0f,  0.0f,  1.0f }, obb.extend.z },
		{ {  0.0f, -1.0f,  0.0f }, obb.extend.y },
		{ {  0.0f,  1.0f,  0.0f }, obb.extend.y },
		{ { -1.0f,  0.0f,  0.0f }, obb.extend.x },
		{ {  1.0f,  0.0f,  0.0f }, obb.extend.x }
	};

	uint32_t numIntersections = 0;
	for (uint32_t i = 0; i < 6; ++i)
	{
		const float d = Dot(org, planes[i].n);
		if (d > planes[i].d)
		{
			float distance = 0.0f;
			if (Intersect(localRay, planes[i], distance) && distance >= 0.0f)
			{
				Vector3 pt = org + (dir * distance);
				if (abs(pt.x) <= obb.extend.x + 0.01f &&
					abs(pt.y) <= obb.extend.y + 0.01f &&
					abs(pt.z) <= obb.extend.z + 0.01f)
				{
					point = pt;
					normal = planes[i].n;
					++numIntersections;
				}
			}
		}
	}

	if (numIntersections == 0)
	{
		return false;
	}

	point = TransformCoord(point, matWorld);
	normal = TransformNormal(normal, matWorld);
	return true;

}