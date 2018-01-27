#include "Wall.h"

const int Wall::width = 64;
const int Wall::height = 64;

Wall::Wall(int x, int y, bool destructable)
{
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