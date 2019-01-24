#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <vector>
#include <fstream>
#include <queue>
#include <utility>
#include "Tile.hpp"

bool initialize();
bool loadMedia();
bool loadTiles(Tile* tiles[]);
bool collisionWithWall(SDL_Rect a, Tile *tiles[]);
void close();
void deleteTiles(Tile* tiles[]);
std::vector<std::vector<std::pair<int, int>>> pathFinding(std::vector<std::vector<int>> &map, int sourceY, int sourceX);
void loadTilesToVector();
void savePositions();
bool loadPositions();
#endif