#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <string>
#include "Texture.h"
#include "Tank.h"
#include "Wall.h"
#include "Bullet.h"
#include "HpBar.h"
#include "Sound.h"

class Game
{
public:
	Game();
	~Game();
	void run();
	void initialize();
	bool checkCollision(SDL_Rect a, SDL_Rect b);

private:
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Event e;
	TTF_Font *bigFont;
	TTF_Font *normalFont;
	std::string score1;
	std::string score2;
	bool quit;
};