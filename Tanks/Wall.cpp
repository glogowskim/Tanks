#include "Wall.h"

Texture Wall::wallTexture{};
Texture Wall::solidWallTexture{};

Wall::Wall(int x, int y, bool destructable)
{
	width = 64;
	height = 64;

	this->x = x;
	this->y = y;
	this->destructable = destructable;
	exist = true;

	//Set collider box
	collider.x = x;
	collider.y = y;
	collider.w = width;
	collider.h = height;
}


Wall::~Wall()
{
}

void Wall::initTextures(std::string wallTexturePath, std::string solidWallTexturePath)
{
	wallTexture.loadPNG(wallTexturePath);
	solidWallTexture.loadPNG(solidWallTexturePath);
}

void Wall::render()
{
	if (destructable && exist) wallTexture.render(x, y);
	else if (exist) solidWallTexture.render(x, y);
}

int Wall::getX()
{
	return x;
}

int Wall::getY()
{
	return y;
}

bool Wall::doesExist()
{
	return exist;
}

void Wall::destroy()
{
	exist = false;
}

SDL_Rect Wall::getCollider()
{
	return collider;
}

bool Wall::isDestructable()
{
	return destructable;
}