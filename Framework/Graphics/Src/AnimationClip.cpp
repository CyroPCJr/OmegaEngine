#include "Precompiled.h"
#include "AnimationClip.h"

using namespace Omega;
using namespace Omega::Graphics;

bool AnimationClip::GetTransform(float time, uint32_t boneIndex, Math::Matrix4& transform) const
{
	auto& boneAnim = boneAnimations[boneIndex];
	if (boneAnim)
	{

		transform = boneAnim->GetTransform(time);
		return true;
	}
	return false;
}
