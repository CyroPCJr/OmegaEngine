#include "TileMap.h"
#include <ImGui/Inc/imgui.h>

void TileMap::Load()
{
	mTextureIds[0] = X::LoadTexture("grass.png");
	mTextureIds[1] = X::LoadTexture("flower.png");
	mTextureIds[2] = X::LoadTexture("tree0.png");
	mTextureIds[3] = X::LoadTexture("tree1.png");
	mTextureIds[4] = X::LoadTexture("tree2.png");
	mTextureIds[5] = X::LoadTexture("tree3.png");
	mCircle = X::LoadTexture("bullet2.png");

	mColumns = 25;
	mRows = 20;
	mTiles.resize(static_cast<size_t>(mColumns * mRows), 0);
	mGraph.Resize(mColumns, mRows);

	mNodes = mGraph.GetListNode();
}

void TileMap::UnLoad()
{
	// clean array, setting all the values to zero
	//std::fill_n(mTextureIds, 6, 0);
	mTiles.clear();
}

void TileMap::Update(float deltaTime)
{
	mFps = 1.0f / deltaTime;
	const int column = X::GetMouseScreenX() / mTileSize;
	const int row = X::GetMouseScreenY() / mTileSize;
	// Check bound and make sure we are within the map - Ok
	// Check if mouse is clicked - Ok
	// Index into mTiles and change values - Ok

	if (X::IsMousePressed(X::Mouse::LBUTTON))
	{
		const int idxClick = GetIndex(column, row);
		if ((mColumns <= column) ||
			(mRows <= row))
		{
			return;
		}
		if (mTiles[idxClick] < 5)
		{
			mTiles[idxClick]++;
		}
		else
		{
			mTiles[idxClick] = 0;
		}

	}

	DebugUI();
}

void TileMap::Render()
{
	RenderGridBoardNeighbors();
	RenderAIPath(mSettingData.types);
}

