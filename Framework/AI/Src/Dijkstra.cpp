#include "Precompiled.h"
#include "Dijkstras.h"

using namespace Omega::AI;

void Dijkstras::Reset(const Graph& graph)
{
	openList.clear();
	closedList.clear();
	g.clear();
	parent.clear();
	opened.clear();
	closed.clear();

	const int totalResize = graph.GetColumns() * graph.GetRows();
	parent.resize(totalResize);
	g.resize(totalResize, 0.0f);
	opened.resize(totalResize);
	closed.resize(totalResize);
}

Path Dijkstras::Search(const Graph& graph, const Coord& start, const Coord& end,
	std::function<bool(Coord)> isBlocked,
	std::function<float(Coord, Coord)> getCost)
{
	Reset(graph);

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
		else
		{
			//- else , expand node;
			auto currentNode = graph.GetNode(current);
			if (currentNode)
			{
				for (auto& neighbor : currentNode->neighbors)
				{
					// if the neightbor is blocked, skip it
					int neighborIndex = graph.GetIndex(neighbor);
					if (isBlocked(neighbor) || closed[neighborIndex])
					{
						continue;
					}

					const float cost = g[graph.GetIndex(current)] + getCost(current, neighbor);
					if (!opened[neighborIndex])
					{
						openList.push_back(neighbor);
						opened[neighborIndex] = true;
						parent[neighborIndex] = current;
						g[neighborIndex] = cost;
						// Wrong! Cannot just add to back
						//openList.push_back(neighbor);

						// for ()
						// check if cost < g[i]
						// insert
						auto it = openList.begin();
						for (auto itEnd = openList.end(); it != itEnd; ++it)
						{
							int index = graph.GetIndex({ it->x, it->y });
							if (cost < g[index])
							{
								break;
							}
						}
						openList.insert(it, neighbor);
					}
					else if (cost < g[neighborIndex])
					{
						openList.remove(neighbor);
						parent[neighborIndex] = current;
						g[neighborIndex] = cost;
						// update parent
						// update g
						// remove and re insert using new g to sort
						auto it = openList.begin();
						for (auto itEnd = openList.end(); it != itEnd; ++it)
						{
							int index = graph.GetIndex({ it->x, it->y });
							if (cost < g[index])
							{
								break;
							}
						}
						openList.insert(it, neighbor);
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
