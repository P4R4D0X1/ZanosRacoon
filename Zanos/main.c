#include <stdlib.h>
#include <stdio.h>

#include "liste.h"
#include "map.h"
#include "pathfinding.h"
#include "graphx.h"
#include "menu.h"

#include "include\SDL2\SDL.h"
#include "include\SDL2\SDL_image.h"


int main(int argc, char **argv) {

	sMap *l_map = NULL;
	sInterface l_interface;
	sText l_text;

	loadMap(&l_map, "map.txt");
	generateGraph(l_map);

	loadInterface(&l_interface, l_map);
	//createMenu(&l_interface, &l_text);

	gameLoop(&l_interface, l_map);
	return EXIT_SUCCESS;
}