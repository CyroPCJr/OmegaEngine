#include "Bullet.h"

using namespace FinalProject;

void Bullet::Load(const std::string& name)
{
	mTextureId = X::LoadTexture(std::move(name.c_str()));
	mVelocity = { 50.0f };
}

void Bullet::Unload()
{
	mTextureId = 0;
}

void Bullet::Update(float deltaTime)
{
	mPosition += mVelocity * deltaTime;
}

void Bullet::Render()
{
	X::DrawSprite(mTextureId, mPosition);
}

void Bullet::Fire(const X::Math::Vector2& pos, const X::Math::Vector2& vel)
{
	mPosition = pos;
	mVelocity = vel;
}
