#pragma once
#include "Game.h"

class Wall
{
public:
	Wall(int x, int y, bool destructable = true);
	~Wall();

	void destroy();

	int getX();
	int getY();
	bool doesExist();
	bool isDestructable();
	SDL_Rect getCollider();

private:
	int x;
	int y;
	bool exist;
	bool destructable;
	SDL_Rect collider;

	static const int width;
	static const int height;
};