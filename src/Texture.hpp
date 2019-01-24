#ifndef TEXTURE_H
#define TEXTURE_H
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>

class Texture
{
public:
	Texture();
	~Texture();
	void free();
	bool loadFromFile(std::string path);
	bool loadFromText(std::string text, SDL_Color textColor);
	void render(int x, int y, SDL_Rect *clip = NULL, double angle = 0.0, SDL_Point *center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	int getWidth();
	int getHeight();
private:
	SDL_Texture *mTexture;
	int mWidth;
	int mHeight;
};
#endif