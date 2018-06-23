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
	window = nullptr;
	renderer = nullptr;
	quit = true;
	initialize();
}

Game::~Game()
{
	freeDynamicAlocatedMemory();

	TTF_CloseFont(bigFont);
	bigFont = nullptr;
	TTF_CloseFont(normalFont);
	normalFont = nullptr;
	
	SDL_DestroyRenderer(renderer);
	renderer = nullptr;
	SDL_DestroyWindow(window);
	window = nullptr;

	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void Game::freeDynamicAlocatedMemory()
{
	delete scoreTank1;
	delete scoreTank2;
	delete player1;
	delete player2;
	delete player1move;
	delete player2move;
	delete player1fire;
	delete player2fire;
	delete hp1;
	delete hp2;
	delete bar1;
	delete bar2;
	delete collisionSound;
}

void Game::initialize()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) return;

	//Set linear filtering
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	window = SDL_CreateWindow("TANKS", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_SHOWN);
	if (window == nullptr) return;

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) return;

	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) return;

	//Initialize TrueTypeFont
	if (TTF_Init() == -1) return;

	bigFont = TTF_OpenFont("fonts/TruenoRg.otf", 48);
	if (bigFont == nullptr) quit = true;

	normalFont = TTF_OpenFont("fonts/TruenoRg.otf", 24);
	if (normalFont == nullptr) quit = true;

	//Initialize audio
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0) return;
	quit = false;

	collisionSound = new Sound();
	collisionSound->loadWAV("sounds/collision.wav");

	//Set renderer for classes
	Object::setRenderer(renderer);

	//Init static textures
	Bullet::init("images/bullet.png", "sounds/fire.wav", collisionSound);
	Tank::initTexture("images/tank.png");
	Wall::initTextures("images/wall.png", "images/solidWall.png");


	tank.push_back(Tank(0, 0, RIGHT, SDLK_UP, SDLK_DOWN, SDLK_LEFT, SDLK_RIGHT));
	tank.push_back(Tank(704, 704, LEFT, SDLK_w, SDLK_s, SDLK_a, SDLK_d));
	bullet.push_back(Bullet(SDLK_RETURN));
	bullet.push_back(Bullet(SDLK_SPACE));
	bar1 = new HpBar(tank[0].getMaxHp(), 150, 30, 836, 157);
	bar2 = new HpBar(tank[1].getMaxHp(), 150, 30, 836, 544);

	object.push_back(&tank[0]);
	object.push_back(&tank[1]);
	object.push_back(&bullet[0]);
	object.push_back(&bullet[1]);
	object.push_back(bar1);
	object.push_back(bar2);

	loadUI();
	loadMap();
}

void Game::loadMap()
{
	//TO-DO: Add loading map from external file
	wall.push_back(Wall(320, 0));
	wall.push_back(Wall(448, 0));
	wall.push_back(Wall(64, 64));
	wall.push_back(Wall(192, 64));
	wall.push_back(Wall(576, 64));
	wall.push_back(Wall(640, 64));
	wall.push_back(Wall(64, 128));
	wall.push_back(Wall(192, 128));
	wall.push_back(Wall(384, 128));
	wall.push_back(Wall(576, 128));
	wall.push_back(Wall(640, 128));
	wall.push_back(Wall(64, 192));
	wall.push_back(Wall(192, 192));
	wall.push_back(Wall(384, 192));
	wall.push_back(Wall(64, 256));
	wall.push_back(Wall(192, 256));
	wall.push_back(Wall(384, 256));
	wall.push_back(Wall(384, 320));
	wall.push_back(Wall(512, 320));
	wall.push_back(Wall(576, 320));
	wall.push_back(Wall(640, 320));
	wall.push_back(Wall(704, 320));
	wall.push_back(Wall(384, 384));
	wall.push_back(Wall(512, 384));
	wall.push_back(Wall(576, 384));
	wall.push_back(Wall(640, 384));
	wall.push_back(Wall(704, 384));
	wall.push_back(Wall(64, 448));
	wall.push_back(Wall(192, 448));
	wall.push_back(Wall(384, 448));
	wall.push_back(Wall(64, 512));
	wall.push_back(Wall(192, 512));
	wall.push_back(Wall(384, 512));
	wall.push_back(Wall(64, 576));
	wall.push_back(Wall(192, 576));
	wall.push_back(Wall(384, 576));
	wall.push_back(Wall(576, 576));
	wall.push_back(Wall(640, 576));
	wall.push_back(Wall(64, 640));
	wall.push_back(Wall(192, 640));
	wall.push_back(Wall(576, 640));
	wall.push_back(Wall(640, 640));
	wall.push_back(Wall(320, 704));
	wall.push_back(Wall(448, 704));
	wall.push_back(Wall(128, 192, false));
	wall.push_back(Wall(128, 576, false));

	for (int i = 0; i < wall.size(); i++)
	{
		object.push_back(&wall[i]);
	}
}

