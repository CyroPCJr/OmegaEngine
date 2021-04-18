#include "Precompiled.h"
#include "AIWorld.h"

using namespace AI;
using namespace Omega::Math;
using namespace Omega::Graphics;

// only translate unit can see
// internal linkage
namespace
{
	template<class Element>
	std::vector<Element*> GetElements(
		const PartitionGrid<Entity>& grid,
		const Circle& range,
		float cellSize,
		uint32_t typeId
	)
	{
		std::vector<Element*> elements;
		int minX = static_cast<int>((range.center.x - range.radius) / cellSize);
		int maxX = static_cast<int>((range.center.x + range.radius) / cellSize);
		int minY = static_cast<int>((range.center.y - range.radius) / cellSize);
		int maxY = static_cast<int>((range.center.y + range.radius) / cellSize);

		minX = Max(minX, 0);
		maxX = Min(maxX, grid.GetColumns() - 1);
		minY = Max(minY, 0);
		maxY = Min(maxY, grid.GetRows() - 1);

		for (int y = minY; y <= maxY; ++y)
		{
			for (int x = minX; x <= maxX; ++x)
			{
				auto& cell = grid.GetCell(x, y);
				for (auto& element : cell)
				{
					if (element->GetTypeId() == typeId)
					{
						elements.push_back(static_cast<Element*>(element));
					}
				}
			}
		}
		return elements;
	}
}

void AIWorld::Initialize(const Settings& settings)
{
	mSettings = settings;
	OMEGAASSERT(settings.partitionGridSize > 0.0f, "[AIWorld] Partition grid size must be greater than zero.");
	const int columns = static_cast<int>(std::ceilf(settings.worldSize.x / settings.partitionGridSize));
	const int row = static_cast<int>(std::ceilf(settings.worldSize.y / settings.partitionGridSize));
	mPartitionGrid.Resize(columns, row);
}

void AIWorld::Update()
{
	mPartitionGrid.ClearCells();
	for (const auto& entity : mEntityList)
	{
		const int columns = static_cast<int>(entity->position.x / mSettings.partitionGridSize);
		const int row = static_cast<int>(entity->position.y / mSettings.partitionGridSize);
		mPartitionGrid.GetCell(columns, row).push_back(entity);
	}
}

void AIWorld::RegisterEntity(Entity* entity)
{
	mEntityList.push_back(entity);
}

void AIWorld::UnRegisterEntity(Entity* entity)
{
	auto iter = std::find(mEntityList.begin(), mEntityList.end(), entity);
	if (iter != mEntityList.end())
	{
		std::iter_swap(iter, mEntityList.end() - 1);
		mEntityList.pop_back();
	}
}

void AI::AIWorld::AddObstacles(const Circle& obstacles)
{
	mObstacles.push_back(obstacles);
}

void AI::AIWorld::AddWalls(const LineSegment& walls)
{
	mWalls.push_back(walls);
}

EntitieList AIWorld::GetEntities(const Circle& range, uint32_t typeId)
{
	return GetElements<Entity>(mPartitionGrid, range, mSettings.partitionGridSize, typeId);
}

AgentList AIWorld::GetNeighborhood(const Circle& range, uint32_t typeId)
{
	return GetElements<Agent>(mPartitionGrid, range, mSettings.partitionGridSize, typeId);
}

bool AI::AIWorld::HasLineOfSight(const Vector2& start, const Vector2& end) const
{
	LineSegment line{ start,end };
	for (auto& wall : mWalls)
	{
		// mean not touch any things
		if (Intersect(line, wall))
		{
			return false;
		}
	}
	for (auto& obstacle : mObstacles)
	{
		if (Intersect(line, obstacle))
		{
			return false;
		}
	}
	return true;
}

void AI::AIWorld::DebugDraw() const
{
	for (auto& obstacle : mObstacles)
	{
		SimpleDraw::AddScreenCircle(obstacle.center, obstacle.radius, Colors::Cyan);
	}

	for (auto& wall : mWalls)
	{
		SimpleDraw::AddScreenLine(wall.from, wall.to, Colors::Cyan);
	}

	for (int i = 0; i < mPartitionGrid.GetColumns(); ++i)
	{
		Vector2 from = { static_cast<float>(i) * mSettings.partitionGridSize, 0.0f};
		Vector2 to = { static_cast<float>(i) * mSettings.partitionGridSize, mSettings.worldSize.y};
		SimpleDraw::AddScreenLine(from, to, Colors::White);
	}

	for (int i = 0; i < mPartitionGrid.GetRows(); ++i)
	{
		Vector2 from = { 0.0f, static_cast<float>(i) * mSettings.partitionGridSize };
		Vector2 to = { mSettings.worldSize.x, static_cast<float>(i) * mSettings.partitionGridSize };
		SimpleDraw::AddScreenLine(from, to, Colors::White);
	}
}

uint32_t AIWorld::GetNextId()
{
	OMEGAASSERT(mNextId < UINT32_MAX, "Run out of ids!");
	return mNextId++;
}
