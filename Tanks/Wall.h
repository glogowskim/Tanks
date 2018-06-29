#pragma once
#include "Game.h"

class Wall : public Object
{
public:
	Wall(int x, int y, bool destructible = true);
	~Wall();

	static void initTextures(std::string wallTexturePath, std::string solidWallTexturePath);

	virtual void render();
	virtual void reset();
	void destroy();

	int getX();
	int getY();
	bool doesExist();
	bool isDestructible();
	SDL_Rect getCollider();

private:
	bool exist;
	bool destructible;
	SDL_Rect collider;

	static Texture wallTexture;
	static Texture solidWallTexture;
};