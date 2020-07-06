#pragma once
#include "AI.h"
#include "Hive.h"
#include "EnemyHive.h"
#include <XEngine.h>

namespace FinalProject
{
	class MainGame
	{
	public:
		void Initialize();
		void Update(float deltaTime);
		void Terminate();
		
	private:
		AI::AIWorld::Settings mSettings;
		AI::AIWorld mAIWorld;

		Hive mHive;
		const int mEnemyHiveCount = 4;
		std::unique_ptr<EnemyHive> mEnemyHive_1;
		std::unique_ptr<EnemyHive> mEnemyHive_2;
		std::unique_ptr<EnemyHive> mEnemyHive_3;
		std::unique_ptr<EnemyHive> mEnemyHive_4;
		
	};
}
