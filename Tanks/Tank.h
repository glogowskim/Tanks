#pragma once
#include "Game.h"

enum direction;
class Texture;

class Tank : public Object
{
public:
	Tank(int x, int y, direction d, int up, int down, int left, int right);
	~Tank();

	static void initTexture(std::string path);
	static int getMaxHp();

	virtual void render();
	void handleEvent(SDL_Event &e);
	void move();
	void undo();
	void respawn(int x, int y);
	void respawn();
	void setVelocity();

	int getX();
	int getY();
	int getWidth();
	int getHeight();
	int getHp();
	unsigned int getScore();
	direction getDirection();
	SDL_Rect getCollider();

	void decreaseHp();
	void increaseScore();

	friend class Bullet;

private:
	int respawnX;
	int respawnY;

	//Velocity of the tank
	int vx;
	int vy;

	int hp;
	unsigned int score;
	direction dir;

	//Collider box
	SDL_Rect collider;

	//Steering keys
	int up;
	int down;
	int left;
	int right;

	//Flags storing information if a button is pressed
	bool upButtonPressed;
	bool downButtonPressed;
	bool leftButtonPressed;
	bool rightButtonPressed;

	//Variables storing ticks from button pressing
	Uint32 upTicks;
	Uint32 downTicks;
	Uint32 leftTicks;
	Uint32 rightTicks;

	static const int velocity;
	static const int maxHp;

	static Texture texture;
};