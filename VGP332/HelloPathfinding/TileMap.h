#pragma once

#include <OmegaEngine/Inc/Omega.h>

class TileMap
{
public:

	enum class Types
	{
		Bfs, Dfs, Dijkstras, AStar
	};

	void Load();
	void UnLoad();

	void Update(float deltaTime);
	void Render();

	void DebugUI();

private:

	constexpr int GetIndex(int x, int y) const
	{
		return x + (y * mColumns);
	}

	constexpr Omega::Math::Vector2 GetPosition(float x, float y) const
	{
		return { x * mTileSize + mTileHalfSize, y * mTileSize + mTileHalfSize };
	}

	void SaveMap(const char* mapFileName);
	
	void LoadMap(const char* mapFileName);

	void RenderAIPath(const Types& types);

	void RenderGridBoardNeighbors();

	struct SettingsData
	{
		Omega::AI::Coord coordStart = { 0,0 };
		Omega::AI::Coord coordEnd = { 0,0 };
		Omega::AI::Path path; // hold the path
		Types types;

		int AStarType = 0;
	};

	SettingsData mSettingData;

	Omega::AI::Graph mGraph;

	Omega::AI::BFS mBFS;
	Omega::AI::DFS mDFS;
	Omega::AI::Dijkstras mDijkstras;
	Omega::AI::AStar mAStar;
	
	std::vector<Omega::AI::Graph::Node> mNodes;

	std::array<std::size_t, 6> mTextureIds;
	std::size_t mCircle;
	std::vector<int> mTiles;

	bool mBeginCoord = false;
	bool mEndCoord = false;
	bool mShowGraph = true;

	int mColumns = 0;
	int mRows = 0;
	const int mTileSize = 32;
	const int mTileHalfSize = mTileSize >> 1;
	float mFps = 0;
	float mCircleSize = mTileHalfSize * 0.5f;
	int mSelectedTile = 0;
};