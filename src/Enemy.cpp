#include "Enemy.hpp"
#include "Globals.hpp"
#include "Constants.h"
#include "Functions.hpp"
#include "CharRotations.h"
#include <iostream>

Enemy::Enemy()
{
	velX = 0;
	velY = 0;
	mBox.x = 0;
	mBox.y = 0;
	mBox.w = PAR::DOT_WIDTH;
	mBox.h = PAR::DOT_HEIGHT;
	currentClip = &charClips[0];
	walkingToX = 0;
	walkingToY = 0;
	cameToNextCell = true;
	frame = 0;
	sourceX = 0;
	sourceY = 0;
}

void Enemy::renderEnemy(int x, int y)
{
	render(mBox.x - x, mBox.y - y, currentClip);
}

bool Enemy::walk(const std::vector<std::vector<std::pair<int, int>>> &came_from, Tile* tiles[])
{
	velX = 0;
	velY = 0;
	bool atEnd = false;
	if (cameToNextCell)
	{
		int currentY = mBox.y / PAR::TILE_HEIGHT;
		int currentX = mBox.x / PAR::TILE_WIDTH;
		if (currentY == sourceY && currentX == sourceX)
		{
			atEnd = true;
		}
		else
		{
			walkingToY = came_from[currentY][currentX].first;
			walkingToX = came_from[currentY][currentX].second;
			cameToNextCell = false;
		}
	}
	if (!atEnd)
	{
		if (walkingToY * PAR::TILE_HEIGHT > mBox.y)
		{
			mBox.y += PAR::FOE_VELOCITY;
			velY++;
		}
		else if (walkingToY * PAR::TILE_HEIGHT < mBox.y)
		{
			mBox.y -= PAR::FOE_VELOCITY;
			velY--;
		}
		else if (walkingToX * PAR::TILE_WIDTH > mBox.x)
		{
			mBox.x += PAR::FOE_VELOCITY;
			velX++;
		}
		else if (walkingToX * PAR::TILE_WIDTH < mBox.x)
		{
			mBox.x -= PAR::FOE_VELOCITY;
			velX--;
		}
		else
		{
			cameToNextCell = true;
			walk(came_from, tiles);
		}
	}
	return atEnd;
}

void Enemy::update()
{
	++frame;
	if (frame / 16 >= 2)
	{
		frame = 0;
	}
	if (velY > 0)
	{
		if (frame / 16 == 0)
		{
			currentClip = &charClips[faceRun1];
		}
		else
		{
			currentClip = &charClips[faceRun2];
		}
	}
	if (velY < 0)
	{
		if (frame / 16 == 0)
		{
			currentClip = &charClips[backRun1];
		}
		else
		{
			currentClip = &charClips[backRun2];
		}
	}
	if (velX > 0)
	{
		if (frame / 16 == 0)
		{
			currentClip = &charClips[rightRun1];
		}
		else
		{
			currentClip = &charClips[rightRun2];
		}
	}
	if (velX < 0)
	{
		if (frame / 16 == 0)
		{
			currentClip = &charClips[leftRun1];
		}
		else
		{
			currentClip = &charClips[leftRun2];
		}
	}
}

bool Enemy::detectPlayer(SDL_Rect playerPos)
{
	/* SET UP VARIABLES */
	bool found = false;
	int playerX = playerPos.x / PAR::TILE_WIDTH;
	int playerY = playerPos.y / PAR::TILE_HEIGHT;
	int currentX = mBox.x / PAR::TILE_WIDTH;
	int currentY = mBox.y / PAR::TILE_HEIGHT;
	int steps = 0;

	if (velX != 0)
	{
		if (playerY != currentY)
		{
			found = false;
		}
		else
		{
			while (map[currentY][currentX] == 4 && steps < 5) //4 is ground
			{
				currentX += velX;
				if (currentX == playerX)
				{
					found = true;
					break;
				}
				steps++;
			}
		}
	}
	else if (velY != 0)
	{
		if (playerX != currentX)
		{
			found = false;
		}
		else
		{
			while (map[currentY][currentX] == 4 && steps < 5) //4 is ground
			{
				currentY += velY;
				if (currentY == playerY)
				{
					found = true;
					break;
				}
				steps++;
			}
		}
	}
	return found;
}

SDL_Rect Enemy::getBox()
{
	return mBox;
}

void Enemy::setBox(int x, int y)
{
	mBox.x = x;
	mBox.y = y;
}

void Enemy::setSource(int x, int y)
{
	sourceX = x;
	sourceY = y;
}

int Enemy::getSourceX()
{
	return sourceX;
}

int Enemy::getSourceY()
{
	return sourceY;
}