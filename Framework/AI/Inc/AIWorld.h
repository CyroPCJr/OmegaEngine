#pragma once

#include "Agent.h"
#include "PartitionGrid.h"

namespace AI
{
	
	class AIWorld
	{
	public:
		struct Settings
		{
			Omega::Math::Vector2 worldSize;
			float partitionGridSize = 0.0f;
		};

		using Obstacles = std::vector<Omega::Math::Circle>;
		using Walls = std::vector<Omega::Math::LineSegment>;

		void Initialize(const Settings& settings);
		void Update();

		void RegisterEntity(Entity* entity);
		void UnRegisterEntity(Entity* entity);

		void AddObstacles(const Omega::Math::Circle& obstacles);
		void AddWalls(const Omega::Math::LineSegment& walls);

		EntitieList GetEntities(const Omega::Math::Circle& range, uint32_t typeId);
		AgentList GetNeighborhood(const Omega::Math::Circle& range, uint32_t typeId);

		const Obstacles& GetObstacles() const { return mObstacles; }
		const Walls& GetWalls() const { return mWalls; }

		bool HasLineOfSight(const Omega::Math::Vector2& start, const Omega::Math::Vector2& end) const;

		void DebugDraw() const;

		Settings GetSettings() const { return mSettings; }

		uint32_t GetNextId();

	private:
		Settings mSettings;
		EntitieList mEntityList;
		Obstacles mObstacles;
		Walls mWalls;
		PartitionGrid<Entity> mPartitionGrid;

		uint32_t mNextId = 0;
	};
}	