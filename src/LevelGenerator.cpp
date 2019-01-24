#include "LevelGenerator.hpp"
#include "Constants.h"
#include "Disjoint.hpp"
#include "TilesNames.h"
#include <random>
#include <ctime>
#include <fstream>
#include <string>

LevelGenerator::LevelGenerator()
{
	int h = PAR::VERTICAL_EDGES, w = PAR::HORIZONTAL_EDGES, N = PAR::NORTH_WALL, W = PAR::WEST_WALL;
	grid.resize(h, std::vector<int>(w, 0b00000000));
	sets.resize(h, std::vector<int>(w, 0));
	int rootID = 0;
	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			sets[y][x] = rootID;
			rootID++;
			if (x > 0)
			{
				edges.push_back({ x, y, W });
				grid[y][x] |= W;
			}
			if (y > 0)
			{
				edges.push_back({ x, y, N });
				grid[y][x] |= N;
			}
		}
	}
}

void LevelGenerator::generate()
{
	Disjoint level(PAR::HORIZONTAL_EDGES * PAR::VERTICAL_EDGES);
	std::mt19937 g(static_cast<uint32_t>(time(0)));
	std::shuffle(std::begin(edges), std::end(edges), g);
	while (!edges.empty())
	{
		int x = edges.back()[0];
		int y = edges.back()[1];
		int dir = edges.back()[2];
		edges.pop_back();
		int nx, ny;
		if (dir == PAR::WEST_WALL) { nx = x - 1; ny = y; }
		else { nx = x; ny = y - 1; }
		int set1 = sets[y][x], set2 = sets[ny][nx];
		if (!level.areConnected(set1, set2))
		{
			level.connect(set1, set2);
			if (dir == PAR::NORTH_WALL) { grid[y][x] &= 0b11111110; } //0b00000011 & 0b11111110
			else { grid[y][x] &= 0b11111101; }
		}
	}
}

void LevelGenerator::makeGrid(std::vector<std::vector<int>> &mapVector)
{
	for (int y = 0; y < PAR::VERTICAL_EDGES; y++)
	{
		for (int x = 0; x < PAR::HORIZONTAL_EDGES; x++)
		{
			if (x > 0)
			{
				if ((grid[y][x] & PAR::WEST_WALL) != 0)
				{
					mapVector[y * 2 + 1][x * 2] = rand() % 4;
					mapVector[y * 2 + 1][x * 2 + 1] = ground;
				}
				else
				{
					mapVector[y * 2 + 1][x * 2] = ground;
					mapVector[y * 2 + 1][x * 2 + 1] = ground;
				}
			}
			else
			{
				mapVector[y * 2 + 1][x + 1] = ground;
			}
		}

		if (y + 1 != PAR::VERTICAL_EDGES)
		{
			int y1 = y + 1;
			for (int x = 0; x < PAR::HORIZONTAL_EDGES; x++)
			{
				if (x > 0)
				{
					if ((grid[y + 1][x] & PAR::NORTH_WALL) != 0)
					{
						mapVector[y1 * 2][x * 2] = rand() % 4;
						mapVector[y1 * 2][x * 2 + 1] = rand() % 4;
					}
					else
					{
						mapVector[y1 * 2][x * 2] = rand() % 4;
						mapVector[y1 * 2][x * 2 + 1] = ground;
					}
				}
				else
				{
					if ((grid[y + 1][x] & PAR::NORTH_WALL) != 0)
					{
						mapVector[y1 * 2][x * 2 + 1] = rand() % 4;
					}
					else
					{
						mapVector[y1 * 2][x * 2 + 1] = ground;
					}
				}
			}
		}
	}
}

void LevelGenerator::saveGrid(std::vector<std::vector<int>> &mapVector)
{
	std::ofstream map("data/tile.map");
	for (int y = 0; y < PAR::TOTAL_VERTICAL; y++)
	{
		for (int x = 0; x < PAR::TOTAL_HORIZONTAL; x++)
		{
			map << mapVector[y][x];
		}
		map << "\n";
	}
}