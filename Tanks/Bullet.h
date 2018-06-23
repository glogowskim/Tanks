#pragma once
#include "Game.h"

enum direction;
class Sound;
class Tank;
class Texture;

class Bullet : public Object
{
public:
	Bullet(int fireButton);
	~Bullet();

	static void init(std::string texturePath, std::string fireSoundPath, Sound *collisionSound);

	//Render bullet if exist
	virtual void render();
	void handleEvent(SDL_Event &e);
	void reset();
	void fire(Tank *tank, int delay);
	void move();

	bool doesExist();
	direction getDirection();
	SDL_Rect getCollider();

private:
	int vx;
	int vy;

	bool exist;

	Uint32 buttonTicks;
	Uint32 shotTicks;

	direction dir;

	SDL_Rect collider;

	int fireButton;
	bool fireButtonPressed;

	static const int velocity;
	static Texture texture;
	static Sound fireSound;
	static Sound *collisionSound;
};