#pragma once
#include "Game.h"

enum direction;
class Sound;
class Tank;

class Bullet
{
public:
	Bullet(int fireButton);
	~Bullet();

	void handleEvent(SDL_Event &e);
	void reset();
	void fire(Tank &tank, Sound &fireSound, int delay);
	void move(Sound &collisionSound);

	int getX();
	int getY();
	int getWidth();
	int getHeight();
	bool doesExist();
	direction getDirection();
	SDL_Rect getCollider();

private:
	int x;
	int y;

	int vx;
	int vy;

	bool exist;

	Uint32 buttonTicks;
	Uint32 shotTicks;

	direction dir;

	SDL_Rect collider;

	int fireButton;

	static const int width;
	static const int height;
	static const int velocity;

	bool fireButtonPressed;
};