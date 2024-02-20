#include "Precompiled.h"
#include "TimeUtil.h"

using namespace std::chrono;

namespace Omega::Core::TimeUtil {

	float GetTime() noexcept
	{
		// here initialize the first call because its static and cons, so never change
		static const auto startTime = high_resolution_clock::now();
		const auto now = high_resolution_clock::now();
		return static_cast<float>(duration_cast<milliseconds>(now - startTime).count()) / 1000.0f;

		/*const auto startTime = high_resolution_clock::now();
		const auto currentTime = high_resolution_clock::now();

		const duration<float> elapsedTime = currentTime - startTime;
		return elapsedTime.count();*/
	}

	float GetDeltaTime() noexcept
	{
		static auto lastTime = high_resolution_clock::now();
		const auto currentTime = high_resolution_clock::now();
		const auto deltaTime = static_cast<float>(duration_cast<milliseconds>(currentTime - lastTime).count()) / 1000.0f;
		lastTime = currentTime;
		return deltaTime;

		/*static auto lastTime = steady_clock::now();
		const auto currentTime = steady_clock::now();
		const duration<float> delta = currentTime - lastTime;
		lastTime = currentTime;
		return delta.count();*/
	}
}