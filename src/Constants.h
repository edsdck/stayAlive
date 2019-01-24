#ifndef  CONSTANTS_H
#define CONSTANTS_H
#include <string>
namespace PAR
{
	//Number of both horizontal and vertical walls
	const int HORIZONTAL_EDGES = 20;
	const int VERTICAL_EDGES = 20;
	//Total walls in horizontal line including border and corridors
	const int TOTAL_HORIZONTAL = (HORIZONTAL_EDGES * 2 + 1); 
	/* Edges multiplied by two to have corridors and side walls as a border. 
	Every wall has corridor but the first one: (N * 2 - 1)
	Every row has one wall from both sides: +2 */
	const int TOTAL_VERTICAL = (VERTICAL_EDGES * 2 + 1);
	//Size properties of each tile
	const int TILE_WIDTH = 64;
	const int TILE_HEIGHT = 64;
	//Flags for wall's existence
	const int NORTH_WALL = 0b00000001;
	const int WEST_WALL = 0b00000010;
	//Calculate level's size
	const int LEVEL_WIDTH = TOTAL_HORIZONTAL * TILE_WIDTH;
	const int LEVEL_HEIGHT = TOTAL_VERTICAL * TILE_HEIGHT;
	//Set screen's size as your preference
	const int SCREEN_WIDTH = 1366;
	const int SCREEN_HEIGHT = 768;
	const char title[] = "Maze";
	//Set other properties of tiles
	const int TOTAL_TILE_SPRITES = 5;
	const int TOTAL_TILES = TOTAL_HORIZONTAL * TOTAL_VERTICAL;
	//Characters properties
	const int DOT_WIDTH = 44;
	const int DOT_HEIGHT = 50;
	const int DOT_VEL = 6;
	//Foe properties
	const int FOE_VELOCITY = 4; //ONLY DIVISIONS OF 8

	//menu properties
	const int MAX_MENU_OPTIONS = 3;
	const std::string options[MAX_MENU_OPTIONS] = { "Continue game", "New game", "Exit" };
}
#endif