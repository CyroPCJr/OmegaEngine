#include "Precompiled.h"
#include "Skeleton.h"

#include "SimpleDraw.h"

using namespace Omega;
using namespace Omega::Graphics;

void Omega::Graphics::DrawSkeleton(Skeleton& skeleton, std::vector<Math::Matrix4>& boneMatrices)
{
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
