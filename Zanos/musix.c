#include "musix.h"


/*

*/

void playSonor(sSonor *p_sonor)
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //Initialisation de l'API Mixer
	{
		printf("%s", Mix_GetError());
	}

	p_sonor->music = Mix_LoadMUS("./assets/songs/SuperMarioBros.mp3");
	Mix_PlayMusic(p_sonor->music, -1);
}
