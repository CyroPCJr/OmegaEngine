#pragma once

#include "Agent.h"
#include "PartitionGrid.h"

namespace Omega::AI
{
	class AIWorld
	{
	public:
		struct Settings
		{
			Omega::Math::Vector2 worldSize = Omega::Math::Vector2::Zero;
			float partitionGridSize = 0.0f;
		};

		using Obstacles = std::vector<Omega::Math::Circle>;
		using Walls = std::vector<Omega::Math::LineSegment>;
		using Paths = std::vector<Omega::Math::Vector2>;

		void Initialize(const Settings& settings);
		void Update();

		void RegisterEntity(Entity* entity);
		void UnRegisterEntity(Entity* entity);

		void AddObstacles(const Omega::Math::Circle& obstacles);
		void AddWalls(const Omega::Math::LineSegment& walls);
		void AddPaths(const Paths& paths);

		EntitieList GetEntities(const Omega::Math::Circle& range, uint32_t typeId);
		AgentList GetNeighborhood(const Omega::Math::Circle& range, uint32_t typeId);

		inline const Obstacles& GetObstacles() const { return mObstacles; }
		inline const Walls& GetWalls() const { return mWalls; }
		inline const Paths& GetPaths() const { return mPaths; }

		bool HasLineOfSight(const Omega::Math::Vector2& start, const Omega::Math::Vector2& end) const;

		void DebugDraw() const;

		Settings GetSettings() const { return mSettings; }

		void WrapAround(Omega::Math::Vector2& position) const;

		uint32_t GetNextId();

	private:
		EntitieList mEntityList;
		Settings mSettings;
		Obstacles mObstacles;
		Walls mWalls;
		Paths mPaths;
		PartitionGrid<Entity> mPartitionGrid;

		uint32_t mNextId = 0;
	};
}