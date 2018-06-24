#pragma once
#include "Game.h"

class HpBar
{
public:
	HpBar(int maxHp, int width, int height, int x, int y);
	~HpBar();

	static void setRenderer(SDL_Renderer *r);

	void render();
	void setHp(int hp);

private:
	int x, y;
	int width, height;
	int hp;
	int maxHp;
	SDL_Rect *bar;

	static SDL_Renderer *renderer;
};