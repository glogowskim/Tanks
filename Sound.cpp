#include "Sound.h"



Sound::Sound()
{
	sound = NULL;
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
	if (sound != NULL)
	{
		Mix_FreeChunk(sound);
		sound = NULL;
	}
}

void Sound::play()
{
	Mix_PlayChannel(-1, sound, 0);
}