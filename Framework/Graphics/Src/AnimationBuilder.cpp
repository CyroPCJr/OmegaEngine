#include "Precompiled.h"
#include "AnimationBuilder.h"

using namespace Omega::Graphics;
using namespace Omega::Math;

AnimationBuilder& Omega::Graphics::AnimationBuilder::SetTime(float time)
{
	mTime = time;
	return *this;
}

AnimationBuilder& AnimationBuilder::AddPositionKey(const Vector3& position)
{
	mAnimation.mPositionKeys.push_back({ position, mTime });
	return *this;
}

AnimationBuilder& AnimationBuilder::AddRotationKey(const Quaternion& rotation)
{
	mAnimation.mRotationKeys.push_back({ rotation, mTime });
	return *this;
}

AnimationBuilder& AnimationBuilder::AddScaleKey(const Vector3& scale)
{
	mAnimation.mScaleKeys.push_back({ scale , mTime });
	return *this;
}

Matrix4 AnimationBuilder::GetAnimation(float time)
{
	return mAnimation.GetTransform(time);
}

