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
	Vector3 test = Normalize(axis);

	// MY code
	/*rot._11 = (test.x * test.x) * oneMinusCos + cos;
	rot._12 = (test.x * test.y) * oneMinusCos - (test.z * sin);
	rot._13 = (test.x * test.z) * oneMinusCos + (test.y * sin);

	rot._21 = (test.y * test.x) * oneMinusCos + (test.z * sin);
	rot._22 = (test.y * test.y) * oneMinusCos + cos;
	rot._23 = (test.y * test.z) * oneMinusCos - (test.x * sin);

	rot._31 = (test.z * test.x) * oneMinusCos - (test.y * sin);
	rot._32 = (test.z * test.y) * oneMinusCos + (test.x * sin);
	rot._33 = (test.z * test.z) * oneMinusCos + cos;*/

	//TEST CODE
	rot._11 = (test.x * test.x) * oneMinusCos + cos;
	rot._12 = (test.x * test.y) * oneMinusCos + (test.z * sin);
	rot._13 = (test.x * test.z) * oneMinusCos - (test.y * sin);

	rot._21 = (test.y * test.x) * oneMinusCos - (test.z * sin);
	rot._22 = (test.y * test.y) * oneMinusCos + cos;
	rot._23 = (test.y * test.z) * oneMinusCos + (test.x * sin);

	rot._31 = (test.z * test.x) * oneMinusCos + (test.y * sin);
	rot._32 = (test.z * test.y) * oneMinusCos - (test.x * sin);
	rot._33 = (test.z * test.z) * oneMinusCos + cos;

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

Quaternion Quaternion::RotationMatrix(const Matrix4& matrix)
{
	/*
	Reference:
	https://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/index.htm
	*/

	const float trace = matrix._11 + matrix._22 + matrix._33 + 1.0f;
	if (trace > 0.0f)
	{
		const float s = 0.5f / sqrtf(trace);
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
					(matrix._12 - matrix._21) / s };
		}
	}
}


Quaternion Quaternion::RotationLook(Vector3 direction, Vector3 up)
{
	Vector3 z = Normalize(direction);
	Vector3 x = Normalize(Cross(up, z));
	Vector3 y = Normalize(Cross(z, x));

	Matrix4 mat{ x.x, x.y, x.z, 0.0f,
				y.x, y.y, y.z, 0.0f,
				z.x, z.y, z.z, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f
	};

	return RotationMatrix(mat);
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