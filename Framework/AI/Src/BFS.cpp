#include "Precompiled.h"
#include "BFS.h"

using namespace Omega::AI;

void BFS::Reset()
{
	openList.clear();
	closedList.clear();
	parent.clear();
	opened.clear();
	closed.clear();
}

Path BFS::Search(const Graph & graph, const Coord & start, const Coord & end, std::function<bool(Coord)> isBlocked)
{
	Reset();

	const int totalResize = graph.GetColumns() * graph.GetRows();
	parent.resize(totalResize);
	opened.resize(totalResize);
	closed.resize(totalResize);

	//-  Add start to the open list;
	openList.push_back(start);
	opened[graph.GetIndex(start)] = true;

	//- Keep searching until we are done;
	bool found = false;
	while (!found && !openList.empty())
	{
		//- Pick the next node from the open list;
		Coord current = openList.front();
		openList.pop_front();
		//- If node is end, we are done;
		if (current == end)
		{
			found = true;
		}
		else //- else , expand node;
		{
			auto currentNode = graph.GetNode(current);

			if (currentNode) 
			{
				for (auto neighbor : currentNode->neighbors)
				{
					int neighborIndex = graph.GetIndex(neighbor);
					if (!opened[neighborIndex] && !isBlocked(neighbor))
					{
						openList.push_back(neighbor);
						opened[neighborIndex] = true;
						parent[neighborIndex] = current;
					}
				}
			}
			
		}
		//- close node;
		closedList.push_back(current);
		closed[graph.GetIndex(current)] = true;
	}

	Path path;
	if (found)
	{
		std::list<Coord> trace;
		Coord next = end;
		while (next.isValid())
		{
			trace.push_front(next);
			next = parent[graph.GetIndex(next)];
		}

		path.reserve(trace.size());
		for (auto node : trace)
		{
			path.push_back(node);
		}
	}

	return path;
}



/*
Notes in class:

DeMorgan's Theorem
!(A || B|| C) === !A && !B && !C
!(A && B&& C) === !A || !B || !C

initialization with {} ->
braces the compiler make double check,
so always is good to use to check parameters get thougth some templates variables

const_cast<> meanings to remove const

*/