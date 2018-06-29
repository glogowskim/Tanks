#include "Game.h"

Game::Game()
{
	window = nullptr;
	renderer = nullptr;
	initialize();
}

Game::~Game()
{
	freeDynamicAllocatedMemory();

	TTF_CloseFont(font72);
	TTF_CloseFont(font48);
	TTF_CloseFont(font24);
	TTF_CloseFont(font18);
	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void Game::freeDynamicAllocatedMemory()
{
	delete state;
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
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) State::setCurrentState(EXIT);

	//Set linear filtering
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	window = SDL_CreateWindow(("TANKS " + VERSION_NUMBER).c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr) State::setCurrentState(EXIT);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) State::setCurrentState(EXIT);

	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) State::setCurrentState(EXIT);

	//Initialize TrueTypeFont
	if (TTF_Init() == -1) State::setCurrentState(EXIT);

	font72 = TTF_OpenFont("fonts/TruenoRg.otf", 72);
	if (font72 == nullptr) State::setCurrentState(EXIT);
	font48 = TTF_OpenFont("fonts/TruenoRg.otf", 48);
	if (font48 == nullptr) State::setCurrentState(EXIT);
	font24 = TTF_OpenFont("fonts/TruenoRg.otf", 24);
	if (font24 == nullptr) State::setCurrentState(EXIT);
	font18 = TTF_OpenFont("fonts/TruenoRg.otf", 18);
	if (font18 == nullptr) State::setCurrentState(EXIT);

	//Initialize audio
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0) State::setCurrentState(EXIT);

	collisionSound = new Sound();
	collisionSound->loadWAV("sounds/collision.wav");

	//Set renderer for classes
	State::setRenderer(renderer);
	Object::setRenderer(renderer);
	Texture::setRenderer(renderer);
	HpBar::setRenderer(renderer);

	state = new TitleState(font48);

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
	ui = new UI(font48, font24);
}

void Game::run()
{
	//Main loop
	while (State::getCurrentState() != EXIT)
	{
		state->handleEvents(e);
		state->logic();
		changeState();
		state->render();
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

void Game::changeState()
{
	if (State::getNextState() != NONE)
	{
		if (State::getNextState() != EXIT)
			delete state;

		switch (State::getNextState())
		{
			case TITLE:
			{
				state = new TitleState(font48);
				break;
			}
			case GAME:
			{
				state = new GameState(this);

				//This loop is needed to stop moving tank or firing bullet after state change
				//Without it tank can move or fire without button pressed (after returning from menu state)
				//It is caused by flags that cannot be changed after state change
				//That is why it have to be manually set
				for (int i = 0; i < static_cast<int>(tank.size()); i++)
				{
					tank[i]->clearButtonFlags();
					bullet[i]->clearButtonFlag();
				}
				break;
			}
			case MENU:
			{
				state = new MenuState(font72, font48);
				break;
			}
			case ABOUT:
			{
				state = new AboutState(VERSION_NUMBER, font72, font48, font24, font18);
				break;
			}
		}

		State::setCurrentState(State::getNextState());
		State::setNextState(NONE);
	}
}