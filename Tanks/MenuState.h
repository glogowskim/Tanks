#pragma once
#include "State.h"
#include "Game.h"

enum class Menu
{
	RESUME,
	RESTART,
	ABOUT,
	EXIT,
	MENUTITLE
};

class Game;

class MenuState : public State
{
public:
	MenuState(TTF_Font *font72, TTF_Font *font48);
	~MenuState();

	virtual void handleEvents(SDL_Event &e);
	virtual void logic();
	virtual void render();

private:
	std::vector<Texture*> texture;
	SDL_Rect currentChoiceRect;
	SDL_Rect background;

	int currentChoice;
	bool returnPressed;
	const int menuElements = 4;

	int menuBeginX = 400;
	int menuBeginY = 350;
};

