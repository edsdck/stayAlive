#include "Tile.hpp"
#include "Globals.hpp"
#include "Constants.h"
#include "Functions.hpp"

Tile::Tile(int x, int y, int type)
{
	mTile.x = x;
	mTile.y = y;
	mTile.w = PAR::TILE_WIDTH;
	mTile.h = PAR::TILE_HEIGHT;
	mType = type;
}

void Tile::tileRender(SDL_Rect& camera)
{
	if (SDL_HasIntersection(&camera, &mTile))
	{
		tileSet.render(mTile.x - camera.x, mTile.y - camera.y, &tileClips[mType]);
	}
}

int Tile::getType()
{
	return mType;
}

SDL_Rect Tile::getBox()
{
	return mTile;
}