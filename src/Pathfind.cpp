#include "Pathfind.hpp"
#include "Constants.h"
#include "TilesNames.h"
#include <queue>
#include <utility>

std::vector<std::vector<std::pair<int, int>>> pathFinding(std::vector<std::vector<int>> &map, int sourceY, int sourceX)
{
	//Breadth first algorithm
	//Using queue - FIFO
	std::queue<std::pair<int, int>> frontier;
	frontier.push(std::make_pair(sourceY, sourceX));
	//Data structure for storing path
	std::vector<std::vector<std::pair<int, int>>> came_from;
	//Initiliazing with -1, it means tile wasn't visited
	came_from.resize(PAR::TOTAL_VERTICAL, std::vector<std::pair<int, int>>(PAR::TOTAL_HORIZONTAL, std::pair<int, int>(-1, -1)));
	came_from[sourceY][sourceX] = { sourceY, sourceX };
	while (!frontier.empty())
	{
		int x, y;
		//Current cell
		y = frontier.front().first;
		x = frontier.front().second;
		frontier.pop();
		//Checking neighbors if they are passable 
		//and if they are pushing them to frontier
		//and also setting that they came from current cell
		if (map[y - 1][x] == ground && (came_from[y - 1][x].first == -1)) //-1 stands for unvisited
		{
			frontier.push(std::make_pair(y - 1, x));
			came_from[y - 1][x] = { y, x };
		}

		if (map[y + 1][x] == ground && (came_from[y + 1][x].first == -1))
		{
			frontier.push(std::make_pair(y + 1, x));
			came_from[y + 1][x] = { y, x };
		}

		if (map[y][x - 1] == ground && (came_from[y][x - 1].first == -1))
		{
			frontier.push(std::make_pair(y, x - 1));
			came_from[y][x - 1] = { y, x };
		}

		if (map[y][x + 1] == ground && (came_from[y][x + 1].first == -1))
		{
			frontier.push(std::make_pair(y, x + 1));
			came_from[y][x + 1] = { y, x };
		}
	}
	return came_from;
}