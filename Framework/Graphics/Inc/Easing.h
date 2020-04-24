#pragma once

/*
Reference:

https://easings.net/
https://gist.github.com/gre/1650294
*/
namespace Omega::Graphics
{

	// no easing, no acceleration
	constexpr float Linear(float time)
	{
		return time;
	}

	// accelerating from zero velocity
	constexpr float EaseInQuad(float time)
	{
		return time * time;
	}

	// decelerating to zero velocity
	constexpr float EaseOutQuad(float time)
	{
		return time * (2.0f - time);
	}

	// acceleration until halfway, then deceleration
	constexpr float EaseInOutQuad(float time)
	{
		return (time < 0.5f) ? 2.0f * time * time : -1.0f + (4.0f - 2.0f * time) * time;
	}

	// accelerating from zero velocity
	constexpr float EaseInCubic(float time)
	{
		return time * time * time;
	}

	// decelerating to zero velocity
	constexpr float EaseOutCubic(float time)
	{
		return (--time) * time * time + 1.0f;
	}

	// acceleration until halfway, then deceleration
	constexpr float EaseInOutCubic(float time)
	{
		return (time < 0.5f) ?
			4.0f * time * time * time :
			(time - 1.0f) * (time * 2.0f - 2.0f) * (2.0f * time - 2.0f) + 1.0f;
	}

	// accelerating from zero velocity
	constexpr float EaseInQuart(float time)
	{
		return time * time * time * time;
	}

	// decelerating to zero velocity
	constexpr float easeOutQuart(float time)
	{
		return 1.0f - (--time) * time * time * time;
	}

	// acceleration until halfway, then deceleration
	constexpr float easeInOutQuart(float time)
	{
		return (time < 0.5f) ?
			8.0f * time * time * time * time :
			1.0f - 8.0f * (--time) * time * time * time;
	}

	// accelerating from zero velocity
	constexpr float EaseInQuint(float time)
	{
		return time * time * time * time * time;
	}

	// decelerating to zero velocity
	constexpr float EaseOutQuint(float time)
	{
		return 1.0f + (--time) * time * time * time * time;
	}

	// acceleration until halfway, then deceleration
	constexpr float EaseInOutQuint(float time)
	{
		return (time < 0.5f) ?
			16.0f * time * time * time * time * time :
			1.0f - 16.0f * (--time) * time * time * time * time;
	}
}