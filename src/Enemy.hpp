#ifndef ENEMY_H
#define ENEMY_H
#include "Texture.hpp"
#include "Tile.hpp"
#include <vector>
#include <utility>

class Enemy : public Texture
{
private:
	int velX, velY;
	SDL_Rect mBox;
	SDL_Rect* currentClip;
	int walkingToX, walkingToY;
	int sourceX, sourceY;
	bool cameToNextCell;
	int frame;
public:
	Enemy();
	void renderEnemy(int x, int y);
	void update();
	bool walk(const std::vector<std::vector<std::pair<int, int>>> &came_from, Tile* tiles[]);
	bool detectPlayer(SDL_Rect playerPos);
	SDL_Rect getBox();
	void setBox(int x, int y);
	void setSource(int x, int y);
	int getSourceX();
	int getSourceY();
};
#endif