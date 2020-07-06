#pragma once

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

	inline int GetIndex(int x, int y) const
	{
		return x + (y * mColumns);
	}

	inline Omega::Math::Vector2 GetPosition(float x, float y) const
	{
		return { x * mTileSize + mTileHalfSize, y * mTileSize + mTileHalfSize };
	}

	void SaveMap(const char* mapFileName);
	
	void LoadMap(const char* mapFileName);
	

	void RenderAIPath(const Types& types);

	void RenderGridBoardNeighbors();

	struct SettingsData
	{
		AI::Coord coordStart = { 0,0 };
		AI::Coord coordEnd = { 0,0 };
		AI::Path path; // hold the path
		Types types;

		int AStarType = 0;
	};

	SettingsData mSettingData;

	AI::Graph mGraph;

	AI::BFS mBFS;
	AI::DFS mDFS;
	AI::Dijkstras mDijkstras;
	AI::AStar mAStar;
	
	std::vector<AI::Graph::Node> mNodes;

	std::array<X::TextureId, 6> mTextureIds;
	X::TextureId mCircle;
	std::vector<int> mTiles;
	int mColumns = 0;
	int mRows = 0;
	int mTileSize = 32;
	int mTileHalfSize = mTileSize >> 1;
	float mFps = 0;
};