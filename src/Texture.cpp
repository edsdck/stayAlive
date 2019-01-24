#include "Texture.hpp"
#include "Globals.hpp"

Texture::Texture()
{
	mWidth = 0;
	mHeight = 0;
	mTexture = nullptr;
}

Texture::~Texture()
{
	free();
}

void Texture::free()
{
	if (mTexture != nullptr)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = nullptr;
		mWidth = 0;
		mHeight = 0;
	}
}

bool Texture::loadFromFile(std::string path)
{
	free();
	SDL_Texture *newTexture = nullptr;
	SDL_Surface *loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface != NULL)
	{
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture != nullptr)
		{
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}
		SDL_FreeSurface(loadedSurface);
	}
	mTexture = newTexture;
	return mTexture != NULL;
}

bool Texture::loadFromText(std::string text, SDL_Color textColor)
{
	free();
	SDL_Surface* textSurface = TTF_RenderText_Blended(font, text.c_str(), textColor);
	if (textSurface == NULL)
	{
		
	}
	else
	{
		mTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		if (mTexture == NULL)
		{
			
		}
		else
		{
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		SDL_FreeSurface(textSurface);
	}
	return mTexture != NULL;
}


void Texture::render(int x, int y, SDL_Rect *clip, double angle, SDL_Point *center, SDL_RendererFlip flip)
{
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	SDL_RenderCopyEx(renderer, mTexture, clip, &renderQuad, angle, center, flip);
}

int Texture::getWidth()
{
	return mWidth;
}

int Texture::getHeight()
{
	return mHeight;
}