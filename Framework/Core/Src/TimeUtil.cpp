#include "Precompiled.h"
#include "TimeUtil.h"

float Omega::Core::TimeUtil::GetTime()
{
	// here initialize the first call because its static and cons, so never change
	static const auto startTime = std::chrono::high_resolution_clock::now();
	auto now = std::chrono::high_resolution_clock::now();
	return static_cast<float>(std::chrono::duration_cast<std::chrono::milliseconds>(now - startTime).count()) / 1000.0f;
}

float Omega::Core::TimeUtil::GetDeltaTime()
{
	static auto lastTime = std::chrono::high_resolution_clock::now();
	auto currentTime = std::chrono::high_resolution_clock::now();
	auto deltaTime = static_cast<float>(std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastTime).count()) / 1000.0f;
	lastTime = currentTime;
	return deltaTime;
}
