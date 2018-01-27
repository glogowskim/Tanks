#include "Bullet.h"

enum direction
{
	UP = 0,
	RIGHT = 90,
	DOWN = 180,
	LEFT = 270
};

const int Bullet::width = 6;
const int Bullet::height = 12;
const int Bullet::velocity = 10;


Bullet::Bullet(int fireButton)
{
	this->fireButton = fireButton;
	reset();

	fireButtonPressed = false;

	shotTicks = 0;
	buttonTicks = 0;
}


Bullet::~Bullet()
{
}

void Bullet::handleEvent(SDL_Event &e)
{
	if (e.type == SDL_KEYDOWN && e.key.keysym.sym == fireButton) fireButtonPressed = true;
	else if (e.type == SDL_KEYUP && e.key.keysym.sym == fireButton) fireButtonPressed = false;
}

void Bullet::reset()
{
	x = 0;
	y = 0;
	vx = 0;
	vy = 0;
	collider = { 0,0,0,0 };

	dir = UP;

	exist = false;
}

void Bullet::fire(Tank &tank, Sound &fireSound, int delay)
{
	if (fireButtonPressed)
	{
		//Get current ticks
		buttonTicks = SDL_GetTicks();

		//If bullet does not exist and the time from last firing is greater than latency
		if (!exist && buttonTicks - delay > shotTicks)
		{
			//Update fire ticks
			shotTicks = buttonTicks;
			
			dir = tank.dir;

			//Set x,y based on tank coordinates and direction
			switch (dir)
			{
				case UP:
				{
					x = tank.x + tank.width / 2 - width / 2;
					y = tank.y - height;
					break;
				}
				case DOWN:
				{
					x = tank.x + tank.width / 2 - width / 2;
					y = tank.y + tank.height;
					break;
				}
				case LEFT:
				{
					x = tank.x - height;
					y = tank.y + tank.height / 2 - width / 2;
					break;
				}
				case RIGHT:
				{
					x = tank.x + tank.width;
					y = tank.y + tank.height / 2 - width / 2;
				}
			}

			exist = true;
			fireSound.play();

			collider.x = x;
			collider.y = y;

			//Flip collider box when necessary
			if (dir == UP || dir == DOWN)
			{
				collider.w = width;
				collider.h = height;
			}
			else if (dir == LEFT || dir == RIGHT)
			{
				collider.w = height;
				collider.h = width;
			}

			//Set velocity of the bullet based on direction 
			switch (dir)
			{
				case UP:
				{
					vy -= velocity;
					break;
				}
				case DOWN:
				{
					vy += velocity;
					break;
				}
				case LEFT:
				{
					vx -= velocity;
					break;
				}
				case RIGHT:
				{
					vx += velocity;
					break;
				}
			}
		}
	}
}

void Bullet::move(Sound &collisionSound)
{
	x += vx;
	collider.x = x;

	if ((x < 0) || (x + width > 768))
	{
		reset();
		collisionSound.play();
	}

	y += vy;
	collider.y = y;

	if ((y < 0) || (y + height > 768))
	{
		reset();
		collisionSound.play();
	}
}

int Bullet::getX()
{
	return x;
}

int Bullet::getY()
{
	return y;
}

int Bullet::getWidth()
{
	return width;
}

int Bullet::getHeight()
{
	return height;
}

bool Bullet::doesExist()
{
	return exist;
}

direction Bullet::getDirection()
{
	return dir;
}

SDL_Rect Bullet::getCollider()
{
	return collider;
}