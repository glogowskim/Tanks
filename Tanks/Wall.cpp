#include "Wall.h"

Texture Wall::wallTexture{};
Texture Wall::solidWallTexture{};

Wall::Wall(int x, int y, bool destructible)
{
	width = WALL_WIDTH;
	height = WALL_HEIGHT;

	this->x = x;
	this->y = y;
	this->destructible = destructible;
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
	if (exist)
	{
		if (destructible) wallTexture.render(x, y);
		else solidWallTexture.render(x, y);
	}
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

void Wall::reset()
{
	exist = true;
}

SDL_Rect Wall::getCollider()
{
	return collider;
}

bool Wall::isDestructible()
{
	return destructible;
}