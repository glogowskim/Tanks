#pragma once
#include "Game.h"

class Sound
{
public:
	Sound();
	~Sound();
	void clean();
	void loadWAV(std::string path);
	void play();

private:
	Mix_Chunk *sound;
};