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

		Math::Matrix4 GetAnimation(float time);
		
	private:
		Animation mAnimation;
		float mTime;
	};
}