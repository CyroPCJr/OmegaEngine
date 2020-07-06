#include "BulletManager.h"

using namespace FinalProject;

void BulletManager::Initialize()
{
	for (auto& bullets : mBullets)
	{
		bullets.Load("bullet1.png");
	}
}

void BulletManager::Terminate()
{
}

void BulletManager::Update(float deltaTime)
{
	for (auto& bullets : mBullets)
	{
		bullets.Update(deltaTime);
	}
}

void BulletManager::Render()
{
	for (auto& bullets : mBullets)
	{
		bullets.Render();
	}
}

void BulletManager::Fire(const X::Math::Vector2& position, const X::Math::Vector2& velocity)
{
	mBullets[mFighterNextBullet++].Fire(position, velocity);
	mFighterNextBullet = (++mFighterNextBullet) % std::size(mBullets);
}
