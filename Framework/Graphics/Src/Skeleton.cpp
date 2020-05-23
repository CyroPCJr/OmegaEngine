#include "Precompiled.h"
#include "Skeleton.h"

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
	//uint32_t size = static_cast<uint32_t>(skeleton.bones.size());
	//boneMatrices.reserve(size);
	//for (uint32_t i = 0; i < size; ++i)
	//{
	//	Bone* bone = skeleton.bones[i].get();
	//	if (bone->parent)
	//	{
	//		auto mat = bone->toParentTransform * bone->parent->toParentTransform;
	//		boneMatrices.push_back(mat);
	//	}
	//	else
	//	{
	//		auto mat = bone->toParentTransform;
	//		//boneMatrices.push_back(mat);
	//	}

	//	for (auto& child : bone->children)
	//	{
	//		Math::Matrix4 mat = child->toParentTransform * bone->toParentTransform;
	//		boneMatrices.push_back(mat);
	//	}
	//}
	if (!bone)
	{
		return;
	}

	if (!bone->parent)
	{
		Math::Matrix4 mat = boneMatrices[bone->index];
		Math::Matrix4 matParent = boneMatrices[bone->parent->index];
		auto currentPosition = GetTranslation(mat);
		auto parentPosition = GetTranslation(matParent);
		SimpleDraw::AddLine(currentPosition, parentPosition, Colors::Black);

		for (auto& child : bone->children)
		{
			DrawSkeleton(child, boneMatrices);
		}
	}





	// Homework
	// Use skeleton so you know what the parent child order is
	//But, use boneMatrices ( whick is the multipled out matrices)
	// TODO: Testar isso aqui
	/*

	Tips for getting the bone matrices:
-----------------------------------

	   R
	   |
	   V
	  [U]
   [U]   [U]
[U]         [U]

GetTransform returns
	bone->toParentTransform if we are using the bind pose (default from the skeleton)
	clip.boneAnim[bone->index] if we are using a animation pose (at time t)

void UpdateBoneRecursive(std::vector<Matrix>& boneMatrices, const Bone* bone)
{
	if (bone->parent)
		boneMatrices[bone->index] = GetTransform(bone) * boneMatrices[bone->parent->index]
	else
		boneMatrices[bone->index] = GetTransform(bone)

	for (auto& child : bone->children)
		UpdateBoneRecursive(boneMatrices, child)
}


std::vector<Matrix> boneMatrices;
UpdateBoneRecursive(boneMatrices, skeleton.root)


	*/

	//http://ogldev.atspace.co.uk/www/tutorial38/tutorial38.html
   /* mat4 BoneTransform = gBones[BoneIDs[0]] * Weights[0];
	BoneTransform += gBones[BoneIDs[1]] * Weights[1];
	BoneTransform += gBones[BoneIDs[2]] * Weights[2];
	BoneTransform += gBones[BoneIDs[3]] * Weights[3];

	vec4 PosL = BoneTransform * vec4(Position, 1.0);
	gl_Position = gWVP * PosL;
	TexCoord0 = TexCoord;
	vec4 NormalL = BoneTransform * vec4(Normal, 0.0);
	Normal0 = (gWorld * NormalL).xyz;
	WorldPos0 = (gWorld * PosL).xyz;
	*/

}

void Omega::Graphics::UpdatePose(Bone& bone, std::vector<Math::Matrix4>& boneMatrices)
{
	if (bone.parent)
	{
		boneMatrices[bone.index] = GetTransform(bone) * boneMatrices[bone.parent->index];
	}
	else
	{
		//boneMatrices[bone.index] = GetTransform(bone);
		boneMatrices[bone.index] = Math::Matrix4::Identity;
	}

	for (auto& child : bone.children)
	{
		UpdatePose(*child, boneMatrices);
	}

	/*if (bone == nullptr)
		return;

	if (bone->parent != nullptr)
		boneWorldMatrices[bone->index] = Math::Matrix4::Identity;
	else
		boneWorldMatrices[bone->index] = bone->toParentTransform * boneWorldMatrices[bone->parent->index];

	for (auto& child : bone->children)
		UpdatePose(child, boneWorldMatrices);*/

}
