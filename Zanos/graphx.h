#ifndef GRAPHX_H
#define GRAPHX_H

#include <stdlib.h>
#include <stdio.h>

#include "definition.h"
#include "metric.h"
#include "map.h"

#include "include\SDL2\SDL.h"
#include "include\SDL2\SDL_image.h"

typedef struct s_interface {
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Event event;

	SDL_Texture **caseSprite;
	struct s_player *playerGraphx;
	sPosition origin;
} sInterface;


typedef struct s_player {
	SDL_Texture **playerSprite;
	sPosition position;
} sPlayer;

int loadInterface(sInterface *p_interface);
//int displayMap(sInterface *p_interface, sMap *p_map);

#endif