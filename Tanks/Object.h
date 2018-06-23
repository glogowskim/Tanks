#pragma once
#include <SDL.h>
#include <vector>
#include <iostream>

class Object
{
public:
	Object();
	~Object();

	static void setRenderer(SDL_Renderer *r);
	virtual void render() = 0;

protected:
	int x, y, width, height;
	static SDL_Renderer *renderer;
};

