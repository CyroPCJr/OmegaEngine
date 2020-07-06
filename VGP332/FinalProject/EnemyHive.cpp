#include "EnemyHive.h"

using namespace FinalProject;

void EnemyHive::Initialize(const X::Math::Vector2& position)
{
	mPosition = position;
}

void EnemyHive::Terminate()
{
}

void EnemyHive::Update(float deltaTime)
{
}

void EnemyHive::Render()
{
	X::DrawScreenCircle(mPosition, 100.0f, X::Colors::Cyan);
}
