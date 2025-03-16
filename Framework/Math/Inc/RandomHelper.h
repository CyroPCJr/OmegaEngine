#pragma once

namespace Omega::Math
{
	struct Vector2;
	struct Vector3;

	class RandomHelper
	{
	public:
		RandomHelper() noexcept(false) : mEngine(std::random_device()()) {};

		int RandomInt(int min = 0, int max = std::numeric_limits<int>::max());
		int RandomInt01();
		float RandomFloat(float min = 0.0f, float max = 1.0f);

		Vector2 RandomVector2(const Vector2& min, const Vector2& max);

		Vector3 RandomVector3(const Vector3& min, const Vector3& max);

		Vector2 RandomUnitCircle();

	private:
		std::mt19937 mEngine;
	};
}
