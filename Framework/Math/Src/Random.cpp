#include "Precompiled.h"
#include "EngineMath.h"

using namespace std;
using namespace Omega::Math;

namespace
{
	random_device randomDevice{};
	mt19937 randomEngine{ randomDevice() };
}

int Omega::Math::RandomInt(int min, int max)
{
	return uniform_int_distribution<int>{ min, max }(randomEngine);
}

float Omega::Math::RandomFloat(float min, float max)
{
	return uniform_real_distribution<float>{ min, max }(randomEngine);
}

Vector2 Omega::Math::RandomVector2(const Vector2& min, const Vector2& max)
{
	return { RandomFloat(min.x, min.y), RandomFloat(max.x, max.y) };
}
