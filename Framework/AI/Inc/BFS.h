#pragma once

#include "Graph.h"

namespace Omega::AI
{
	class BFS
	{
	public:

		void Reset();

		Path Search(const Graph& graph, const Coord& start, const Coord& end, std::function<bool(Coord)> isBlocked);

		std::list<Coord> GetClosedList() const { return closedList; }
		std::vector<Coord> GetParentList() const { return parent; }

	private:
		std::list<Coord> openList;
		std::list<Coord> closedList;
		std::vector<Coord> parent;
		std::vector<bool> opened;
		std::vector<bool> closed;
	};

}