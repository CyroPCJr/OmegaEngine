#include "Precompiled.h"
#include "Random.h"
#include "EngineMath.h"

using namespace std;
using namespace Omega::Math;

namespace
{
	random_device randomDevice{};
	mt19937 randomEngine{ randomDevice()};
}

float Random::RandomFloat(float min, float max)
{
	return uniform_real_distribution<float>{ min, max }(randomEngine);
}

Vector2 Random::RandomVector2(const Vector2& min, const Vector2& max)
{
	return { RandomFloat(min.x, min.y), RandomFloat(max.x, max.y) };
}

Vector2 Random::RandomUnitCircle()
{
	const float angle = RandomFloat(0.0f, 360.0f);
	const float radius = RandomFloat(-1.0f, 1.0f);
	return Normalize(Vector2{ radius * cosf(angle), radius * sinf(angle) });
}

Vector3 Random::RandomVector3(const Vector3& min, const Vector3& max)
{
	return { RandomFloat(min.x, max.x), RandomFloat(min.y, max.y), RandomFloat(min.z, max.z) };
}