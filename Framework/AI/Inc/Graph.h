#pragma once

#include "Common.h"

namespace AI
{
	struct Coord
	{
		int x = -1;
		int y = -1;

		inline bool isValid() const
		{
			return x != -1 && y != -1;
		}

		inline bool operator==(const Coord& rhs) const
		{
			return (x == rhs.x) &&
				(y == rhs.y);
		}

		inline Coord operator-(const Coord& rhs) const 
		{
			return { x - rhs.x, y - rhs.y };
		}

	};

	using Path = std::vector<Coord>;

	class Graph
	{
	public:
		struct Node
		{
			std::vector<Coord> neighbors;
		};

		void Resize(int columns, int ros);

		// Node* ->
		// Node& == Node* const
		Node* GetNode(const Coord& coord);
		const Node* GetNode(const Coord& coord) const;

		int GetColumns() const;
		int GetRows() const;
		std::vector<Node> GetListNode() const { return mNodes; }
		const int GetNodeSize() const { return static_cast<int>(mNodes.size()); }

		int GetIndex(const Coord& coord) const;

	private:
		std::vector<Node> mNodes;
		int mColumns = 0;
		int mRows = 0;
	};

}