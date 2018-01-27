#pragma once
#include "Game.h"

class HpBar
{
public:
	HpBar(int maxHp, int width, int height, int x, int y);
	~HpBar();

	void render(SDL_Renderer *renderer, int hp);

private:
	SDL_Rect *bar;
	int maxHp;
};