#pragma once
#include <SDL.h>

enum StateEnum
{
	NONE,
	TITLE,
	GAME,
	MENU,
	ABOUT,
	EXIT
};

class State
{
public:
	virtual ~State() {};
	virtual void handleEvents(SDL_Event &e) = 0;
	virtual void logic() = 0;
	virtual void render() = 0;
	
	static void setRenderer(SDL_Renderer *r);
	static void setCurrentState(StateEnum arg);
	static void setNextState(StateEnum arg);

	static StateEnum getCurrentState();
	static StateEnum getNextState();

protected:
	static SDL_Renderer *renderer;
	static StateEnum currentState;
	static StateEnum nextState;
};

