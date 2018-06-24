#include "Game.h"

Game::Game()
{
	window = nullptr;
	renderer = nullptr;
	quit = true;
	initialize();
}

Game::~Game()
{
	freeDynamicAllocatedMemory();

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

void Game::freeDynamicAllocatedMemory()
{
	delete collisionSound;
	delete ui;

	for (int i = 0; i < static_cast<int>(wall.size()); i++)
	{
		delete wall[i];
	}

	for (int i = 0; i < static_cast<int>(tank.size()); i++)
	{
		delete tank[i];
	}

	for (int i = 0; i < static_cast<int>(bullet.size()); i++)
	{
		delete bullet[i];
	}
}

void Game::initialize()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) return;

	//Set linear filtering
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	window = SDL_CreateWindow(("TANKS " + VERSION_NUMBER).c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr) return;

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) return;

	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) return;

	//Initialize TrueTypeFont
	if (TTF_Init() == -1) return;

	bigFont = TTF_OpenFont("fonts/TruenoRg.otf", 48);
	if (bigFont == nullptr) return;

	normalFont = TTF_OpenFont("fonts/TruenoRg.otf", 24);
	if (normalFont == nullptr) return;

	//Initialize audio
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0) return;
	quit = false;

	collisionSound = new Sound();
	collisionSound->loadWAV("sounds/collision.wav");

	//Set renderer for classes
	Object::setRenderer(renderer);
	Texture::setRenderer(renderer);
	HpBar::setRenderer(renderer);

	//Init static textures
	Bullet::init("images/bullet.png", "sounds/fire.wav", collisionSound);
	Tank::initTexture("images/tank.png");
	Wall::initTextures("images/wall.png", "images/solidWall.png");

	loadUI();
	loadMap();

	bullet.push_back(new Bullet(SDLK_RETURN));
	bullet.push_back(new Bullet(SDLK_SPACE));
}

void Game::loadMap()
{
	MapLoader ml("map.txt");
	ml.getWalls(wall);
	ml.getTanks(tank);
}

void Game::loadUI()
{
	ui = new UI(bigFont, normalFont);
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

			bullet[0]->handleEvent(e);
			tank[0]->handleEvent(e);
			bullet[1]->handleEvent(e);
			tank[1]->handleEvent(e);
		}

		tank[0]->setVelocity();
		tank[1]->setVelocity();

		//Loop for every tank
		for (int i = 0; i < static_cast<int>(tank.size()); i++)
		{
			bullet[i]->fire(tank[i], 500);
			bullet[i]->move();
			tank[i]->move();

			//Check tank with tank collision
			if (checkCollision(tank[i]->getCollider(), tank[(i+1)%2]->getCollider())) tank[i]->undo();

			//Check bullet with tank collision
			if (bullet[i]->doesExist() && checkCollision(bullet[i]->getCollider(), tank[(i+1)%2]->getCollider()))
			{
				tank[(i+1)%2]->decreaseHp();
				bullet[i]->reset();
				collisionSound->play();
				if (tank[(i+1)%2]->getHp() == 0)
				{
					tank[(i+1)%2]->respawn();
					tank[i]->increaseScore();
				}
			}

			//Check collision with every piece of wall
			for (int j = 0; j < static_cast<int>(wall.size()); j++)
			{
				if (wall[j]->doesExist() && checkCollision(tank[i]->getCollider(), wall[j]->getCollider())) tank[i]->undo();
				if (wall[j]->doesExist() && bullet[i]->doesExist() && checkCollision(bullet[i]->getCollider(), wall[j]->getCollider()))
				{
					if (wall[j]->isDestructable()) wall[j]->destroy();
					bullet[i]->reset();
					collisionSound->play();
				}
			}
		}

		//Set current score
		ui->setScore(tank[0]->getScore(), tank[1]->getScore());
		ui->setBar(tank[0]->getHp(), tank[1]->getHp());

		render();
	}
}

void Game::render()
{
	//Clear window
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	Object::renderAll();

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