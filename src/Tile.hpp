#ifndef TILE_H
#define TILE_H
#include <SDL.h>
class Tile
{
private:
	SDL_Rect mTile;
	int mType;
public:
	Tile(int x, int y, int type);
	void tileRender(SDL_Rect& camera);
	int getType();
	SDL_Rect getBox();
};
#endif