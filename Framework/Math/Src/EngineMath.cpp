#include "Precompiled.h"
#include "EngineMath.h"

using namespace Omega::Math;

constexpr Vector2 Vector2::Zero{ 0.0f, 0.0f };
constexpr Vector2 Vector2::One{ 1.0f, 1.0f };
constexpr Vector2 Vector2::XAxis{ 1.0f, 0.0f };
constexpr Vector2 Vector2::YAxis{ 0.0f, 1.0f };

constexpr Vector3 Vector3::Zero{ 0.0f };
constexpr Vector3 Vector3::One{ 1.0f };
constexpr Vector3 Vector3::XAxis{ 1.0f, 0.0f,0.0f };
constexpr Vector3 Vector3::YAxis{ 0.0f, 1.0f,0.0f };
constexpr Vector3 Vector3::ZAxis{ 0.0f, 0.0f,1.0f };

constexpr Matrix3 Matrix3::Identity{ 1.0f, 0.0f, 0.0f,
								 0.0f, 1.0f, 0.0f,
								 0.0f, 0.0f, 1.0f };
constexpr Matrix3 Matrix3::Zero{ 0.0f };

constexpr Matrix4 Matrix4::Identity{ 1.0f, 0.0f, 0.0f, 0.0f,
								 0.0f, 1.0f, 0.0f, 0.0f,
								 0.0f, 0.0f, 1.0f, 0.0f,
								 0.0f, 0.0f, 0.0f, 1.0f };
constexpr Matrix4 Matrix4::Zero{ 0.0f };

constexpr Quaternion Quaternion::Zero{ 0.0f , 0.0f, 0.0f ,0.0f };
constexpr Quaternion Quaternion::Identity{ 0.0f , 0.0f, 0.0f ,1.0f };


Matrix4 Matrix4::RotationAxis(const Vector3& axis, float rad)
{
	const float cos = cosf(rad);
	const float sin = sinf(rad);
	const float oneMinusCos = (1.0f - cos);
	Matrix4 rot = Identity;
	const Vector3 axisNormalied = Normalize(axis);

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

Matrix4 Matrix4::RotationQuaternion(const Quaternion& q) noexcept
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

Matrix4 Matrix4::Transform(const Vector3& translation, const Quaternion& rotation, const Vector3& scale) noexcept
{
	Math::Matrix4 transform = Math::Matrix4::RotationQuaternion(rotation);
	transform._11 *= scale.x;
	transform._22 *= scale.y;
	transform._33 *= scale.z;
	transform._41 = translation.x;
	transform._42 = translation.y;
	transform._43 = translation.z;
	return transform;
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

	const Matrix4 matrix = Transpose(m);

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
	const Vector3 forward = Normalize(direction);
	const Vector3 orth = Normalize(Cross(up, forward)); // real up
	const Vector3 right = Cross(forward, orth);
	const Matrix4 m
	{
		orth.x,	orth.y, orth.z, 0.0f,
		right.x, right.y, right.z, 0.0f,
		forward.x, forward.y, forward.z, 0.0f,
		0.0f, 0.0f
	};
	return RotationMatrix(m);
}

Quaternion Quaternion::RotationFromTo(const Vector3& from, const Vector3& to)
{
	const Vector3 localFrom = Normalize(from);
	const Vector3 localTo = Normalize(to);

	const float cosTheta = Dot(localFrom, localTo);
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
		rotationAxis = Cross(Vector3::ZAxis, localFrom);

		if (Magnitude(rotationAxis) < 0.01f)
		{
			// bad luck, they were parallel, try again!
			rotationAxis = Cross(Vector3::XAxis, localFrom);
		}
		rotationAxis = Normalize(rotationAxis);
		return Quaternion::RotationAxis(rotationAxis, 180.0f);
	}

	rotationAxis = Cross(localFrom, localTo);

	const float s = sqrtf((1.0f + cosTheta) * 2.0f);
	const float invs = 1.0f / s;

	return { rotationAxis.x * invs,
			rotationAxis.y * invs,
			rotationAxis.z * invs,
			s * 0.5f };
}

