#ifndef MUSIX_H
#define MUSIX_H

#include <stdlib.h>
#include <stdio.h>

#include "definition.h"
#include "metric.h"
#include "map.h"

#include "include\SDL2\SDL.h"
#include "include\SDL2\SDL_image.h"
#include "include\SDL2\SDL_mixer.h"

typedef struct s_sonor {
	Mix_Music *music;
}sSonor;

void playSonor(sSonor *p_sonor);

#endif