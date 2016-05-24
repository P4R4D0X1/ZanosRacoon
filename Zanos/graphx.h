#ifndef GRAPHX_H
#define GRAPHX_H

#include <stdlib.h>
#include <stdio.h>

#include "definition.h"
#include "metric.h"
#include "map.h"
#include "liste.h"
#include "pathfinding.h"
#include "musix.h"

#include "include\SDL2\SDL.h"
#include "include\SDL2\SDL_image.h"

typedef struct s_player {
	SDL_Texture *playerSprite[4];
	sPosition position;
	eDirection direction;
} sPlayer;

typedef struct s_interface {
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Event event;

	SDL_Texture *caseSprite[CASE_TYPE_AMOUNT];
	struct s_player playerGraphx;
	sPosition origin;
} sInterface;



int loadInterface(sInterface *p_interface, sMap *p_map);
int closeInterface(sInterface *p_interface);
int winCongrate(sInterface *p_interface, sMap *p_map);
int gameLoop(sInterface *p_interface, sMap *p_map);
int moovePlayer(sInterface *p_interface, sMap *p_map, eDirection p_direction);
int displayMap(sInterface *p_interface, sMap *p_map);
int solveGame(sInterface *p_interface, sMap *p_map);
bool WinOrNot(sInterface *p_interface, sMap *p_map);
//void playSong();

#endif