#pragma once
#include "EngineMath.h"

namespace Omega::Math::Random
{
	int RandomInt(int min = 0, int max = std::numeric_limits<int>::max());
	float RandomFloat(float min = 0.0f, float max = 1.0f);

	Omega::Math::Vector2 RandomVector2(const Omega::Math::Vector2& min, const Omega::Math::Vector2& max);

	Omega::Math::Vector2 RandomUnitCircle();

	Omega::Math::Vector3 RandomVector3(const Omega::Math::Vector3& min, const Omega::Math::Vector3& max);
	
}