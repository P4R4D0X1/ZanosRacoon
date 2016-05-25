#ifndef MENU_H
#define MENU_H

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

typedef struct s_text {
	TTF_Font *font;
	SDL_Surface *surfaceText;
	SDL_Rect posText;
	SDL_Color color;
	SDL_Texture *fontTexture;

} sText;

void createFont(sText *p_text, SDL_Renderer *p_renderer, char* toWrite);
void createMenu(struct s_interface *p_interface, sMap *p_map);
void closeFonts(sText p_text);
#endif
