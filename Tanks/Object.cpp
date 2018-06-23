#include "Object.h"

SDL_Renderer* Object::renderer = nullptr;


Object::Object()
{
}

Object::~Object()
{
}

void Object::setRenderer(SDL_Renderer *r)
{
	renderer = r;
}