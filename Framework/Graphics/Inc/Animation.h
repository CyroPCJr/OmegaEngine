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

		//TODO: make use it this function
		bool IsLooping() const { return mLooping; }
		//TODO: implement this function
		void SetWrappedTime(float time);

	private:
		friend class AnimationBuilder;
		friend class AnimationIO;

		PositionKeys mPositionKeys;
		RotationKeys mRotationKeys;
		ScaleKeys mScaleKeys;

		bool mLooping = false;
	};

	using Animations = std::vector<std::unique_ptr<Animation>>;
}
