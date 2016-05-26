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

typedef struct s_text {
	TTF_Font *font;
	SDL_Surface *surfaceText;
	SDL_Rect posText;
	SDL_Color color;
	SDL_Texture *fontTexture;

} sText;

typedef struct s_animation {
	int frameAmount;
	int actualFrame;

	SDL_Texture **sprite;
	SDL_Rect position;
} sAnimation;

void createFont(sText *p_text, SDL_Renderer *p_renderer, char *p_message);
void closeFonts(sText p_text);
void createMenu(struct s_interface *p_interface, sMap *p_map);
void loadAnimation(int type, sAnimation **p_animation, int p_frameAmount, SDL_Rect p_position, char *p_path, struct s_interface *p_interface);
void updateAnimation(sAnimation *p_animation, struct s_interface *p_interface);
int getDigit(int p_number, int p_index);

#endif
