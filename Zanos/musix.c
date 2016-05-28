/**
* \file musix.c
* \brief Programme de rendu sonor
* \date 27 mai 2016
*
* Programme qui initialise les structures de son et charge les musiques
*
*/
#include "musix.h"

/**
* \fn void loadSonor(sSonor *p_sonor)
* \brief Fonction de chargement des son du jeu
*
* \param *p_sonor structure qui contient les sons du jeu
*/
void loadSonor(sSonor *p_sonor)
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096) == -1) //Initialisation de l'API Mixer
	{
		printf("ERROR : %s", Mix_GetError());
	}

	Mix_AllocateChannels(3);

	p_sonor->musicMenu = Mix_LoadMUS("./assets/songs/menu.wav");
	Mix_VolumeMusic(MIX_MAX_VOLUME/2);

	p_sonor->musicGame = Mix_LoadMUS("./assets/songs/game.wav");
	Mix_VolumeMusic(MIX_MAX_VOLUME / 2);

	p_sonor->slide = Mix_LoadWAV("./assets/songs/slide.wav");
	Mix_VolumeChunk(p_sonor->slide, MIX_MAX_VOLUME/2);

	p_sonor->applause = Mix_LoadWAV("./assets/songs/levelUp.wav");
	Mix_VolumeChunk(p_sonor->applause, MIX_MAX_VOLUME / 2);
}

/**
* \fn void closeMixer(sSonor *p_sonor)
* \brief Fonction de dechargement des son du jeu
*
* \param *p_sonor structure qui contient les sons du jeu
*/
void closeMixer(sSonor *p_sonor) {
	Mix_FreeMusic(p_sonor->musicGame);
	Mix_FreeMusic(p_sonor->musicMenu);
	Mix_CloseAudio(); 
}