Quaternion Omega::Math::SlerpUnclamped(const Quaternion& from, const Quaternion& to, float time)
{
	float n1 = 0.0f;
	float n2 = 0.0f;
	float n3 = Dot(from, to);
	bool flag = false;

	if (n3 < 0.f)
	{
		flag = true;
		n3 = -n3;
	}

	if (n3 > 0.999999f)
	{
		n2 = 1.f - time;
		n1 = flag ? -time : time;
	}
	else
	{
		const float n4 = acosf(n3);
		const float n5 = 1.f / sinf(n4);
		n2 = sinf((1.f - time) * n4) * n5;
		n1 = flag ? -sinf(time * n4) * n5 : sinf(time * n4) * n5;
	}
	const Quaternion q = (from * n2) + (to * n1);
	return Normalize(q);
}


Quaternion Omega::Math::Slerp(const Quaternion& from, const Quaternion& to, float time)
{
	///*
	////	Reference:
	////	https://www.euclideanspace.com/maths/algebra/realNormedAlgebra/quaternions/slerp/index.htm
	////	*/
	//float angle = Dot(from, to);

	///* If the dot product is negative, slerp won't take
	// the shorter path. Note that v1 and -v1 are equivalent when
	// the negation is applied to all four components. Fix by
	// reversing one quaternion.*/
	//if (angle < 0.0f)
	//{
	//	to = -to;
	//	angle = -angle;
	//}
	//else if (angle > 0.9995f)
	//{
	//	// bck
	//	//return Normalize(Lerp(from, to, time));
	//	return Lerp(from, to, time);
	//}

	//// Since dot is in range [0, angleThreshold], acos is safe
	//const float theta = acosf(angle);        // theta_0 = angle between input vectors
	//const float inverseSinTheta = 1.0f / sinf(theta);
	//const float scale = sinf(theta * (1.0f - time)) * inverseSinTheta;
	//const float inverseScale = sinf(theta * time) * inverseSinTheta;
	//return (from * scale) + (to * inverseScale);

	if (time < 0.f) return Normalize(from);
	else if (time > 1.f) return Normalize(to);
	return SlerpUnclamped(from, to, time);
}

