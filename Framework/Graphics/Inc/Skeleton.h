#pragma once

#include "Bone.h"
#include "AnimationClip.h"

namespace Omega::Graphics
{

	struct Skeleton
	{
		Bone* root = nullptr;
		std::vector<std::unique_ptr<Bone>> bones;
	};


	Bone* FindBone(const Skeleton& skeleton, const char* boneName);
	void DrawSkeleton(Bone* skeleton, const std::vector<Math::Matrix4>& boneMatrices);
	void DrawSkeleton(Bone* skeleton, const std::vector<Math::Matrix4>& boneMatrices, const Math::Vector3& modelPosition);
	void DrawSkeleton(const Skeleton& skeleton, const std::vector<Math::Matrix4>& boneMatrices, const Math::Vector3& modelPosition);
	void UpdateBindPose(Bone* bone, std::vector<Math::Matrix4>& boneMatrices, bool showSkeletonOffSet);
	void UpdateAnimationPose(Bone* bone, std::vector<Math::Matrix4>& boneMatrices,
		float time, bool showSkeletonOffSet = false, const AnimationClip& anim = AnimationClip());
}
