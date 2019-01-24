#ifndef DOT_H
#define DOT_H
#include "Texture.hpp"
#include "Tile.hpp"

class Dot : public Texture
{
private:
	int velX, velY;
	SDL_Rect mBox;
	SDL_Rect* currentClip;
	int frame;
public:
	Dot();
	~Dot();
	void handleEvent();
	void move(Tile *tiles[]);
	void renderTexture(int camX, int camY);
	void updateChar();
	void setCamera(SDL_Rect &camera);
	SDL_Rect getBox();
	void setBox(int x, int y);
};
#endif