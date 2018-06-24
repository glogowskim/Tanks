#pragma once
#include "Game.h"

class Texture
{
public:
	Texture(int x = 0, int y = 0);
	~Texture();

	static void setRenderer(SDL_Renderer *r);

	void render();
	void render(int x, int y, double angle = 0.0);
	void clean();
	void loadPNG(std::string path);
	void loadText(std::string text, TTF_Font *font, SDL_Color textColor = { 255,255,255,255 });
	void setPosition(int x, int y);

	int getWidth();
	int getHeight();

private:
	int x, y;
	int width, height;

	static SDL_Renderer *renderer;
	SDL_Texture *texture;
	SDL_Surface *surface;
	SDL_Rect renderRect;
};