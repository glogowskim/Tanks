#include "AboutState.h"



AboutState::AboutState(std::string version, TTF_Font *font72, TTF_Font *font48, TTF_Font *font24, TTF_Font *font18)
{
	texture.push_back(new Texture(400, 50));
	texture.push_back(new Texture(460, 130));
	texture.push_back(new Texture(100, 500));
	texture.push_back(new Texture(100, 550));
	texture.push_back(new Texture(100, 600));
	texture.push_back(new Texture(100, 650));

	texture[0]->loadText("TANKS", font72);
	texture[1]->loadText(version, font48);
	texture[2]->loadText("Copyright \xa9 2018 Michal Glogowski (Szaman97)", font24);
	texture[3]->loadText("https://github.com/Szaman97", font24);
	texture[4]->loadText("License: BSD 3-Clause", font24);
	texture[5]->loadText("This software uses Simple DirectMedia Layer library", font24);
}


AboutState::~AboutState()
{
	for (int i = 0; i < static_cast<int>(texture.size()); i++)
	{
		delete texture[i];
	}
}

void AboutState::handleEvents(SDL_Event &e)
{
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
			this->setNextState(EXIT);
		else if (e.type == SDL_KEYDOWN)
			this->setNextState(MENU);
	}
}

void AboutState::logic() {}

void AboutState::render()
{
	//Clear window
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	for (auto x : texture)
	{
		x->render();
	}

	SDL_RenderPresent(renderer);
}