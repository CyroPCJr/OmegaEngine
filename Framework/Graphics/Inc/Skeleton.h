#pragma once

#include "Bone.h"

namespace Omega::Graphics
{
	struct Skeleton
	{
		Bone* root = nullptr;
		std::vector<std::unique_ptr<Bone>> bones;
	};

	void DrawSkeleton(Skeleton& skeleton, std::vector<Math::Matrix4>& boneMatrices);
}
