#include "Precompiled.h"
#include "Animator.h"

#include "Model.h"

using namespace Omega;
using namespace Omega::Graphics;

void Animator::Initialize(const Model& model)
{
	mModel = std::move(&model);
	mBoneMatrices.resize(mModel->skeleton.bones.size());
}

void Animator::Terminate()
{
	delete mModel;
}

void Animator::ComputeBindPose()
{
	UpdateBindPose(mModel->skeleton.root, mBoneMatrices);
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
	mTimer += deltaTime * animationClip->tickPerSecond;
	if (mTimer > animationClip->duration)
	{
		mTimer -= animationClip->duration;
	}

	UpdateAnimationPose(mModel->skeleton.root, mBoneMatrices, mTimer, *animationClip);
}