bool Omega::Math::Intersect(const Ray& ray, const Plane& plane, float& distance)
{
	const float orgDotN = Dot(ray.origin, plane.n);
	const float dirDotN = Dot(ray.direction, plane.n);

	// Check if ray is parallel to the plane
	
	if (Abs(dirDotN) < Constants::Epsilon) //0.0001f
	{
		if (Abs(orgDotN - plane.d) < Constants::Epsilon)
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
	const auto min = aabb.Min();
	const auto max = aabb.Max();
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
	//const Math::Matrix4 toLocal = WorldToLocalMatrix(obb.center, obb.rot, obb.extend);

	// Compute the world-to-local matrices
	const Math::Matrix4 matTrans = Math::Matrix4::Translation(obb.center);
	const Math::Matrix4 matRotation = Math::Matrix4::RotationQuaternion(obb.rot);
	Math::Matrix4 matScale = Math::Matrix4::Scaling(obb.extend);
	const Math::Matrix4 toWorld = matScale * matRotation * matTrans;
	const Math::Matrix4 toLocal = Inverse(toWorld);

	// Transform the point into the OBB's local space
	const Vector3 localPoint = TransformCoord(point, toLocal);

	// Test against local AABB
	return IsContained(localPoint, AABB{ Vector3::Zero, Vector3::One });
}

bool Omega::Math::GetContactPoint(const Ray& ray, const OBB& obb, Vector3& point, Vector3& normal)
{
	// Compute the local-to-world/world-to-local matrices
	// Compute the local-to-world/world-to-local matrices
	const Matrix4 matTrans = Matrix4::Translation(obb.center);
	Matrix4 matRot = Matrix4::RotationQuaternion(obb.rot);
	const Matrix4 matWorld = matRot * matTrans;
	const Matrix4 matWorldInv = Inverse(matWorld);

	//const Math::Matrix4 toLocal = WorldToLocalMatrix(obb.center, obb.rot);

	// Transform the ray into the OBB's local space
	const Vector3 org = TransformCoord(ray.origin, matWorldInv);
	const Vector3 dir = TransformNormal(ray.direction, matWorldInv);
	const Ray localRay{ org, dir };

	std::vector<Plane> planes = {
		{Vector3{ 0.0f, 0.0f, -1.0f }, obb.extend.z},
		{Vector3{ 0.0f, 0.0f, 1.0f }, obb.extend.z},
		{Vector3{ 0.0f, -1.0f, 0.0f }, obb.extend.y},
		{Vector3{ 0.0f, 1.0f, 0.0f }, obb.extend.y},
		{Vector3{ -1.0f, 0.0f, 0.0f }, obb.extend.x},
		{Vector3{ 1.0f, 0.0f, 0.0f }, obb.extend.x}
	};


	uint32_t numIntersections = 0;
	for (const Plane& plane : planes)
	{
		if (const float d = Dot(org, plane.n);
			d > plane.d)
		{
			float distance = 0.0f;
			if (Intersect(localRay, plane, distance) && distance >= 0.0f)
			{
				Vector3 pt = org + (dir * distance);
				if (Abs(pt.x) <= obb.extend.x + 0.01f &&
					Abs(pt.y) <= obb.extend.y + 0.01f &&
					Abs(pt.z) <= obb.extend.z + 0.01f)
				{
					point = pt;
					normal = plane.n;
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

bool Omega::Math::PointInRect(const Vector2& point, const Rect& rect) noexcept
{
	return !(point.x < rect.left || point.x > rect.right || point.y < rect.top || point.y > rect.bottom);
}

bool Omega::Math::PointInCircle(const Vector2& point, const Circle& circle)
{
	const float distance = DistanceSqr(point, circle.center);
	return distance < circle.radius * circle.radius;
}

bool Omega::Math::Intersect(const LineSegment& a, const LineSegment& b) noexcept
{
	float ua = ((a.to.x - a.from.x) * (b.from.y - a.from.y)) - ((a.to.y - a.from.y) * (b.from.x - a.from.x));
	float ub = ((b.to.x - b.from.x) * (b.from.y - a.from.y)) - ((b.to.y - b.from.y) * (b.from.x - a.from.x));
	const float denom = ((a.to.y - a.from.y) * (b.to.x - b.from.x)) - ((a.to.x - a.from.x) * (b.to.y - b.from.y));

	// First check for special cases
	if (denom == 0.0f)
	{
		if (ua == 0.0f && ub == 0.0f)
		{
			// The line segments are the same
			return true;
		}
		else
		{
			// The line segments are parallel
			return false;
		}
	}

	ua /= denom;
	ub /= denom;

	if (ua < 0.0f || ua > 1.0f || ub < 0.0f || ub > 1.0f)
	{
		return false;
	}

	return true;
}
bool Omega::Math::Intersect(const LineSegment& a, const LineSegment& b, Vector2& intersectPoint)
{
	float ua = ((a.to.x - a.from.x) * (b.from.y - a.from.y)) - ((a.to.y - a.from.y) * (b.from.x - a.from.x));
	float ub = ((b.to.x - b.from.x) * (b.from.y - a.from.y)) - ((b.to.y - b.from.y) * (b.from.x - a.from.x));
	const float denom = ((a.to.y - a.from.y) * (b.to.x - b.from.x)) - ((a.to.x - a.from.x) * (b.to.y - b.from.y));

	// First check for special cases
	if (denom == 0.0f)
	{
		if (ua == 0.0f && ub == 0.0f)
		{
			// The line segments are the same
			return true;
		}
		else
		{
			// The line segments are parallel
			return false;
		}
	}

	ua /= denom;
	ub /= denom;

	if (ua < 0.0f || ua > 1.0f || ub < 0.0f || ub > 1.0f)
	{
		return false;
	}
	intersectPoint = b.from + (b.from - b.to) * -ua;
	return true;
}

bool Omega::Math::Intersect(const Vector2& a, const Vector2& b, const Vector2& c, const Vector2& d, float& dist, Vector2& point)
{
	const float rTop = (a.y - c.y) * (d.x - c.x) - (a.x - c.x) * (d.y - c.y);
	const float rBot = (b.x - a.x) * (d.y - c.y) - (b.y - a.y) * (d.x - c.x);

	const float sTop = (a.y - c.y) * (b.x - a.x) - (a.x - c.x) * (b.y - a.y);
	const float sBot = (b.x - a.x) * (d.y - c.y) - (b.y - a.y) * (d.x - c.x);

	if ((rBot == 0.0f) || (sBot == 0.0f))
	{
		//lines are parallel
		return false;
	}

	const float r = rTop / rBot;
	const float s = sTop / sBot;

	if ((r > 0.0f) && (r < 1.0f) && (s > 0.0f) && (s < 1.0f))
	{
		dist = Distance(a, b) * r;
		point = a + r * (b - a);
		return true;
	}

	dist = 0.0f;
	return false;
}

bool Omega::Math::Intersect(const Circle& c0, const Circle& c1)
{
	const float combinedRadius = c0.radius + c1.radius;
	const float distanceSquared = DistanceSqr(c0.center, c1.center);
	return distanceSquared < combinedRadius * combinedRadius;
}

bool Omega::Math::Intersect(const Rect& r0, const Rect& r1) noexcept
{
	return !(r0.right < r1.left || r0.left > r1.right || r0.bottom < r1.top || r0.top > r1.bottom);
}

bool Omega::Math::Intersect(const Circle& c, const LineSegment& l, Vector2* closestPoint)
{
	const Vector2 startToCenter = c.center - l.from;
	const Vector2 startToEnd = l.to - l.from;
	const float len = Magnitude(startToEnd);
	const Vector2 dir = startToEnd / len;

	// Find the closest point to the line segment
	Vector2 point;
	if (const float projection = Dot(startToCenter, dir);
		projection > len)
	{
		point = l.to;
	}
	else if (projection < 0.0f)
	{
		point = l.from;
	}
	else
	{
		point = l.from + (dir * projection);
	}

	// Check if the closest point is within the circle
	if (!PointInCircle(point, c))
	{
		return false;
	}

	if (closestPoint)
	{
		*closestPoint = point;
	}

	return true;
}

bool Omega::Math::Intersect(const LineSegment& l, const Circle& c)
{
	return Intersect(c, l);
}

bool Omega::Math::Intersect(const Circle& c, const Rect& r)
{
	return Intersect(r, c);
}

bool Omega::Math::Intersect(const Rect& r, const Circle& c)
{
	Vector2 closestPoint;
	closestPoint.x = Clamp(c.center.x, r.left, r.right);
	closestPoint.y = Clamp(c.center.y, r.top, r.bottom);

	const float distance = Distance(closestPoint, c.center);
	return !(distance > c.radius);
}

bool Omega::Math::Intersect(const LineSegment& line, const Vector2& point)
{
	const float cross = (line.from.x - line.to.x) * (point.y - line.to.y) - (point.x - line.to.x) * (line.from.y - line.to.y);

	// Check if the point lies on the line defined by line
	return Abs(cross) < Constants::Epsilon &&
		point.x >= Min(line.from.x, line.to.x) &&
		point.x <= Max(line.from.x, line.to.x) &&
		point.y >= Min(line.from.y, line.to.y) &&
		point.y <= Max(line.from.y, line.to.y); // Adjust epsilon for comparison precision
}