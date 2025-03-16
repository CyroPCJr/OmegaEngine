#include "Precompiled.h"
#include "Constants.h"
#include "RandomHelper.h"
#include "Vector2.h"
#include "Vector3.h"

using namespace Omega::Math;

int RandomHelper::RandomInt(int min, int max)
{
	return std::uniform_int_distribution<int>{min, max}(mEngine);
}

int RandomHelper::RandomInt01()
{
	return RandomInt(0,1);
}

float RandomHelper::RandomFloat(float min, float max)
{
	return std::uniform_real_distribution<float>{min, max}(mEngine);
}

Vector2 RandomHelper::RandomVector2(const Vector2& min, const Vector2& max)
{
	return { RandomFloat(min.x, min.y), RandomFloat(max.x, max.y) };
}

Vector2 RandomHelper::RandomUnitCircle()
{
	const float angle = RandomFloat(0.0f, Constants::TwoPi);
	const float radius = std::sqrt(RandomFloat(0.0f, 1.0f));
	return { radius * cosf(angle), radius * sinf(angle) };
}

Vector3 RandomHelper::RandomVector3(const Vector3& min, const Vector3& max)
{
	return { RandomFloat(min.x, max.x), RandomFloat(min.y, max.y), RandomFloat(min.z, max.z) };
}


