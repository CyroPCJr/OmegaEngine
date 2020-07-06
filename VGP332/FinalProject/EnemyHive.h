#pragma once

#include <XEngine.h>

namespace FinalProject
{
	class EnemyHive
	{
	public:
		void Initialize(const X::Math::Vector2& position);
		void Terminate();
		void Update(float deltaTime);
		void Render();
	private:
		X::Math::Vector2 mPosition;
	};
}