#include <stdlib.h>
#include <stdio.h>

#include "liste.h"
#include "map.h"
#include "pathfinding.h"
#include "graphx.h"

#include "include\SDL2\SDL.h"
#include "include\SDL2\SDL_image.h"


int main(int argc, char **argv) {

	sMap *l_map = NULL;
	sInterface l_interface;
	sSonor *l_sonor;

	loadMap(&l_map, "map.txt");
	generateGraph(l_map);
	gameLoop(&l_interface, l_map, l_sonor);

/*

	l_solutionPath = dijkstra(l_map, l_position);
	while (l_solutionPath && l_solutionPath->next) {

		SDL_RenderDrawLine(pRenderer, 50 * l_solutionPath->position.x, 50 * l_solutionPath->position.y, 50 * (l_solutionPath->next)->position.x, 50 * (l_solutionPath->next)->position.y);
		SDL_RenderPresent(pRenderer);

		l_solutionPath = l_solutionPath->next;
	}
		

	*/
	return EXIT_SUCCESS;
}