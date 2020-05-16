#pragma once

#include "AnimationClip.h"

namespace Omega::Graphics
{
	struct AnimationSet
	{
		std::vector<std::unique_ptr<AnimationClip>> clips;
	};
}