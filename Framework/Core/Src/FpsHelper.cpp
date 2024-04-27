#include "Precompiled.h"
#include "FpsHelper.h"

using namespace Omega::Core;
using namespace std::chrono;

static int mFps{ 0 };

int FpsHelper::GetCurrentFps() noexcept
{
	return mFps;
}

void FpsHelper::BeginFrame() noexcept
{
	++mFrameCount;
	mCurrentTime = steady_clock::now();
}

void FpsHelper::EndFrame() noexcept
{
	mElapsedTime = duration_cast<milliseconds>(mCurrentTime - mStartTime).count();
}

void FpsHelper::Update() noexcept
{
	if (mElapsedTime >= 1000ll) // Update FPS every second
	{
		mFps = mFrameCount;
		mFrameCount = 0;
		mStartTime = mCurrentTime;
	}
}
