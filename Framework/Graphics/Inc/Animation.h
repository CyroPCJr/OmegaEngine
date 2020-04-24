#pragma once
#pragma once
#include "Keyframe.h"

namespace Omega::Graphics
{
	class Animation
	{
	public:
		Math::Vector3 GetPosition(float time) const;
		Math::Quaternion GetRotation(float time) const;
		Math::Vector3 GetScale(float time) const;
		Math::Matrix4 GetTransform(float time) const;

		bool IsLooping() const { return mLooping; }
	private:
		friend class AnimationBuilder;
		PositionKeys mPositionKeys;
		RotationKeys mRotationKeys;
		ScaleKeys mScaleKeys;

		bool mLooping = false;
	};

	using Animations = std::vector<std::unique_ptr<Animation>>;
}
