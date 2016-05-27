/**
* \file graphx.h
* \brief Header des fonctions de rendu, d'affichage et d'interfacage avec l'utilisateur
* \date 27 mai 2016
*
* Header qui contient les definitions des fonctions et des structures de rendu, d'affichage et d'interfacage
*
*/
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


/**
* \struct sPlayer
* \brief Structure qui représente le personnage que l'on incarne
*/
typedef struct s_player {
	SDL_Texture *playerSprite[4];
	SDL_Rect realPosition;
	SDL_Rect realDestination;

	bool isSliding;
	sPosition mapPosition;
	eDirection direction;
} sPlayer;

/**
* \struct sEffect
* \brief Structure qui représente les effets de l'enigme
*/
typedef struct s_effect {
	SDL_Texture *particleSprite[3];
	struct s_particleSystem *particle;
}sEffect;

/**
* \struct sInterface
* \brief Structure qui représente l'interface de l'enigme
*/
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

#endif