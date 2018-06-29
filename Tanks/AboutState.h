#pragma once
#include "State.h"
#include "Game.h"

class AboutState : public State
{
public:
	AboutState(std::string version, TTF_Font *font72, TTF_Font *font48, TTF_Font *font24, TTF_Font *font18);
	~AboutState();
	virtual void handleEvents(SDL_Event &e);
	virtual void logic();
	virtual void render();

private:
	std::vector<Texture*> texture;
};

