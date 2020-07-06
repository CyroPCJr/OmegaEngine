#pragma once
#include <XEngine.h>
#include "Bullet.h"

namespace FinalProject
{
	class BulletManager
	{
	public:
		void Initialize();
		void Terminate();

		void Update(float deltaTime);
		void Render();
		void Fire(const X::Math::Vector2& position, const X::Math::Vector2& velocity);
	private:
		Bullet mBullets[200];
		int mFighterNextBullet = 0;
	};
}