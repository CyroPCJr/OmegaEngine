#include "Precompiled.h"
#include "Animator.h"

#include "Model.h"

using namespace Omega;
using namespace Omega::Graphics;

void Animator::Initialize(const Model& model)
{
	mModel = std::move(&model);
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

void Animator::Update(float deltaTime)
{
	//TODO: continuar daqui --- Animation Clip 
}
