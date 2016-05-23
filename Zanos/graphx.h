#ifndef GRAPHX_H
#define GRAPHX_H

#include <stdlib.h>
#include <stdio.h>

#include "definition.h"
#include "metric.h"

#include "include\SDL2\SDL.h"
#include "include\SDL2\SDL_image.h"


typedef struct s_interface {
	sPosition origin;
	SDL_Texture **t_case;
} sInterface;


typedef struct s_player {
	SDL_Texture **t_player;
	sPosition position;
} sPlayer;


	


#endif