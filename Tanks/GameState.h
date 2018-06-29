#pragma once
#include "State.h"
#include "Game.h"

class Game;

class GameState : public State
{
public:
	GameState(Game *game);
	~GameState();
	virtual void handleEvents(SDL_Event &e);
	virtual void logic();
	virtual void render();
private:
	Game *game;
};

