#pragma once
#include <SDL.h>
#include <vector>

class Object
{
public:
	Object();
	~Object();

	static void setRenderer(SDL_Renderer *r);
	static void renderAll();
	virtual void render() = 0;

protected:
	int x, y, width, height;
	static SDL_Renderer *renderer;
	static std::vector<Object*> object;
};

