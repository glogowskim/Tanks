#include "GameState.h"



GameState::GameState(Game *game)
{
	this->game = game;
}


GameState::~GameState()
{
}

void GameState::handleEvents(SDL_Event &e)
{
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
			this->setNextState(EXIT);
		else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
			this->setNextState(MENU);

		game->bullet[0]->handleEvent(e);
		game->tank[0]->handleEvent(e);
		game->bullet[1]->handleEvent(e);
		game->tank[1]->handleEvent(e);
	}
}

void GameState::logic()
{
	game->tank[0]->setVelocity();
	game->tank[1]->setVelocity();

	//Loop for every tank
	for (int i = 0; i < static_cast<int>(game->tank.size()); i++)
	{
		game->bullet[i]->fire(game->tank[i], 500);
		game->bullet[i]->move();
		game->tank[i]->move();

		//Check tank with tank collision
		if (game->checkCollision(game->tank[i]->getCollider(), game->tank[(i + 1) % 2]->getCollider())) game->tank[i]->undo();

		//Check bullet with tank collision
		if (game->bullet[i]->doesExist() && game->checkCollision(game->bullet[i]->getCollider(), game->tank[(i + 1) % 2]->getCollider()))
		{
			game->tank[(i + 1) % 2]->decreaseHp();
			game->bullet[i]->reset();
			game->collisionSound->play();
			if (game->tank[(i + 1) % 2]->getHp() == 0)
			{
				game->tank[(i + 1) % 2]->respawn();
				game->tank[i]->increaseScore();
			}
		}

		//Check collision with every piece of wall
		for (int j = 0; j < static_cast<int>(game->wall.size()); j++)
		{
			if (game->wall[j]->doesExist() && game->checkCollision(game->tank[i]->getCollider(), game->wall[j]->getCollider())) game->tank[i]->undo();
			if (game->wall[j]->doesExist() && game->bullet[i]->doesExist() && game->checkCollision(game->bullet[i]->getCollider(), game->wall[j]->getCollider()))
			{
				if (game->wall[j]->isDestructible())
					game->wall[j]->destroy();

				game->bullet[i]->reset();
				game->collisionSound->play();
			}
		}
	}

	//Set current score
	game->ui->setScore(game->tank[0]->getScore(), game->tank[1]->getScore());
	game->ui->setBar(game->tank[0]->getHp(), game->tank[1]->getHp());
}

void GameState::render()
{
	//Clear window
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	Object::renderAll();

	SDL_RenderPresent(renderer);
}