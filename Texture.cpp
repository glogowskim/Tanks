#include "Texture.h"



Texture::Texture()
{
	texture = NULL;
	surface = NULL;
	width = 0;
	height = 0;
	renderRect = { 0,0,0,0 };
}


Texture::~Texture()
{
	clean();
}

void Texture::clean()
{
	if (texture != NULL)
	{
		SDL_DestroyTexture(texture);
		texture = NULL;
		surface = NULL;
		width = 0;
		height = 0;
		renderRect = { 0,0,0,0 };
	}
}

void Texture::loadPNG(SDL_Renderer *renderer, std::string path)
{
	clean();

	surface = IMG_Load(path.c_str());
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 255, 255, 255));

	texture = SDL_CreateTextureFromSurface(renderer, surface);
	width = surface->w;
	height = surface->h;
	renderRect.w = width;
	renderRect.h = height;

	SDL_FreeSurface(surface);
	surface = NULL;
}

void Texture::loadText(SDL_Renderer *renderer, std::string text, TTF_Font *font, SDL_Color textColor)
{
	clean();

	surface = TTF_RenderText_Solid(font, text.c_str(), textColor);

	texture = SDL_CreateTextureFromSurface(renderer, surface);
	width = surface->w;
	height = surface->h;
	renderRect.w = width;
	renderRect.h = height;

	SDL_FreeSurface(surface);
	surface = NULL;
}

void Texture::render(SDL_Renderer *renderer, int x, int y, double angle)
{
	renderRect.x = x;
	renderRect.y = y;

	SDL_RenderCopyEx(renderer, texture, NULL, &renderRect, angle, NULL, SDL_FLIP_NONE);
}

int Texture::getWidth()
{
	return width;
}

int Texture::getHeight()
{
	return height;
}