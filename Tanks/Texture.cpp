#include "Texture.h"

SDL_Renderer* Texture::renderer = nullptr;

Texture::Texture(int x, int y)
{
	texture = nullptr;
	surface = nullptr;
	this->x = x;
	this->y = y;
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
	if (texture != nullptr)
	{
		SDL_DestroyTexture(texture);
		texture = nullptr;
		surface = nullptr;
		width = 0;
		height = 0;
		renderRect = { 0,0,0,0 };
	}
}

void Texture::loadPNG(std::string path)
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
	surface = nullptr;
}

void Texture::loadText(std::string text, TTF_Font *font, SDL_Color textColor)
{
	clean();

	surface = TTF_RenderText_Solid(font, text.c_str(), textColor);

	texture = SDL_CreateTextureFromSurface(renderer, surface);
	width = surface->w;
	height = surface->h;
	renderRect.w = width;
	renderRect.h = height;

	SDL_FreeSurface(surface);
	surface = nullptr;
}

void Texture::setPosition(int x, int y)
{
	this->x = x;
	this->y = y;
}

void Texture::render(int x, int y, double angle)
{
	renderRect.x = x;
	renderRect.y = y;

	SDL_RenderCopyEx(renderer, texture, nullptr, &renderRect, angle, nullptr, SDL_FLIP_NONE);
}

void Texture::render()
{
	renderRect.x = x;
	renderRect.y = y;

	SDL_RenderCopyEx(renderer, texture, nullptr, &renderRect, 0, nullptr, SDL_FLIP_NONE);
}

void Texture::setRenderer(SDL_Renderer *r)
{
	renderer = r;
}

int Texture::getWidth()
{
	return width;
}

int Texture::getHeight()
{
	return height;
}