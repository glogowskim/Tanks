#include "TitleState.h"



TitleState::TitleState(TTF_Font *font)
{
	background = new Texture();
	background->loadPNG("images/title.png");

	info = new Texture();
	info->loadText("Press any key to start", font);
	info->setPosition(250, 550);
}


TitleState::~TitleState()
{
	delete background;
	delete info;
}

void TitleState::handleEvents(SDL_Event &e)
{
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
			this->setNextState(EXIT);
		else if (e.type == SDL_KEYDOWN)
			this->setNextState(GAME);
	}
}

void TitleState::logic() {}

void TitleState::render()
{
	//Clear window
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	background->render();
	info->render();

	SDL_RenderPresent(renderer);
}