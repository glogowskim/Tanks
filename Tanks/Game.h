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
#include "MapLoader.h"
#include "UI.h"

constexpr int MAP_WIDTH = 768;
constexpr int MAP_HEIGHT = 768;
constexpr int WALL_WIDTH = 64;
constexpr int WALL_HEIGHT = 64;
constexpr int SCREEN_WIDTH = 1024;
constexpr int SCREEN_HEIGHT = 768;

const std::string VERSION_NUMBER = "v1.1.0";

class HpBar;
class Wall;
class Texture;
class Object;
class UI;

enum direction
{
	UP = 0,
	RIGHT = 90,
	DOWN = 180,
	LEFT = 270
};

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
	void freeDynamicAllocatedMemory();
	bool checkCollision(SDL_Rect a, SDL_Rect b);

	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Event e;
	TTF_Font *bigFont;
	TTF_Font *normalFont;
	bool quit;

	std::vector<Wall*> wall;
	std::vector<Tank*> tank;
	std::vector<Bullet*> bullet;
	Sound *collisionSound;
	UI *ui;
};