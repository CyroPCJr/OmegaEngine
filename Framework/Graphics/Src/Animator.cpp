#include "Precompiled.h"
#include "Animator.h"

#include "Model.h"

using namespace Omega;
using namespace Omega::Graphics;

void Animator::Initialize(const Model& model)
{
	mModel = std::move(&model);
	mBoneMatrices.clear();
	mBoneMatrices.resize(mModel->skeleton.bones.size());
	ComputeBindPose();
}

void Animator::Terminate()
{
	mBoneMatrices.clear();
	mModel = nullptr;
}

void Animator::ComputeBindPose()
{
	UpdateBindPose(mModel->skeleton.root, mBoneMatrices, false);
}

void Animator::PlayAnimation(int index)
{
	OMEGAASSERT(index < static_cast<int>(mModel->animationSet.clips.size()), "[Animator] Invalid index.");
	mClipIndex = index;
}

void Animator::StopAnimation(bool stop)
{
	if (stop)
	{
		mCurrentTimer = mTimer;
	}
}

void Animator::SetTime(float time)
{
	mTimer = time;
}

void Animator::Update(float deltaTime)
{
	auto& animationClip = mModel->animationSet.clips[mClipIndex];
	mMaxDuration = animationClip->duration;

	mTimer += deltaTime * animationClip->tickPerSecond;
	if (mTimer > mMaxDuration)
	{
		mTimer -= mMaxDuration;
	}

	UpdateAnimationPose(mModel->skeleton.root, mBoneMatrices, mTimer, !mShowSkeleton, *animationClip);

	/*const size_t size = mBoneMatrices.size();
	for (size_t i = 0; i < size; ++i)
	{
		mBoneMatricesFinal[i] = Transpose(mModel->skeleton.bones[i]->offsetTransform * mBoneMatrices[i]);
	}*/
}