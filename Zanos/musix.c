#include "musix.h"


void playSonor(sSonor *p_sonor)
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096) == -1) //Initialisation de l'API Mixer
	{
		printf("ERROR : %s", Mix_GetError());
	}

	p_sonor->music = Mix_LoadMUS("SuperMarioBrosCuted.wav");

	Mix_PlayMusic(p_sonor->music, -1);
}

