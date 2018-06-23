#include "Tank.h"

enum direction
{
	UP = 0,
	RIGHT = 90,
	DOWN = 180,
	LEFT = 270
};

const int Tank::velocity = 2;
const int Tank::maxHp = 4;

Texture Tank::texture;

Tank::Tank(int x, int y, direction d, int up, int down, int left, int right)
{
	respawn(x, y);

	width = 60;
	height = 60;

	vx = 0;
	vy = 0;

	collider.w = width;
	collider.h = height;

	dir = d;

	score = 0;

	//Set steering keys
	this->up = up;
	this->down = down;
	this->left = left;
	this->right = right;

	upButtonPressed = false;
	downButtonPressed = false;
	leftButtonPressed = false;
	rightButtonPressed = false;

	upTicks = 0;
	downTicks = 0;
	leftTicks = 0;
	rightTicks = 0;
}


Tank::~Tank()
{
}

void Tank::handleEvent(SDL_Event &e)
{
	//If button has been pressed
	if (e.type == SDL_KEYDOWN)
	{
		if (e.key.keysym.sym == up)
		{
			upButtonPressed = true;
			upTicks = SDL_GetTicks();
		}
		else if (e.key.keysym.sym == down)
		{
			downButtonPressed = true;
			downTicks = SDL_GetTicks();
		}
		else if (e.key.keysym.sym == left)
		{
			leftButtonPressed = true;
			leftTicks = SDL_GetTicks();
		}
		else if (e.key.keysym.sym == right)
		{
			rightButtonPressed = true;
			rightTicks = SDL_GetTicks();
		}
	}

	//If button has been released
	if (e.type == SDL_KEYUP)
	{
		if (e.key.keysym.sym == up) upButtonPressed = false;
		else if (e.key.keysym.sym == down) downButtonPressed = false;
		else if (e.key.keysym.sym == left) leftButtonPressed = false;
		else if (e.key.keysym.sym == right) rightButtonPressed = false;
	}
}

void Tank::setVelocity()
{
	//If any steering button is pressed
	if (upButtonPressed || downButtonPressed || leftButtonPressed || rightButtonPressed)
	{
		if (upTicks > downTicks && upTicks > leftTicks && upTicks > rightTicks && upButtonPressed)
		{
			vx = 0;
			vy = -velocity;
			dir = UP;
		}
		else if (downTicks > upTicks && downTicks > leftTicks && downTicks > rightTicks && downButtonPressed)
		{
			vx = 0;
			vy = velocity;
			dir = DOWN;
		}
		else if (leftTicks > upTicks && leftTicks > downTicks && leftTicks > rightTicks && leftButtonPressed)
		{
			vx = -velocity;
			vy = 0;
			dir = LEFT;
		}
		else if (rightTicks > upTicks && rightTicks > downTicks && rightTicks > leftTicks && rightButtonPressed)
		{
			vx = velocity;
			vy = 0;
			dir = RIGHT;
		}
		else
		{
			vx = 0;
			vy = 0;
		}
	}
	else 
	{
		vx = 0;
		vy = 0;
	}
}

void Tank::move()
{
	x += vx;
	collider.x = x;

	if ((x < 0) || (x + width > 768))
	{
		x -= vx;
		collider.x = x;
	}

	y += vy;
	collider.y = y;

	if ((y < 0) || (y + height > 768))
	{
		y -= vy;
		collider.y = y;
	}
}

void Tank::undo()
{
	x -= vx;
	collider.x = x;

	y -= vy;
	collider.y = y;
}

void Tank::respawn(int x, int y)
{
	this->x = x;
	this->y = y;
	hp = maxHp;
}

int Tank::getX()
{
	return x;
}

int Tank::getY()
{
	return y;
}

int Tank::getWidth()
{
	return width;
}

int Tank::getHeight()
{
	return height;
}

int Tank::getHp()
{
	return hp;
}

int Tank::getMaxHp()
{
	return maxHp;
}

unsigned int Tank::getScore()
{
	return score;
}

direction Tank::getDirection()
{
	return dir;
}

SDL_Rect Tank::getCollider()
{
	return collider;
}

void Tank::decreaseHp()
{
	hp--;
}

void Tank::increaseScore()
{
	score++;
}

void Tank::initTexture(std::string path)
{
	texture.loadPNG(path);
}

void Tank::render()
{
	texture.render(x, y, static_cast<double>(dir));
}