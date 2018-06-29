#include "MenuState.h"



MenuState::MenuState(TTF_Font *font72, TTF_Font *font48)
{
	currentChoice = static_cast<int>(Menu::RESUME);
	returnPressed = false;
	background = { menuBeginX - 50,menuBeginY - 160,320,400 };
	currentChoiceRect = { menuBeginX,menuBeginY+7,230,50 };

	texture.push_back(new Texture(menuBeginX, menuBeginY));
	texture.push_back(new Texture(menuBeginX, menuBeginY + 50));
	texture.push_back(new Texture(menuBeginX, menuBeginY + 100));
	texture.push_back(new Texture(menuBeginX, menuBeginY + 150));
	texture.push_back(new Texture(menuBeginX, 200));

	texture[static_cast<int>(Menu::RESUME)]->loadText("RESUME", font48);
	texture[static_cast<int>(Menu::RESTART)]->loadText("RESTART", font48);
	texture[static_cast<int>(Menu::ABOUT)]->loadText("ABOUT", font48);
	texture[static_cast<int>(Menu::EXIT)]->loadText("EXIT", font48);
	texture[static_cast<int>(Menu::MENUTITLE)]->loadText("MENU", font72);
}


MenuState::~MenuState()
{
	for (int i = 0; i < static_cast<int>(texture.size()); i++)
	{
		delete texture[i];
	}
}

void MenuState::handleEvents(SDL_Event &e)
{
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
			this->setNextState(EXIT);
		else if (e.type == SDL_KEYDOWN)
		{
			switch (e.key.keysym.sym)
			{
				case SDLK_ESCAPE:
				{
					this->setNextState(GAME);
					break;
				}
				case SDLK_UP:
				{
					currentChoice--;
					break;
				}
				case SDLK_DOWN:
				{
					currentChoice++;
					break;
				}
				case SDLK_RETURN:
				{
					returnPressed = true;
					break;
				}
			}
		}
	}
}

void MenuState::logic()
{
	//Correct current element when its out of range
	if (currentChoice < 0)
		currentChoice = menuElements - 1;
	else if (currentChoice >= menuElements)
		currentChoice = 0;

	if (returnPressed)
	{
		switch (currentChoice)
		{
			case (int)Menu::RESUME:
			{
				this->setNextState(GAME);
				break;
			}
			case (int)Menu::RESTART:
			{
				this->setNextState(GAME);
				Object::resetAll();
				break;
			}
			case (int)Menu::ABOUT:
			{
				this->setNextState(ABOUT);
				break;
			}
			case (int)Menu::EXIT:
			{
				this->setNextState(EXIT);
				break;
			}
		}
	}

	//Change position of the rectangle
	currentChoiceRect.y = menuBeginY + 7 + currentChoice * 50;
}

void MenuState::render()
{
	//Clear window
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	Object::renderAll();

	SDL_SetRenderDrawColor(renderer, 32, 32, 32, 255);
	SDL_RenderFillRect(renderer, &background);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawRect(renderer, &background);

	for (auto x : texture)
	{
		x->render();
	}

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawLine(renderer, menuBeginX, 280, menuBeginX + 220, 280);
	SDL_RenderDrawLine(renderer, menuBeginX, 283, menuBeginX + 220, 283);
	SDL_RenderDrawLine(renderer, menuBeginX, 286, menuBeginX + 220, 286);
	SDL_RenderDrawRect(renderer, &currentChoiceRect);

	SDL_RenderPresent(renderer);
}