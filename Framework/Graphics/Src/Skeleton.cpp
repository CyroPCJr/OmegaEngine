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
		auto currentPosition = GetTranslation(boneMatrices[bone->index]);
		for (auto& child : bone->children)
		{
			auto childPos = GetTranslation(boneMatrices[child->index]);
			SimpleDraw::AddLine(currentPosition, childPos, Colors::Red);
			DrawSkeleton(child, boneMatrices);
		}
	}

}

void Omega::Graphics::DrawSkeleton(Bone* bone, const std::vector<Math::Matrix4>& boneMatrices, const Math::Vector3& modelPosition)
{

	/*if (!bone)
	{
		return;
	}*/

	auto currentPosition = GetTranslation(boneMatrices[bone->index]);
	for (auto& child : bone->children)
	{
		auto childPos = GetTranslation(boneMatrices[child->index]);
		SimpleDraw::AddSphere(currentPosition + modelPosition, 1.0f, 2, 2, Colors::DarkCyan);
		SimpleDraw::AddLine(currentPosition + modelPosition, childPos + modelPosition, Colors::Red);
		DrawSkeleton(child, boneMatrices, modelPosition);
	}

}

void Omega::Graphics::DrawSkeleton(const Skeleton& skeleton, const std::vector<Math::Matrix4>& boneMatrices, const Math::Vector3& modelPosition)
{
	DrawSkeleton(skeleton.root, boneMatrices, modelPosition);
}

void Omega::Graphics::UpdateBindPose(Bone* bone, std::vector<Math::Matrix4>& boneMatrices, bool showSkeletonOffSet)
{
	if (bone->parent)
	{
		boneMatrices[bone->index] = GetTransform(*bone) * boneMatrices[bone->parent->index];
	}
	else
	{
		boneMatrices[bone->index] = bone->toParentTransform;
	}

	for (auto& child : bone->children)
	{
		UpdateBindPose(child, boneMatrices, showSkeletonOffSet);
	}

	if (showSkeletonOffSet)
	{
		boneMatrices[bone->index] = Math::Transpose(bone->offsetTransform * boneMatrices[bone->index]);
	}
}

void Omega::Graphics::UpdateAnimationPose(Bone* bone, std::vector<Math::Matrix4>& boneMatrices,
	float time, bool showSkeletonOffSet, const AnimationClip& anim)
{
	Math::Matrix4 matTransform = bone->toParentTransform;
	if (bone->parent)
	{
		//Math::Matrix4 matTransform = Math::Matrix4::Identity; //original

		if (anim.GetTransform(time, bone->index, matTransform))
		{
			boneMatrices[bone->index] = matTransform * boneMatrices[bone->parent->index];
		}
		else
		{
			boneMatrices[bone->index] = bone->toParentTransform * boneMatrices[bone->parent->index];
		}
	}
	else
	{
		//boneMatrices[bone->index] = bone->toParentTransform; //original
		boneMatrices[bone->index] = matTransform;
	}

	for (auto& child : bone->children)
	{
		UpdateAnimationPose(child, boneMatrices, time, showSkeletonOffSet, anim);
	}

	if (showSkeletonOffSet)
	{
		boneMatrices[bone->index] = Math::Transpose(bone->offsetTransform * boneMatrices[bone->index]);
	}

}