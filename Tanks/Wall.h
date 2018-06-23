#pragma once
#include "Game.h"

class Wall : public Object
{
public:
	Wall(int x, int y, bool destructable = true);
	~Wall();

	static void initTextures(std::string wallTexturePath, std::string solidWallTexturePath);

	virtual void render();
	void destroy();

	int getX();
	int getY();
	bool doesExist();
	bool isDestructable();
	SDL_Rect getCollider();

private:
	bool exist;
	bool destructable;
	SDL_Rect collider;

	static Texture wallTexture;
	static Texture solidWallTexture;
};