#include "Precompiled.h"
#include "AnimationIO.h"

using namespace Omega;
using namespace Omega::Graphics;

void AnimationIO::Write(FILE* file, const Animation& animation)
{
	fprintf_s(file, "PositionCount: %d\n", static_cast<int>(animation.mPositionKeys.size()));
	for (auto& position : animation.mPositionKeys)
	{
		fprintf_s(file, "Position/Time: %f %f %f %.2f\n", position.key.x, position.key.y, position.key.z, position.time);
	}

	fprintf_s(file, "RotationCount: %d\n", static_cast<int>(animation.mRotationKeys.size()));
	for (auto& rotation : animation.mRotationKeys)
	{
		fprintf_s(file, "Rotation/Time: %f %f %f %.2f\n", rotation.key.x, rotation.key.y, rotation.key.z, rotation.time);
	}

	fprintf_s(file, "ScaleCount: %d\n", static_cast<int>(animation.mScaleKeys.size()));
	for (auto& scaling : animation.mScaleKeys)
	{
		fprintf_s(file, "Scale/Time: %f %f %f %.2f\n", scaling.key.x, scaling.key.y, scaling.key.z, scaling.time);
	}

}

void AnimationIO::Read(FILE* file, Animation& animation)
{
	uint32_t count = 0;
	fscanf_s(file, "PositionCount: %d\n", &count);
	if (count > 0)
	{
		animation.mPositionKeys.resize(count);
		for (auto& position : animation.mPositionKeys)
		{
			fscanf_s(file, "Position/Time: %f %f %f %f\n", &position.key.x, &position.key.y, &position.key.z, &position.time);
		}
	}

	count = 0;
	fscanf_s(file, "RotationCount: %d\n", &count);
	if (count > 0)
	{
		animation.mRotationKeys.resize(count);
		for (auto& rotation : animation.mRotationKeys)
		{
			fscanf_s(file, "Rotation/Time: %f %f %f %f\n", &rotation.key.x, &rotation.key.y, &rotation.key.z, &rotation.time);
		}
	}

	count = 0;
	fscanf_s(file, "ScaleCount: %d\n", &count);
	if (count > 0)
	{
		animation.mScaleKeys.resize(count);
		for (auto& scaling : animation.mScaleKeys)
		{
			fscanf_s(file, "Scale/Time: %f %f %f %f\n", &scaling.key.x, &scaling.key.y, &scaling.key.z, &scaling.time);
		}
	}
}

void AnimationIO::Write(FILE* file, const AnimationClip& animationClip)
{
	for (auto& clips : animationClip.boneAnimations)
	{
		if (clips)
		{
			fprintf_s(file, "[AnimationPos]\n");
			Write(file, *clips);
		}
		else
		{
			fprintf_s(file, "[Empty]\n");
		}
	}

}

void AnimationIO::Read(FILE* file, AnimationClip& animationClip)
{
	uint32_t boneAnimationCout = 0;
	fscanf_s(file, "BoneAnimationCount: %d\n", &boneAnimationCout);
	animationClip.boneAnimations.resize(boneAnimationCout);
	char empty[20];
	for (uint32_t i = 0; i < boneAnimationCout; ++i)
	{
		//std::string emptyblock = empty;
		fscanf_s(file, "%s\n", &empty, (uint32_t)std::size(empty));
		if (std::string(empty) != "[Empty]")
		{
			auto boneAnimation = std::make_unique<Animation>();
			animationClip.boneAnimations[i] = std::move(boneAnimation);
			Read(file, *animationClip.boneAnimations[i]);
		}
	}
}