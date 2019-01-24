#ifndef GLOBALS_H
#define GLOBALS_H
#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>
#include <utility>
#include "Constants.h"
#include "Dot.hpp"
#include "Enemy.hpp"
#include "Texture.hpp"
#include "Tile.hpp"

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern SDL_Event e;
extern SDL_Rect tileClips[PAR::TOTAL_TILE_SPRITES];
extern SDL_Rect charClips[12]; //3 clips for every rotation
extern Dot dot;
extern Enemy foe;
extern Texture tileSet;
extern std::vector<std::vector<int>> map;
extern int game_state;
extern TTF_Font* font;
extern Texture menuOption[PAR::MAX_MENU_OPTIONS];
extern Texture gameOver;
extern Tile* tiles[PAR::TOTAL_TILES];
extern std::vector<std::vector<std::pair<int, int>>> came_from;
#endif