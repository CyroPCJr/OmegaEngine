#include "Precompiled.h"
#include "Animation.h"

using namespace Omega::Graphics;
using namespace Omega::Math;

Vector3 Animation::GetPosition(float time) const
{
	const int size = static_cast<int>(mPositionKeys.size());
	if (size > 0)
	{
		int currentKey = 0;
		for (int i = 0; i < size; ++i)
		{
			currentKey = i;
			if (mPositionKeys[i].time > time)
			{
				break;
			}
		}
		const int nextKey = (currentKey + 1) % size;
		const float total_t = (mPositionKeys[nextKey].time - mPositionKeys[currentKey].time);
		const float t = (total_t != 0.0) ?
			(time - mPositionKeys[currentKey].time) / total_t :
			0.0f;

		Vector3 vBegin = mPositionKeys[currentKey].key;
		Vector3 vEnd = mPositionKeys[nextKey].key;
		return Lerp<Vector3>(vBegin, vEnd, t);
	}
	else
	{
		return Vector3::Zero;
	}
}

Quaternion Animation::GetRotation(float time) const
{
	const int size = static_cast<int>(mRotationKeys.size());
	if (size > 0)
	{
		int currentKey = 0;
		for (int i = 0; i < size; ++i)
		{
			currentKey = i;
			if (mRotationKeys[i].time > time)
			{
				break;
			}
		}
		const int nextKey = (currentKey + 1) % size;
		const float total_t = mRotationKeys[nextKey].time - mRotationKeys[currentKey].time;
		const float t = (total_t != 0.0) ?
			(time - mRotationKeys[currentKey].time) / total_t :
			0.0f;

		Quaternion qBegin = mRotationKeys[currentKey].key;
		Quaternion qEnd = mRotationKeys[currentKey].key;
		return Slerp(qBegin, qEnd, t);
	}
	else
	{
		return Quaternion::Zero;
	}
}

Vector3 Animation::GetScale(float time) const
{
	const int size = static_cast<int>(mScaleKeys.size());
	if (size > 0)
	{
		int currentKey = 0;
		for (int i = 0; i < size; ++i)
		{
			currentKey = i;
			if (mScaleKeys[i].time > time)
			{
				break;
			}
		}
		const int nextKey = (currentKey + 1) % size;
		const float total_t = mScaleKeys[nextKey].time - mScaleKeys[currentKey].time;
		const float t = (total_t != 0.0) ?
			(time - mScaleKeys[currentKey].time) / total_t :
			0.0f;

		Vector3 vBegin = mScaleKeys[currentKey].key;
		Vector3 vEnd = mScaleKeys[nextKey].key;
		return Lerp<Vector3>(vBegin, vEnd, t);
	}
	else
	{
		return Vector3::Zero;
	}
}

Matrix4 Animation::GetTransform(float time) const
{
	//Rotation 
	Matrix4 matrixRot = Matrix4::RotationQuaternion(GetRotation(time));
	// Position
	Matrix4 matrixPos = Matrix4::Translation(GetPosition(time));
	// Scaling
	Matrix4 matrixScale = Matrix4::Scaling(GetScale(time));

	// Combining
	return matrixRot * matrixPos * matrixScale;
}
