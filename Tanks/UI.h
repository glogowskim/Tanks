#pragma once
#include "Game.h"

enum class textureUI
{
	PLAYER1,
	PLAYER2,
	PLAYER1MOVE,
	PLAYER2MOVE,
	PLAYER1FIRE,
	PLAYER2FIRE,
	HP1,
	HP2,
	SCORETANK1,
	SCORETANK2
};

class HpBar;

class UI : public Object
{
public:
	UI(TTF_Font *bigFont, TTF_Font *normalFont);
	~UI();

	virtual void render();
	void setBar(int player1, int player2);
	void setScore(int player1, int player2);

private:
	SDL_Rect background;
	std::vector<Texture*> texture;
	HpBar *bar1;
	HpBar *bar2;

	std::string score1;
	std::string score2;

	TTF_Font *bigFont;
	TTF_Font *normalFont;
};

