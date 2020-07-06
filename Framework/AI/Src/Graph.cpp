#include "Precompiled.h"
#include "Graph.h"

using namespace AI;

void Graph::Resize(int column, int rows)
{
	mColumns = column;
	mRows = rows;
	mNodes.resize(static_cast<size_t>(column * rows));

	const int rowDir[8] = { -1, -1, -1,  0, 0,  1, 1, 1 };
	const int colDir[8] = { -1, 0,   1, -1, 1, -1, 0, 1 };

	for (int y = 0; y < rows; ++y)
	{
		for (int x = 0; x < column; ++x)
		{
			int index = GetIndex({ x,y });
			for (int i = 0; i < 8; ++i)
			{
				Coord checkCoord = { x + colDir[i], y + rowDir[i] };
				if (GetNode(checkCoord))
				{
					mNodes[index].neighbors.push_back(checkCoord);
				}
			}
		}
	}
}

Graph::Node* Graph::GetNode(const Coord& coord)
{
	return const_cast<Node*>(static_cast<const Graph*>(this)->GetNode(coord));
}

const Graph::Node* AI::Graph::GetNode(const Coord & coord) const
{
	if (coord.x < 0 || coord.y < 0 || coord.x >= mColumns || coord.y >= mRows)
	{
		return nullptr;
	}
	return &mNodes[GetIndex(coord)];
}

int Graph::GetColumns() const
{
	return mColumns;
}

int Graph::GetRows() const
{
	return mRows;
}

int Graph::GetIndex(const Coord& coord) const
{
	return coord.x + (coord.y * mColumns);
}