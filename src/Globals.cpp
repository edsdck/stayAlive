#include "Globals.hpp"

SDL_Renderer* renderer = NULL;
SDL_Event e;
SDL_Window* window = NULL;
SDL_Rect tileClips[PAR::TOTAL_TILE_SPRITES];
SDL_Rect charClips[12];
Dot dot;
Enemy foe;
Texture tileSet;
std::vector<std::vector<int>> map(PAR::TOTAL_VERTICAL, std::vector<int>(PAR::TOTAL_HORIZONTAL, 1));
int game_state = 0;
TTF_Font* font = NULL;
Texture menuOption[PAR::MAX_MENU_OPTIONS];
Texture gameOver;
Tile* tiles[PAR::TOTAL_TILES];
std::vector<std::vector<std::pair<int, int>>> came_from;