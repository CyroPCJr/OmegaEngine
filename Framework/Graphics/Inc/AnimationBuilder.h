#pragma once

#include "Animation.h"

namespace Omega::Graphics
{
	class AnimationBuilder
	{
	public:
		AnimationBuilder& SetTime(float time);
		AnimationBuilder& AddPositionKey(const Math::Vector3& position);
		AnimationBuilder& AddRotationKey(const Math::Quaternion& rotation);
		AnimationBuilder& AddScaleKey(const Math::Vector3& scale);

		AnimationBuilder& AddPositionKey(const Math::Vector3& position, float time);
		AnimationBuilder& AddRotationKey(const Math::Quaternion& rotation, float time);
		AnimationBuilder& AddScaleKey(const Math::Vector3& position, float time);


		Math::Matrix4 GetAnimation(float time);

		AnimationBuilder& GetAnimation(const Animation& animation);
	private:
		Animation mAnimation;
		
		float mTime;
	};
}