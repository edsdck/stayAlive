#include "Dot.hpp"
#include "Globals.hpp"
#include "Functions.hpp"
#include "Constants.h"
#include "CharRotations.h"

Dot::Dot()
{
	frame = 0;
	velX = 0;
	velY = 0;
	mBox.x = 0;
	mBox.y = 0;
	mBox.w = PAR::DOT_WIDTH;
	mBox.h = PAR::DOT_HEIGHT;
	currentClip = &charClips[0];
}

Dot::~Dot()
{
	free();
}

void Dot::handleEvent()
{
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT: 
			velX -= PAR::DOT_VEL; 
			break;
		case SDLK_RIGHT: 
			velX += PAR::DOT_VEL; 
			break;
		case SDLK_UP: 
			velY -= PAR::DOT_VEL;
			break;
		case SDLK_DOWN: 
			velY += PAR::DOT_VEL; 
			break;
		}
	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT: 
			velX += PAR::DOT_VEL; 
			break;
		case SDLK_RIGHT: 
			velX -= PAR::DOT_VEL; 
			break;
		case SDLK_UP: 
			velY += PAR::DOT_VEL; 
			break;
		case SDLK_DOWN: 
			velY -= PAR::DOT_VEL;
			break;
		}
	}
}

void Dot::move(Tile *tiles[])
{
	mBox.x += velX;
	if (mBox.x < 0 || (mBox.x + PAR::DOT_WIDTH) > PAR::LEVEL_WIDTH || collisionWithWall(mBox, tiles))
	//if (mBox.x < 0 || (mBox.x + PAR::DOT_WIDTH) > PAR::LEVEL_WIDTH)
	{
		mBox.x -= velX;
	}

	mBox.y += velY;
	if (mBox.y < 0 || (mBox.y + PAR::DOT_HEIGHT) > PAR::LEVEL_HEIGHT || collisionWithWall(mBox, tiles))
	//if (mBox.y < 0 || (mBox.y + PAR::DOT_HEIGHT) > PAR::LEVEL_HEIGHT)
	{
		mBox.y -= velY;
	}
}

void Dot::updateChar()
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

void Dot::setCamera(SDL_Rect &camera)
{
	camera.x = (mBox.x + PAR::DOT_WIDTH / 2) - PAR::SCREEN_WIDTH / 2;
	camera.y = (mBox.y + PAR::DOT_HEIGHT / 2) - PAR::SCREEN_HEIGHT / 2;

	if (camera.x < 0)
	{
		camera.x = 0;
	}
	if (camera.y < 0)
	{
		camera.y = 0;
	}
	if (camera.x > PAR::LEVEL_WIDTH - camera.w)
	{
		camera.x = PAR::LEVEL_WIDTH - camera.w;
	}
	if (camera.y > PAR::LEVEL_HEIGHT - camera.h)
	{
		camera.y = PAR::LEVEL_HEIGHT - camera.h;
	}
}

void Dot::renderTexture(int camX, int camY)
{
	render(mBox.x - camX, mBox.y - camY, currentClip);
}

SDL_Rect Dot::getBox()
{
	return mBox;
}

void Dot::setBox(int x, int y)
{
	mBox.x = x;
	mBox.y = y;
}