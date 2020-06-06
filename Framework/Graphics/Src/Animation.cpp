#include "Precompiled.h"
#include "Animation.h"

using namespace Omega::Graphics;
using namespace Omega::Math;

Vector3 Animation::GetPosition(float time) const
{
	const int size = static_cast<int>(mPositionKeys.size());
	if (size > 0)
	{
		int nextKey = 0;
		for (int i = 0; i < size; ++i)
		{
			nextKey = i;
			if (mPositionKeys[i].time > time)
			{
				break;
			}
		}
		const int currentKey = std::max(0, nextKey - 1);
		const float total_t = (mPositionKeys[nextKey].time - mPositionKeys[currentKey].time);
		const float t = (total_t != 0.0f) ?
			(time - mPositionKeys[currentKey].time) / total_t :
			(time - mPositionKeys[currentKey].time);

		Vector3 vBegin = mPositionKeys[currentKey].key;
		Vector3 vEnd = mPositionKeys[nextKey].key;
		return Lerp<Vector3>(vBegin, vEnd, t);
	}
	return Vector3::Zero;
}

Quaternion Animation::GetRotation(float time) const
{
	const int size = static_cast<int>(mRotationKeys.size());
	if (size > 0)
	{
		int nextKey = 0;
		for (int i = 0; i < size; ++i)
		{
			nextKey = i;
			if (mRotationKeys[i].time > time)
			{
				break;
			}
		}
		const int currentKey = std::max(0, nextKey - 1);
		const float total_t = mRotationKeys[nextKey].time - mRotationKeys[currentKey].time;
		const float t = (total_t != 0.0f) ?
			(time - mRotationKeys[currentKey].time) / total_t :
			(time - mRotationKeys[currentKey].time);

		Quaternion qBegin = mRotationKeys[currentKey].key;
		Quaternion qEnd = mRotationKeys[nextKey].key;
		return Slerp(qBegin, qEnd, t);
	}
	return Quaternion::Identity;
}

Vector3 Animation::GetScale(float time) const
{
	const int size = static_cast<int>(mScaleKeys.size());
	if (size > 0)
	{
		int nextKey = 0;
		for (int i = 0; i < size; ++i)
		{
			nextKey = i;
			if (mScaleKeys[i].time > time)
			{
				break;
			}
		}
		const int currentKey = std::max(0, nextKey - 1);
		const float total_t = mScaleKeys[nextKey].time - mScaleKeys[currentKey].time;
		const float t = (total_t != 0.0f) ?
			(time - mScaleKeys[currentKey].time) / total_t :
			(time - mScaleKeys[currentKey].time);

		Vector3 vBegin = mScaleKeys[currentKey].key;
		Vector3 vEnd = mScaleKeys[nextKey].key;
		return Lerp<Vector3>(vBegin, vEnd, t);
	}
	return Vector3::Zero;
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
	return matrixScale * matrixRot * matrixPos;
}
