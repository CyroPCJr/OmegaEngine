#pragma once

#include "Graph.h"

namespace Omega::AI
{
	class Dijkstras
	{
	public:

		Path Search(const Graph& graph, const Coord& start, const Coord& end, 
			std::function<bool(Coord)> isBlocked, 
			std::function<float(Coord, Coord)> getCost);

		std::list<Coord> GetClosedList() const { return closedList; }
		std::vector<Coord> GetParentList() const { return parent; }

	private:

		void Reset(const Graph& graph);
		
		std::list<Coord> openList;
		std::list<Coord> closedList;
		std::vector<Coord> parent;
		std::vector<float> g; // total cost
		std::vector<bool> opened;
		std::vector<bool> closed;		
	};
}

/*
31/01/2020
Notes in class:

Egde Relaxation
1) Change parents
2) Change to total cost

Graph -> Dijkstra -> shortest path Tree 

*/