void Game::loadUI()
{
	player1 = new Texture(784, 0);
	player2 = new Texture(780, 384);
	player1move = new Texture(816, 64);
	player2move = new Texture(810, 448);
	player1fire = new Texture(816, 96);
	player2fire = new Texture(810, 480);
	hp1 = new Texture(786, 154);
	hp2 = new Texture(786, 539);
	scoreTank1 = new Texture(786, 200);
	scoreTank2 = new Texture(786, 587);

	object.push_back(player1);
	object.push_back(player2);
	object.push_back(player1move);
	object.push_back(player2move);
	object.push_back(player1fire);
	object.push_back(player2fire);
	object.push_back(hp1);
	object.push_back(hp2);
	object.push_back(scoreTank1);
	object.push_back(scoreTank2);

	player1->loadText("PLAYER 1", bigFont);
	player2->loadText("PLAYER 2", bigFont);
	player1move->loadText("Move: arrows", normalFont);
	player1fire->loadText("Fire: RETURN", normalFont);
	player2move->loadText("Move: W S A D", normalFont);
	player2fire->loadText("Fire: SPACE", normalFont);
	hp1->loadText("HP:", normalFont);
	hp2->loadText("HP:", normalFont);
}

void Game::run()
{
	//Main loop
	while (!quit)
	{
		//Checking events
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT) quit = true;
			else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) quit = true;

			bullet[0].handleEvent(e);
			tank[0].handleEvent(e);
			bullet[1].handleEvent(e);
			tank[1].handleEvent(e);
		}

		tank[0].setVelocity();
		tank[1].setVelocity();

		//Loop for every tank
		for (int i = 0; i < static_cast<int>(tank.size()); i++)
		{
			bullet[i].fire(&tank[i], 500);
			bullet[i].move();
			tank[i].move();

			//Check tank with tank collision
			if (checkCollision(tank[i].getCollider(), tank[(i+1)%2].getCollider())) tank[i].undo();

			//Check bullet with tank collision
			if (bullet[i].doesExist() && checkCollision(bullet[i].getCollider(), tank[(i+1)%2].getCollider()))
			{
				tank[(i+1)%2].decreaseHp();
				bullet[i].reset();
				collisionSound->play();
				if (tank[(i+1)%2].getHp() == 0)
				{
					tank[(i+1)%2].respawn(704, 704);
					tank[i].increaseScore();
				}
			}

			//Check collision with every piece of wall
			for (int j = 0; j < static_cast<int>(wall.size()); j++)
			{
				if (wall[j].doesExist() && checkCollision(tank[i].getCollider(), wall[j].getCollider())) tank[i].undo();
				if (wall[j].doesExist() && bullet[i].doesExist() && checkCollision(bullet[i].getCollider(), wall[j].getCollider()))
				{
					if (wall[j].isDestructable()) wall[j].destroy();
					bullet[i].reset();
					collisionSound->play();
				}
			}
		}

		//Setting current score
		score1 = "SCORE: " + std::to_string(tank[0].getScore());
		score2 = "SCORE: " + std::to_string(tank[1].getScore());
		scoreTank1->loadText(score1.c_str(), normalFont);
		scoreTank2->loadText(score2.c_str(), normalFont);

		bar1->setHp(tank[0].getHp());
		bar2->setHp(tank[1].getHp());

		render();
	}
}

void Game::render()
{
	//Clear window
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawLine(renderer, 768, 0, 768, 768);

	//Render all objects
	for (int i = 0; i < static_cast<int>(object.size()); i++)
	{
		object[i]->render();
	}

	SDL_RenderPresent(renderer);
}

bool Game::checkCollision(SDL_Rect a, SDL_Rect b)
{
	if (a.y >= b.y + b.h) return false;
	if (a.y + a.h <= b.y) return false;
	if (a.x >= b.x + b.w) return false;
	if (a.x + a.w <= b.x) return false;

	return true;
}