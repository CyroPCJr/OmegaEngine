#include "Precompiled.h"
#include "TimeUtil.h"

using namespace std::chrono;

namespace Omega::Core::TimeUtil 
{

	const float GetTime() noexcept 
	{
		// here initialize the first call because its static and cons, so never change
		const static auto startTime = high_resolution_clock::now();
		const auto currentTime = high_resolution_clock::now();
		const duration<float> elapsedTime = currentTime - startTime;
		return elapsedTime.count();
	}

	const float GetDeltaTime() noexcept
	{
		static auto lastTime = steady_clock::now();
		const auto currentTime = steady_clock::now();
		const duration<float> delta = currentTime - lastTime;
		lastTime = currentTime;
		return delta.count();
	}
	
}