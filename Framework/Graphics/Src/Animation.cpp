#include "Precompiled.h"
#include "Animation.h"

using namespace Omega::Graphics;
using namespace Omega::Math;

namespace {
	unsigned int BSNextKeyVector3(float time, const Keyframes<Vector3>& position)
	{
		unsigned int left = 0;
		unsigned int right = static_cast<unsigned int>(position.size()) - 1;

		while (left < right)
		{
			const unsigned int mid = left + ((right - left) >> 1);

			if (position[mid].time <= time)
			{
				left = mid + 1;
			}
			else
			{
				right = mid;
			}
		}

		return left;
	}

	unsigned int BSNextKeyQuaternion(float time, const Keyframes<Quaternion>& position)
	{
		unsigned int left = 0;
		unsigned int right = static_cast<unsigned int>(position.size()) - 1;

		while (left < right)
		{
			const unsigned int mid = left + ((right - left) >> 1);

			if (position[mid].time <= time)
			{
				left = mid + 1;
			}
			else
			{
				right = mid;
			}
		}

		return left;
	}
}

Vector3 Animation::GetPositionOptimized(float time) const
{
	if (const size_t size = mPositionKeys.size(); size > 0)
	{
		unsigned int nextKey = BSNextKeyVector3(time, mPositionKeys);
		const unsigned int currentKey = (nextKey > 0) ? nextKey - 1 : 0;

		if (mPositionKeys[nextKey].time == mPositionKeys[currentKey].time)
		{
			return mPositionKeys[currentKey].key;
		}

		const float total_t = mPositionKeys[nextKey].time - mPositionKeys[currentKey].time;
		const float t = (time - mPositionKeys[currentKey].time) / total_t;

		const Vector3& vBegin = mPositionKeys[currentKey].key;
		const Vector3& vEnd = mPositionKeys[nextKey].key;
		return Lerp<Vector3>(vBegin, vEnd, t);
	}

	return Vector3::Zero;
}

Vector3 Animation::GetScaleOptimized(float time) const
{
	if (const size_t size = mScaleKeys.size(); size > 0)
	{
		unsigned int nextKey = BSNextKeyVector3(time, mScaleKeys);
		const unsigned int currentKey = (nextKey > 0) ? nextKey - 1 : 0;

		if (mScaleKeys[nextKey].time == mScaleKeys[currentKey].time)
		{
			return mScaleKeys[currentKey].key;
		}

		const float total_t = mScaleKeys[nextKey].time - mScaleKeys[currentKey].time;
		const float t = (time - mScaleKeys[currentKey].time) / total_t;

		const Vector3& vBegin = mScaleKeys[currentKey].key;
		const Vector3& vEnd = mScaleKeys[nextKey].key;
		return Lerp<Vector3>(vBegin, vEnd, t);
	}

	return Vector3::Zero;
}

Quaternion Animation::GetRotationOptimized(float time) const
{
	if (const size_t size = mRotationKeys.size(); size > 0)
	{
		unsigned int nextKey = BSNextKeyQuaternion(time, mRotationKeys);
		const unsigned int currentKey = (nextKey > 0) ? nextKey - 1 : 0;

		if (mRotationKeys[nextKey].time == mRotationKeys[currentKey].time)
		{
			return mRotationKeys[currentKey].key;
		}

		const float total_t = mRotationKeys[nextKey].time - mRotationKeys[currentKey].time;
		const float t = (time - mRotationKeys[currentKey].time) / total_t;

		const Quaternion& vBegin = mRotationKeys[currentKey].key;
		const Quaternion& vEnd = mRotationKeys[nextKey].key;
		return Slerp(vBegin, vEnd, t);
	}

	return Quaternion::Identity;
}

Matrix4 Animation::GetTransform(float time) const
{
	// Combining
	return Matrix4::Transform(GetPositionOptimized(time), GetRotationOptimized(time), GetScaleOptimized(time));;
}
