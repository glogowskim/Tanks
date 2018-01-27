#pragma once
#include "Game.h"

class Texture
{
public:
	Texture();
	~Texture();
	void clean();
	void loadPNG(SDL_Renderer *renderer, std::string path);
	void loadText(SDL_Renderer *renderer, std::string text, TTF_Font *font, SDL_Color textColor = { 255,255,255,255 });
	void render(SDL_Renderer *renderer, int x, int y, double angle = 0.0);

	int getWidth();
	int getHeight();

private:
	SDL_Texture *texture;
	SDL_Surface *surface;
	SDL_Rect renderRect;
	int width;
	int height;
};