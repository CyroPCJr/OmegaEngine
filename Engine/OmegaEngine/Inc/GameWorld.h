#pragma once

#include "GameObjectFactory.h"

namespace Omega
{
	class GameWorld
	{
	public:
		void Initialize(size_t capacity);
		void Terminate();

		GameObjectHandle Create(const std::filesystem::path& templateFileName, std::string name);
		GameObjectHandle Find(const std::string& name);
		void Destroy(GameObjectHandle handle);

		void Update(float deltaTime);
		void Render();
		void DebugUI();

	private:
		using GameObjectList = std::vector<GameObject*>;

		std::unique_ptr<GameObjectAllocator> mGameObjectAllocator;
		std::unique_ptr<GameObjectHandlePool> mGameObjectHandlePool;

		GameObjectList mUpdateList;

		bool mInitialized = false;
	};

}