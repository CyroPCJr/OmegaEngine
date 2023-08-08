#pragma once

#include "Graph.h"

namespace Omega::AI
{
	enum class HeuristicType
	{
		Euclidian = 0,
		Manhattan,
		Chebyshev 
	};
	
	class AStar
	{
	public:

		Path Search(const Graph& graph, 
			const Coord& start, 
			const Coord& end,
			std::function<bool(Coord)> isBlocked,
			std::function<float(Coord, Coord)> getCost,
			std::function<float(Coord, Coord)> getHeuristic);

		const std::list<Coord>& GetClosedList() const { return closedList; }
		const std::vector<Coord>& GetParentList() const { return parent; }

		float EstimateCoord(const Coord& begin, const Coord& dest, const HeuristicType& heuristic = HeuristicType::Euclidian);
		
	private:
		
		void Reset(const Graph& graph);

		std::list<Coord> openList;
		std::list<Coord> closedList;
		std::vector<Coord> parent;
		std::vector<float> h;
		std::vector<float> g; // total cost
		std::vector<bool> opened;
		std::vector<bool> closed;
	};

}