#include "MainGame.h"

using namespace FinalProject;

void MainGame::Initialize()
{
	mSettings.partitionGridSize = 100.0f;
	mSettings.worldSize = { static_cast<float>(X::GetScreenWidth()), static_cast<float>(X::GetScreenHeight()) };
	mAIWorld.Initialize(mSettings);

	mEnemyHive_1 = std::make_unique<EnemyHive>();
	mEnemyHive_2 = std::make_unique<EnemyHive>();
	mEnemyHive_3 = std::make_unique<EnemyHive>();
	mEnemyHive_4 = std::make_unique<EnemyHive>();

	mEnemyHive_1.get()->Initialize({ 0.0f, 0.0f }); // top left
	mEnemyHive_2.get()->Initialize({ 0.0f, mSettings.worldSize.y }); // botton left
	mEnemyHive_3.get()->Initialize({ mSettings.worldSize.x, 0.0f }); // top right
	mEnemyHive_4.get()->Initialize({ mSettings.worldSize.x, mSettings.worldSize.y }); // botton right

	mHive.Initialize(mAIWorld);
}

void MainGame::Update(float deltaTime)
{
	mAIWorld.Update();
	mAIWorld.DebugDraw();

	mHive.Update(deltaTime);
	mHive.Render();

	mEnemyHive_1.get()->Update(deltaTime);
	mEnemyHive_2.get()->Update(deltaTime);
	mEnemyHive_3.get()->Update(deltaTime);
	mEnemyHive_4.get()->Update(deltaTime);

	mEnemyHive_1.get()->Render();
	mEnemyHive_2.get()->Render();
	mEnemyHive_3.get()->Render();
	mEnemyHive_4.get()->Render();
}

void MainGame::Terminate()
{
	mHive.Terminate();
}