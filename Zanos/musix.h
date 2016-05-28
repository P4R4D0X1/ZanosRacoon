/**
* \file musix.h
* \brief Header des fonctions de rendu sonore
* \date 27 mai 2016
*
* Header qui contient les definitions des fonctions et des structures de rendu sonore
*
*/
#ifndef MUSIX_H
#define MUSIX_H

#include <stdlib.h>
#include <stdio.h>

#include "definition.h"
#include "metric.h"
#include "map.h"

#include "include\SDL2\SDL.h"
#include "include\SDL2\SDL_image.h"
#include "include\SDL2\SDL_mixer.h"

/**
* \struct sSonor
* \brief Structure qui contient les sons du jeu
*/
typedef struct s_sonor {
	Mix_Music *musicMenu;
	Mix_Music *musicGame;
	Mix_Chunk *slide;
	Mix_Chunk *applause;

}sSonor;

void loadSonor(sSonor *p_sonor);
void closeMixer(sSonor *p_sonor);

#endif