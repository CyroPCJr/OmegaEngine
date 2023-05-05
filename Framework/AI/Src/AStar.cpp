#include "Precompiled.h"
#include "AStar.h"
#include <algorithm>

using namespace Omega::AI;

void AStar::Reset(const Graph& graph)
{
	openList.clear();
	closedList.clear();
	h.clear();
	g.clear();
	parent.clear();
	opened.clear();
	closed.clear();

	const int totalResize = graph.GetColumns() * graph.GetRows();
	parent.resize(totalResize);
	h.resize(totalResize, 0.0f);
	g.resize(totalResize, 0.0f);
	opened.resize(totalResize);
	closed.resize(totalResize);
}

Path AStar::Search(const Graph& graph,
	const Coord& start,
	const Coord& end,
	std::function<bool(Coord)> isBlocked,
	std::function<float(Coord, Coord)> getCost,
	std::function<float(Coord, Coord)> getHeuristic)
{
	Reset(graph);

	//-  Add start to the open list;
	openList.push_back(start);
	opened[graph.GetIndex(start)] = true;
	h[graph.GetIndex(start)] = getHeuristic(start, end);

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
					float heuristic = getHeuristic(neighbor, end);
					if (!opened[neighborIndex])
					{
						opened[neighborIndex] = true;
						parent[neighborIndex] = current;
						g[neighborIndex] = cost;
						// how much the rest of the way!
						h[neighborIndex] = heuristic;

						// Wrong! Cannot just add to back
						//openList.push_back(neighbor);

						// for ()
						// check if (cost + heuristic) < (g[i] + h[i])
						// insert
						auto it = openList.begin();
						for (auto end = openList.end(); it != end; ++it)
						{
							int index = graph.GetIndex({ it->x, it->y });
							if ((cost + heuristic) < (g[index] + h[index]))
							{
								break;
							}
						}
						openList.insert(it, neighbor);
					}
					else if (cost < g[neighborIndex]) //  edge relaxation
					{
						// update parent
						// update g
						// keep it h (i.e no code)
						// remove and re insert using new f = g + h to sort
						openList.remove(neighbor);
						parent[neighborIndex] = current;
						g[neighborIndex] = cost;

						auto it = openList.begin();
						for (auto end = openList.end(); it != end; ++it)
						{
							int index = graph.GetIndex({ it->x, it->y });
							if ((cost + heuristic) < (g[index] + h[index]))
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

float AStar::EstimateCoord(const Coord& begin, const Coord& dest, const HeuristicType& heuristic)
{
	const Coord& dCoord = begin - dest;
	float distance = 0.0f;
	float x = static_cast<float>(dCoord.x);
	float y = static_cast<float>(dCoord.y);

	switch (heuristic)
	{
	case HeuristicType::Euclidian:
	{
		distance = sqrtf(x * x + y * y);
	}
	break;
	case HeuristicType::Manhattan:
	{
		distance = fabsf(x) + fabsf(y);
	}
	break;
	case HeuristicType::Chebyshev:
	{
		distance = std::fmaxf(x, y);
	}
	break;
	default:
		break;
	}
	return distance;
}
