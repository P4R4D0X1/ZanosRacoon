#include "musix.h"



void playSonor(sSonor *p_sonor)
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096) == -1) //Initialisation de l'API Mixer
	{
		printf("ERROR : %s", Mix_GetError());
	}

	Mix_AllocateChannels(3);

	p_sonor->music = Mix_LoadMUS("./assets/songs/SuperMarioBrosCuted.wav");
	Mix_VolumeMusic(MIX_MAX_VOLUME/2);
	Mix_PlayMusic(p_sonor->music, -1);

	p_sonor->slide = Mix_LoadWAV("./assets/songs/slide.wav");
	Mix_VolumeChunk(p_sonor->slide, MIX_MAX_VOLUME/2);



}

void closeMixer(sSonor *p_sonor) {
	Mix_FreeMusic(p_sonor->music); 
	Mix_CloseAudio(); 
}