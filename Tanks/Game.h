#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <string>
#include <vector>
#include "Object.h"
#include "Texture.h"
#include "Tank.h"
#include "Wall.h"
#include "Bullet.h"
#include "HpBar.h"
#include "Sound.h"

class HpBar;
class Wall;
class Texture;
class Object;

class Game
{
public:
	Game();
	~Game();
	void run();

private:
	void initialize();
	void loadMap();
	void loadUI();
	void render();
	void freeDynamicAlocatedMemory();
	bool checkCollision(SDL_Rect a, SDL_Rect b);

	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Event e;
	TTF_Font *bigFont;
	TTF_Font *normalFont;
	std::string score1;
	std::string score2;
	bool quit;

	std::vector<Object*> object;
	std::vector<Tank> tank;
	std::vector<Bullet> bullet;
	std::vector<Wall> wall;
	Sound *collisionSound;
	HpBar *bar1;
	HpBar *bar2;

	Texture *player1;
	Texture *player2;
	Texture *player1move;
	Texture *player1fire;
	Texture *player2move;
	Texture *player2fire;
	Texture *hp1;
	Texture *hp2;
	Texture *scoreTank1;
	Texture *scoreTank2;
};