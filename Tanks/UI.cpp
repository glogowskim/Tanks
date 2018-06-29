#include "UI.h"



UI::UI(TTF_Font *bigFont, TTF_Font *normalFont)
{
	x = MAP_WIDTH;
	y = 0;
	width = SCREEN_WIDTH - MAP_WIDTH;
	height = SCREEN_HEIGHT;

	this->bigFont = bigFont;
	this->normalFont = normalFont;

	background = { x,y,width,height };

	texture.push_back(new Texture(784, 0));
	texture.push_back(new Texture(780, 384));
	texture.push_back(new Texture(816, 64));
	texture.push_back(new Texture(810, 448));
	texture.push_back(new Texture(816, 96));
	texture.push_back(new Texture(810, 480));
	texture.push_back(new Texture(786, 154));
	texture.push_back(new Texture(786, 539));
	texture.push_back(new Texture(786, 200));
	texture.push_back(new Texture(786, 587));

	texture[static_cast<int>(TextureUI::PLAYER1)]->loadText("PLAYER 1", bigFont);
	texture[static_cast<int>(TextureUI::PLAYER2)]->loadText("PLAYER 2", bigFont);
	texture[static_cast<int>(TextureUI::PLAYER1MOVE)]->loadText("Move: arrows", normalFont);
	texture[static_cast<int>(TextureUI::PLAYER2MOVE)]->loadText("Move: W S A D", normalFont);
	texture[static_cast<int>(TextureUI::PLAYER1FIRE)]->loadText("Fire: RETURN", normalFont);
	texture[static_cast<int>(TextureUI::PLAYER2FIRE)]->loadText("Fire: SPACE", normalFont);
	texture[static_cast<int>(TextureUI::HP1)]->loadText("HP:", normalFont);
	texture[static_cast<int>(TextureUI::HP2)]->loadText("HP:", normalFont);
	reset();

	bar1 = new HpBar(Tank::getMaxHp(), 150, 30, 836, 157);
	bar2 = new HpBar(Tank::getMaxHp(), 150, 30, 836, 544);
}


UI::~UI()
{
	for (int i = 0; i < static_cast<int>(texture.size()); i++)
	{
		delete texture[i];
	}

	delete bar1;
	delete bar2;
}

void UI::render()
{
	//Render UI
	SDL_SetRenderDrawColor(renderer, 32, 32, 32, 255);
	SDL_RenderFillRect(renderer, &background);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawLine(renderer, x, y, x, y + height);

	//Render all textures
	for (int i = 0; i < static_cast<int>(texture.size()); i++)
	{
		texture[i]->render();
	}

	bar1->render();
	bar2->render();
}

void UI::reset()
{
	texture[static_cast<int>(TextureUI::SCORETANK1)]->loadText("SCORE: 0", normalFont);
	texture[static_cast<int>(TextureUI::SCORETANK2)]->loadText("SCORE: 0", normalFont);
}

void UI::setBar(int player1, int player2)
{
	bar1->setHp(player1);
	bar2->setHp(player2);
}

void UI::setScore(int player1, int player2)
{
	score1 = "SCORE: " + std::to_string(player1);
	score2 = "SCORE: " + std::to_string(player2);
	texture[static_cast<int>(TextureUI::SCORETANK1)]->loadText(score1.c_str(), normalFont);
	texture[static_cast<int>(TextureUI::SCORETANK2)]->loadText(score2.c_str(), normalFont);
}