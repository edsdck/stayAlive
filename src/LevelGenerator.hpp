#ifndef LEVEL_GENERATOR_H
#define LEVEL_GENERATOR_H
#include <vector>
class LevelGenerator
{
private:
	std::vector<std::vector<int>> edges;
	std::vector<std::vector<int>> sets;
	std::vector<std::vector<int>> grid;
public:
	LevelGenerator();
	void generate();
	void makeGrid(std::vector<std::vector<int>> &map);
	void saveGrid(std::vector<std::vector<int>> &mapVector);
};
#endif