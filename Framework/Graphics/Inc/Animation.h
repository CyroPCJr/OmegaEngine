#pragma once
#include "Keyframe.h"

namespace Omega::Graphics
{
	class Animation
	{
	public:

		Math::Matrix4 GetTransform(float time) const;

	private:
		std::vector<Keyframe<float>> mKeyFrames;
	};
}
