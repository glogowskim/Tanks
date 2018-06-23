#include "HpBar.h"

HpBar::HpBar(int maxHp, int width, int height, int x, int y)
{
	this->maxHp = maxHp;
	this->hp = maxHp;

	bar = new SDL_Rect[maxHp];

	for (int i = 0; i < maxHp; i++)
	{
		bar[i].w = width / maxHp;
		bar[i].h = height;
		bar[i].x = x + i * bar[i].w;
		bar[i].y = y;
	}
}


HpBar::~HpBar()
{
	delete[] bar;
}

void HpBar::setHp(int hp)
{
	this->hp = hp;
}

void HpBar::render()
{
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	for (int i = 0; i < hp; i++) SDL_RenderFillRect(renderer, &bar[i]);
	SDL_SetRenderDrawColor(renderer, 128, 0, 0, 255);
	for (int i = hp; i < maxHp; i++) SDL_RenderFillRect(renderer, &bar[i]);
}