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
	const uint32_t bonesSize = static_cast<uint32_t>(skeleton.bones.size());
	for (uint32_t i = 0; i < bonesSize; ++i)
	{
		Bone* bone = skeleton.bones[i].get();
		if (bone->parentIndex == -1) // root has no parent
		{
			skeleton.root = bone;
		}
		else
		{
			bone->parent = skeleton.bones[bone->parentIndex].get();
		}
		if (!bone->childIndices.empty())
		{
			// Link bone->children[]
			bone->children = bone->children[bone->parentIndex]->children;
		}
		
	}

}
