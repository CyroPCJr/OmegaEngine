#pragma once

#include "Bone.h"

namespace Omega::Graphics
{
	class AnimationClip;

	struct Skeleton
	{
		Bone* root = nullptr;
		std::vector<std::unique_ptr<Bone>> bones;
	};

	void DrawSkeleton(Bone* skeleton, const std::vector<Math::Matrix4>& boneMatrices);
	void UpdateBindPose(Bone* bone, std::vector<Math::Matrix4>& boneMatrices);
	void UpdateAnimationPose(Bone* bone, std::vector<Math::Matrix4>& boneMatrices, 
		float time, Math::Matrix4& transform, const AnimationClip& anim);
}
