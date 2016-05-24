#include "musix.h"


void playSonor(sSonor *p_sonor)
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //Initialisation de l'API Mixer
	{
		printf("ERROR : %s", Mix_GetError());
	}

	if (p_sonor->music = Mix_LoadMUS("./assets/songs/SuperMarioBros.ogg") == NULL)
	{
		printf("ERROR WHEN LOADING MUSIC: %s", Mix_GetError());
	}

	Mix_VolumeMusic(MIX_MAX_VOLUME);
	if (Mix_PlayMusic(p_sonor->music, -1) == -1)
	{
		printf("ERROR WHEN PLAYING MUSIC: %s", Mix_GetError());
	}
}
