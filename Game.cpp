#include "Game.h"

enum direction
{
	UP = 0,
	RIGHT = 90,
	DOWN = 180,
	LEFT = 270
};

Game::Game()
{
	window = NULL;
	renderer = NULL;
	quit = true;
	initialize();
}


Game::~Game()
{
	TTF_CloseFont(bigFont);
	bigFont = NULL;
	TTF_CloseFont(normalFont);
	normalFont = NULL;
	
	SDL_DestroyRenderer(renderer);
	renderer = NULL;
	SDL_DestroyWindow(window);
	window = NULL;

	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}


void Game::initialize()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) return;

	//Set linear filtering
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	window = SDL_CreateWindow("TANKS", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_SHOWN);
	if (window == NULL) return;

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL) return;

	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) return;

	//Initialize TrueTypeFont
	if (TTF_Init() == -1) return;

	bigFont = TTF_OpenFont("fonts/TruenoRg.otf", 48);
	if (bigFont == NULL) quit = true;

	normalFont = TTF_OpenFont("fonts/TruenoRg.otf", 24);
	if (normalFont == NULL) quit = true;

	//Initialize audio
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0) return;
	quit = false;
}

void Game::run()
{
	Tank tank1(0, 0, RIGHT, SDLK_UP, SDLK_DOWN, SDLK_LEFT, SDLK_RIGHT);
	Tank tank2(704, 704, LEFT, SDLK_w, SDLK_s, SDLK_a, SDLK_d);

	Bullet bullet1(SDLK_RETURN);
	Bullet bullet2(SDLK_SPACE);

	Wall wall[46] = { Wall(320,0), Wall(448,0), Wall(64,64), Wall(192,64), Wall(576,64), Wall(640,64), Wall(64,128), Wall(192,128), Wall(384,128), Wall(576,128), Wall(640,128), Wall(64,192),
	Wall(192,192), Wall(384,192), Wall(64,256), Wall(192,256), Wall(384,256), Wall(384,320), Wall(512,320), Wall(576,320), Wall(640,320), Wall(704,320), Wall(384,384), Wall(512,384),
	Wall(576,384), Wall(640,384), Wall(704,384), Wall(64,448), Wall(192,448), Wall(384,448), Wall(64,512), Wall(192,512), Wall(384,512), Wall(64,576), Wall(192,576), Wall(384,576),
	Wall(576,576), Wall(640,576), Wall(64,640), Wall(192,640), Wall(576,640), Wall(640,640), Wall(320,704), Wall(448,704), Wall(128,192,false), Wall(128,576,false)};

	HpBar bar1(tank1.getMaxHp(), 150, 30, 836, 157);
	HpBar bar2(tank2.getMaxHp(), 150, 30, 836, 544);

	Texture tankTexture;
	tankTexture.loadPNG(renderer, "images/tank.png");

	Texture wallTexture;
	wallTexture.loadPNG(renderer, "images/wall.png");

	Texture solidWallTexture;
	solidWallTexture.loadPNG(renderer, "images/solidWall.png");

	Texture bulletTexture;
	bulletTexture.loadPNG(renderer, "images/bullet.png");

	Texture player1;
	player1.loadText(renderer, "PLAYER 1", bigFont);

	Texture player2;
	player2.loadText(renderer, "PLAYER 2", bigFont);

	Texture player1move;
	player1move.loadText(renderer, "Move: arrows", normalFont);

	Texture player1fire;
	player1fire.loadText(renderer,"Fire: RETURN", normalFont);
	
	Texture player2move;
	player2move.loadText(renderer, "Move: W S A D", normalFont);

	Texture player2fire;
	player2fire.loadText(renderer, "Fire: SPACE", normalFont);

	Texture hp;
	hp.loadText(renderer, "HP:", normalFont);

	Texture scoreTank1;
	Texture scoreTank2;

	Sound fireSound;
	fireSound.loadWAV("sounds/fire.wav");

	Sound collisionSound;
	collisionSound.loadWAV("sounds/collision.wav");

	//Main loop
	while (!quit)
	{
		//Checking events
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT) quit = true;
			else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) quit = true;

			bullet1.handleEvent(e);
			tank1.handleEvent(e);
			bullet2.handleEvent(e);
			tank2.handleEvent(e);
			
		}

		tank1.setVelocity();
		tank2.setVelocity();

		//Moving objects, checking collisions, firing bullets
		//tank1 and bullet1
		bullet1.fire(tank1, fireSound, 500);
		bullet1.move(collisionSound);
		tank1.move();
		if (checkCollision(tank1.getCollider(), tank2.getCollider())) tank1.undo();
		if (bullet1.doesExist() && checkCollision(bullet1.getCollider(), tank2.getCollider()))
		{
			tank2.decreaseHp();
			bullet1.reset();
			collisionSound.play();
			if (tank2.getHp() == 0)
			{
				tank2.respawn(704, 704);
				tank1.increaseScore();
			}
		}
		for (int i = 0; i < 46; i++)
		{
			if (wall[i].doesExist() && checkCollision(tank1.getCollider(), wall[i].getCollider())) tank1.undo();
			if (wall[i].doesExist() && bullet1.doesExist() && checkCollision(bullet1.getCollider(), wall[i].getCollider()))
			{
				if (wall[i].isDestructable()) wall[i].destroy();
				bullet1.reset();
				collisionSound.play();
			}
		}

		//tank2 and bullet2
		bullet2.fire(tank2, fireSound, 500);
		bullet2.move(collisionSound);
		tank2.move();
		if (checkCollision(tank2.getCollider(), tank1.getCollider())) tank2.undo();
		if (bullet2.doesExist() && checkCollision(bullet2.getCollider(), tank1.getCollider()))
		{
			tank1.decreaseHp();
			bullet2.reset();
			collisionSound.play();
			if (tank1.getHp() == 0)
			{
				tank1.respawn(0, 0);
				tank2.increaseScore();
			}
		}
		for (int i = 0; i < 46; i++)
		{
			if (wall[i].doesExist() && checkCollision(tank2.getCollider(), wall[i].getCollider())) tank2.undo();
			if (wall[i].doesExist() && bullet2.doesExist() && checkCollision(bullet2.getCollider(), wall[i].getCollider()))
			{
				if (wall[i].isDestructable()) wall[i].destroy();
				bullet2.reset();
				collisionSound.play();
			}
		}

		//Setting current score
		score1 = "SCORE: " + std::to_string(tank1.getScore());
		score2 = "SCORE: " + std::to_string(tank2.getScore());
		scoreTank1.loadText(renderer, score1.c_str(), normalFont);
		scoreTank2.loadText(renderer, score2.c_str(), normalFont);

		//Clear window
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderDrawLine(renderer, 768, 0, 768, 768);

		//Rendering objects
		tankTexture.render(renderer, tank1.getX(), tank1.getY(), (double)tank1.getDirection());
		tankTexture.render(renderer, tank2.getX(), tank2.getY(), (double)tank2.getDirection());
		if (bullet1.doesExist()) bulletTexture.render(renderer, bullet1.getX(), bullet1.getY(), (double)bullet1.getDirection());
		if (bullet2.doesExist()) bulletTexture.render(renderer, bullet2.getX(), bullet2.getY(), (double)bullet2.getDirection());

		for (int i = 0; i < 46; i++)
		{
			if (wall[i].doesExist() && wall[i].isDestructable()) wallTexture.render(renderer, wall[i].getX(), wall[i].getY());
			else if (wall[i].doesExist()) solidWallTexture.render(renderer, wall[i].getX(), wall[i].getY());
		}

		//Side panel
		player1.render(renderer, 784, 0);
		player2.render(renderer, 780, 384);
		player1move.render(renderer, 816, 64);
		player2move.render(renderer, 810, 448);
		player1fire.render(renderer, 816, 96);
		player2fire.render(renderer, 810, 480);
		hp.render(renderer, 786, 154);
		hp.render(renderer, 786, 539);

		bar1.render(renderer, tank1.getHp());
		bar2.render(renderer, tank2.getHp());

		//Score
		scoreTank1.render(renderer, 786, 200);
		scoreTank2.render(renderer, 786, 587);

		SDL_RenderPresent(renderer);
	}
}

bool Game::checkCollision(SDL_Rect a, SDL_Rect b)
{
	if (a.y >= b.y + b.h) return false;
	if (a.y + a.h <= b.y) return false;
	if (a.x >= b.x + b.w) return false;
	if (a.x + a.w <= b.x) return false;

	return true;
}