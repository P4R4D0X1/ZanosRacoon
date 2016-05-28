/**
* \file menu.h
* \brief Header des fonctions de rendu, d'affichage et d'interfacage entre l'utilisateur et le menu de l'enigme
* \date 27 mai 2016
*
* Header qui contient les definitions des fonctions et des structures de rendu, d'affichage et d'interfacage
*
*/
#ifndef MENU_H
#define MENU_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

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
* \struct sAnimation
* \brief Structure qui représente une animation
*/
typedef struct s_animation {
	int frameAmount;
	int actualFrame;
	int speed;
	int load;

	SDL_Texture **sprite;
	SDL_Rect position;
} sAnimation;

void displayText(SDL_Renderer *p_renderer, char *p_message, SDL_Color p_color, SDL_Rect p_position);
void createMenu();
void loadAnimation(int type, sAnimation **p_animation, int p_frameAmount, SDL_Rect p_position, char *p_path, struct s_interface *p_interface, int p_speed);
void freeAnimation(sAnimation *p_animation);
void updateAnimation(sAnimation *p_animation, struct s_interface *p_interface);
int getDigit(int p_number, int p_index);
void centrerPosition(SDL_Rect *p_posSprite, SDL_Rect p_offset);

#endif
