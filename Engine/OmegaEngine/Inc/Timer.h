#pragma once

namespace Omega
{
	
	class Timer
	{
	public:
		Timer();

		void Initialize();
		void Update();

		float GetElapsedTime() const;
		float GetTotalTime() const;
		float GetFramesPerSecond() const;
	private:
		LARGE_INTEGER mTicksPerSecond;
		LARGE_INTEGER mLastTick;
		LARGE_INTEGER mCurrentTick;

		float mElapsedTime = 0.0f;
		float mTotalTime = 0.0f;

		float mLastUpdateTime = 0.0f;
		float mFrameSinceLastSecond = 0.0f;
		float mFramesPerSecond = 0.0f;
	};
}
