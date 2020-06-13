#include "Precompiled.h"
#include "Skeleton.h"
#include "AnimationClip.h"

#include "SimpleDraw.h"

using namespace Omega;
using namespace Omega::Graphics;

namespace
{
	Math::Matrix4 GetTransform(const Bone& bone)
	{
		return bone.toParentTransform;
	}
}

void Omega::Graphics::DrawSkeleton(Bone* bone, const std::vector<Math::Matrix4>& boneMatrices)
{
	if (!bone)
	{
		return;
	}

	if (bone->parent)
	{
		Math::Matrix4 mat = boneMatrices[bone->index];
		Math::Matrix4 matParent = boneMatrices[bone->parent->index];
		auto currentPosition = GetTranslation(mat);
		auto parentPosition = GetTranslation(matParent);
		SimpleDraw::AddLine(currentPosition, parentPosition, Colors::Red);
		for (auto& child : bone->children)
		{
			DrawSkeleton(child, boneMatrices);
		}
	}
}

void Omega::Graphics::UpdateBindPose(Bone* bone, std::vector<Math::Matrix4>& boneMatrices)
{
	if (bone->parent)
	{
		boneMatrices[bone->index] = GetTransform(*bone) * boneMatrices[bone->parent->index];
	}
	else
	{
		boneMatrices[bone->index] = Math::Matrix4::Identity;
	}

	for (auto& child : bone->children)
	{
		UpdateBindPose(child, boneMatrices);
	}
}

void Omega::Graphics::UpdateAnimationPose(Bone* bone, std::vector<Math::Matrix4>& boneMatrices,
	float time, const AnimationClip& anim)
{
	if (bone->parent)
	{
		Math::Matrix4 matTransform = Math::Matrix4::Identity;
		if (anim.GetTransform(time, bone->index, matTransform))
		{
			boneMatrices[bone->index] = matTransform * boneMatrices[bone->parent->index];
		}
	}
	else
	{
		boneMatrices[bone->index] = Math::Matrix4::Identity;
	}

	for (auto& child : bone->children)
	{
		UpdateAnimationPose(child, boneMatrices, time, anim);
	}
}