#ifndef MENU_H
#define MENU_H

#include <stdlib.h>
#include <stdio.h>

#include "definition.h"
#include "metric.h"
#include "map.h"

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

void createMenu(sText *p_text);
void closeFonts(font);

#endif