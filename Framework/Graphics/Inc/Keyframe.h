#pragma once

#include <Math/Inc/EngineMath.h>

namespace Omega::Graphics
{
	template<class T>
	struct Keyframe
	{
		Keyframe() = default;
		Keyframe(const T& t_key, float t_time)
			: key(t_key), time(t_time) 
		{}

		T key;
		float time = 0.0f;
	};

	template<class T>
	using Keyframes = std::vector<Keyframe<T>>;

	using PositionKeys = Keyframes<Math::Vector3>;
	using RotationKeys = Keyframes<Math::Quaternion>;
	using ScaleKeys = Keyframes<Math::Vector3>;
}