#pragma once
#include "Game.h"

class HpBar : public Object
{
public:
	HpBar(int maxHp, int width, int height, int x, int y);
	~HpBar();

	virtual void render();
	void setHp(int hp);

private:
	int hp;
	int maxHp;
	SDL_Rect *bar;
};