#include "Sound.h"



Sound::Sound()
{
	sound = nullptr;
}

Sound::~Sound()
{
	clean();
}

void Sound::loadWAV(std::string path)
{
	clean();
	sound = Mix_LoadWAV(path.c_str());
}

void Sound::clean()
{
	if (sound != nullptr)
	{
		Mix_FreeChunk(sound);
		sound = nullptr;
	}
}

void Sound::play()
{
	Mix_PlayChannel(-1, sound, 0);
}