void TileMap::DebugUI()
{
	ImVec4 mYellowColor = { 1,1,0,1 };
	ImGui::Begin("AI Settings", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::TextColored(mYellowColor, "FPS: %.2f", mFps);
	ImGui::Separator();
	ImGui::TextColored(mYellowColor, "Coordinades");
	ImGui::Separator();
	ImGui::DragInt("Start X", &mSettingData.coordStart.x, 0.5f, 0, mColumns - 1);
	ImGui::DragInt("Start Y", &mSettingData.coordStart.y, 0.5f, 0, mRows - 1);
	ImGui::DragInt("Final X", &mSettingData.coordEnd.x, 0.5f, 0, mColumns - 1);
	ImGui::DragInt("Final Y", &mSettingData.coordEnd.y, 0.5f, 0, mRows - 1);
	ImGui::Separator();

	if (ImGui::Button("Save map"))
	{
		char fileName[MAX_PATH] = {};
		if (X::SaveFileDialog(fileName, "Save Map", ".txt"))
		{
			SaveMap(fileName);
		}
	}

	if (ImGui::Button("Load map"))
	{
		char fileName[MAX_PATH] = {};
		if (X::OpenFileDialog(fileName, "Load Map", ".txt"))
		{
			//UnloadMap();
			LoadMap(fileName);
		}
	}

	if (ImGui::CollapsingHeader("BFS: Breath-First Search", ImGuiTreeNodeFlags_DefaultOpen))
	{
		if (ImGui::Button("Run BFS"))
		{
			mSettingData.types = Types::Bfs;
			mSettingData.path.clear();
			mSettingData.path = mBFS.Search(mGraph, mSettingData.coordStart, mSettingData.coordEnd, [this](AI::Coord coord)
			{
				return mTiles[GetIndex(coord.x, coord.y)];
			});
		}

	}

	ImGui::Separator();

	if (ImGui::CollapsingHeader("DFS: Depth-First Search", ImGuiTreeNodeFlags_DefaultOpen))
	{
		if (ImGui::Button("Run DFS"))
		{
			mSettingData.types = Types::Dfs;
			mSettingData.path.clear();
			mSettingData.path = mDFS.Search(mGraph, mSettingData.coordStart, mSettingData.coordEnd, [this](AI::Coord coord)
			{
				return mTiles[GetIndex(coord.x, coord.y)];
			});

		}
	}

	ImGui::Separator();

	if (ImGui::CollapsingHeader("Dijkstras", ImGuiTreeNodeFlags_DefaultOpen))
	{
		if (ImGui::Button("Run Dijkstras"))
		{
			mSettingData.types = Types::Dijkstras;
			mSettingData.path.clear();
			auto funcIsBlocked = [this](AI::Coord coord)
			{
				return mTiles[GetIndex(coord.x, coord.y)];
			};

			auto funcIsCost = [this](AI::Coord to, AI::Coord from)
			{
				return (to.x != from.x && to.y != from.y) ?  1.4142f : 1.0f;
			};

			mSettingData.path = mDijkstras.Search(mGraph, mSettingData.coordStart, mSettingData.coordEnd, funcIsBlocked, funcIsCost);

		}
	}

	ImGui::Separator();

	if (ImGui::CollapsingHeader("AStar", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::RadioButton("Euclidian", &mSettingData.AStarType, 0);
		ImGui::RadioButton("Manhattan", &mSettingData.AStarType, 1);
		ImGui::RadioButton("Chebyshev", &mSettingData.AStarType, 2);

		if (ImGui::Button("Run AStar"))
		{
			mSettingData.types = Types::AStar;
			mSettingData.path.clear();
			auto funcIsBlocked = [this](AI::Coord coord)
			{
				return mTiles[GetIndex(coord.x, coord.y)];
			};

			auto funcIsCost = [this](AI::Coord to, AI::Coord from)
			{
				return (to.x != from.x && to.y != from.y) ? 1.4142f : 1.0f;
			};

			auto funcHeuristic = [this](AI::Coord to, AI::Coord from)
			{

				return mAStar.EstimateCoord(to, from,
					static_cast<AI::HeuristicType>(mSettingData.AStarType));
			};

			mSettingData.path = mAStar.Search(mGraph, mSettingData.coordStart, mSettingData.coordEnd, funcIsBlocked, funcIsCost, funcHeuristic);

		}
	}

	ImGui::End();
}

void TileMap::SaveMap(const char* mapFileName)
{
	FILE* file = nullptr;
	fopen_s(&file, mapFileName, "w");
	if (!file)
	{
		return;
	}
	fscanf_s(file, "Rows: %d\n", &mRows);
	fscanf_s(file, "Columns: %d\n", &mColumns);
	fprintf_s(file, "Rows: %d\n", mRows);
	fprintf_s(file, "Columns: %d\n", mColumns);
	for (int y = 0; y < mRows; ++y)
	{
		for (int x = 0; x < mColumns; ++x)
		{
			int index = mGraph.GetIndex({ x, y });
			fprintf_s(file, std::to_string(mTiles[index]).c_str());
		}
		fputc('\n', file);
	}
	fclose(file);
}

void TileMap::LoadMap(const char* mapFileName)
{
	mTiles.clear();
	FILE* file = nullptr;
	fopen_s(&file, mapFileName, "r");
	if (file == nullptr)
	{
		return;
	}
	fscanf_s(file, "Rows: %d\n", &mRows);
	fscanf_s(file, "Columns: %d\n", &mColumns);

	mTiles.resize(static_cast<size_t>(mRows * mColumns));

	for (int y = 0; y < mRows; ++y)
	{
		for (int x = 0; x < mColumns; ++x)
		{
			int index = mGraph.GetIndex({ x,y });
			mTiles[index] = fgetc(file) - '0';
		}
		fgetc(file);
	}
	fclose(file);
}

void TileMap::RenderAIPath(const Types& types)
{
	X::Color color;
	std::list<AI::Coord> closedList;
	std::vector<AI::Coord> parentList;

	switch (types)
	{
	case Types::Bfs:
	{
		color = X::Colors::Blue;
		closedList = mBFS.GetClosedList();
		parentList = mBFS.GetParentList();
	}
	break;
	case Types::Dfs:
	{
		color = X::Colors::Crimson;
		closedList = mDFS.GetClosedList();
		parentList = mDFS.GetParentList();
	}
	break;
	case Types::Dijkstras:
	{
		color = X::Colors::Silver;
		closedList = mDijkstras.GetClosedList();
		parentList = mDijkstras.GetParentList();
	}
	break;
	case Types::AStar:
	{
		color = X::Colors::Salmon;
		closedList = mAStar.GetClosedList();
		parentList = mAStar.GetParentList();
	}
	break;
	default:
		break;
	}

	for (auto node : closedList)
	{
		auto& parentNode = parentList[mGraph.GetIndex(node)];
		if (parentNode.isValid())
		{
			X::DrawScreenLine(GetPosition(static_cast<float>(node.x), static_cast<float>(node.y)),
				GetPosition(static_cast<float>(parentNode.x), static_cast<float>(parentNode.y)),
				X::Colors::DarkGreen);
		}
	}

	const int size = static_cast<int>(mSettingData.path.size());
	for (int i = 0; i + 1 < size; ++i)
	{
		auto to = mSettingData.path[i];
		auto from = mSettingData.path[i + 1];

		X::Math::Vector2 pos = GetPosition(static_cast<float>(to.x), static_cast<float>(to.y));
		X::Math::Vector2 vec = GetPosition(static_cast<float>(from.x), static_cast<float>(from.y));
		X::DrawScreenLine(pos, vec, color);

		X::DrawScreenCircle(GetPosition(static_cast<float>(from.x), static_cast<float>(from.y)), 3.0f, X::Colors::Yellow);
		X::DrawScreenCircle(GetPosition(static_cast<float>(to.x), static_cast<float>(to.y)), 3.0f, X::Colors::Purple);
	}
}

void TileMap::RenderGridBoardNeighbors()
{
	for (int y = 0; y < mRows; ++y)
	{
		for (int x = 0; x < mColumns; ++x)
		{
			const int index = GetIndex(x, y);
			X::Math::Vector2 pos = { static_cast<float>(x)* mTileSize,
								  static_cast<float>(y)* mTileSize
			};
			X::DrawSprite(mTextureIds[mTiles[index]], pos, X::Pivot::TopLeft);

			for (int i = 0; i < mNodes[index].neighbors.size(); ++i)
			{
				X::Math::Vector2 vec = GetPosition(static_cast<float>(mNodes[index].neighbors[i].x),
					static_cast<float>(mNodes[index].neighbors[i].y));

				X::DrawScreenLine(pos + static_cast<float>(mTileHalfSize), vec, X::Colors::Gray);
			}
		}
	}
}

/*
Notes in class
31/01/2020

pathfinding = graph search
OpenList = add the neighbors
ClosedList = node already checked
They are both have in common a parents

*/