#pragma once

#include "AnimationClip.h"

namespace Omega::Graphics
{
	class AnimationIO
	{
	public:
		static void Write(FILE* file, const Animation& animation);
		static void Read(FILE* file, Animation& animation);

		static void Write(FILE* file, const AnimationClip& animationClip);
		static void Read(FILE* file, AnimationClip& animationClip);
	};
}