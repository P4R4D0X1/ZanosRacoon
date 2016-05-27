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
#include "include\SDL2\SDL_ttf.h"


typedef struct s_player {
	SDL_Texture *playerSprite[4];
	SDL_Rect realPosition;
	SDL_Rect realDestination;

	bool isSliding;
	sPosition mapPosition;
	eDirection direction;
} sPlayer;

typedef struct s_effect {
	SDL_Texture *particleSprite[3];
	struct s_particleSystem *particle;
}sEffect;

typedef struct s_interface {
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Event event;

	SDL_Texture *caseSprite[CASE_TYPE_AMOUNT];
	SDL_Texture *backgroundSprite;
	SDL_Texture *cursor;

	struct s_player player;
	struct s_effect effect;
	sSonor sonor;
	sList *solution;
	sPosition origin;
	int compteur;
} sInterface;


int loadInterface(sInterface *p_interface);
int closeInterface(sInterface *p_interface);

int gameLoop(sInterface *p_interface, sMap *p_map);
int updateGoal(sInterface *p_interface, sMap *p_map, eDirection p_direction);
int updateVision(sInterface *p_interface, sMap *p_map);

int displayMap(sInterface *p_interface, sMap *p_map);
int showSolution(sInterface *p_interface, sList *p_solutionPath);

bool WinOrNot(sInterface *p_interface, sMap *p_map);
SDL_Rect getRealPosition(sPosition p_position);
sPosition getMapPosition(SDL_Rect p_position);
bool comparePositionRect(SDL_Rect p_firstPosition, SDL_Rect p_secondPosition);
bool comparePositionMap(sPosition p_firstPosition, sPosition p_secondPosition);

//void playSong();

#endif