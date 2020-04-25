#include "Precompiled.h"
#include "AnimationBuilder.h"

using namespace Omega::Graphics;
using namespace Omega::Math;

AnimationBuilder& AnimationBuilder::SetTime(float time)
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

AnimationBuilder& AnimationBuilder::AddPositionKey(const Math::Vector3& position, float time)
{
	mAnimation.mPositionKeys.push_back({position, time});
	return *this;
}

AnimationBuilder& AnimationBuilder::AddRotationKey(const Math::Quaternion& rotation, float time)
{
	mAnimation.mRotationKeys.push_back({ rotation, time });
	return *this;
}

AnimationBuilder& AnimationBuilder::AddScaleKey(const Math::Vector3& position, float time)
{
	//mAnimation
	return *this;
}

Matrix4 AnimationBuilder::GetAnimation(float time)
{
	return mAnimation.GetTransform(time);
}

AnimationBuilder& AnimationBuilder::GetAnimation(const Animation& animation)
{
	mAnimation = std::move(animation);
	return *this;
}
