#pragma once
#include "State.h"
#include "Texture.h"

class Texture;

class TitleState : public State
{
public:
	TitleState(TTF_Font *font);
	~TitleState();
	virtual void handleEvents(SDL_Event &e);
	virtual void logic();
	virtual void render();
private:
	Texture *background;
	Texture *info;
};

