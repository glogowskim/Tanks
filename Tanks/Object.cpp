#include "Object.h"

SDL_Renderer* Object::renderer = nullptr;
std::vector<Object*> Object::object{};


Object::Object()
{
	object.push_back(this);
}

Object::~Object()
{
}

void Object::setRenderer(SDL_Renderer *r)
{
	renderer = r;
}

void Object::renderAll()
{
	for (auto x : object)
	{
		x->render();
	}
}

void Object::resetAll()
{
	for (auto x : object)
	{
		x->reset();
	}
}