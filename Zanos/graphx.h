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

typedef struct s_interface {
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Event event;

	SDL_Texture *caseSprite[CASE_TYPE_AMOUNT];
	struct s_player player;
	sPosition origin;
} sInterface;

typedef struct s_text {
	TTF_Font *font;
	SDL_Surface *surfaceText;
	SDL_Rect posText;
	SDL_Color color;
	SDL_Texture *fontTexture;

} sText;


int loadInterface(sInterface *p_interface, sMap *p_map);
int closeInterface(sInterface *p_interface);

int gameLoop(sInterface *p_interface, sMap *p_map);
int updateGoal(sInterface *p_interface, sMap *p_map, eDirection p_direction);
int updateVision(sInterface *p_interface, sMap *p_map);

int displayMap(sInterface *p_interface, sMap *p_map);
int solveGame(sInterface *p_interface, sMap *p_map);

bool WinOrNot(sInterface *p_interface, sMap *p_map);
SDL_Rect getRealPosition(sPosition p_position);
sPosition getMapPosition(SDL_Rect p_position);
bool comparePositionRect(SDL_Rect p_firstPosition, SDL_Rect p_secondPosition);
bool comparePositionMap(sPosition p_firstPosition, sPosition p_secondPosition);

void createFont(sText *p_text, SDL_Renderer *p_renderer, char* toWrite);
void createMenu(sInterface *p_interface, sMap *p_map);
void closeFonts(sText p_text);
//void playSong();

#endif