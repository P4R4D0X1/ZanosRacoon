#include <stdlib.h>
#include <stdio.h>

#include "liste.h"
#include "map.h"
#include "pathfinding.h"
#include "graphx.h"

#include "include\SDL2\SDL.h"
#include "include\SDL2\SDL_image.h"


int main(int argc, char **argv) {
	bool l_loop = TRUE;

	sMap *l_map = NULL;
	sList *l_solutionPath = NULL;
	sInterface *l_interface = NULL;
	sPosition l_position;

	SDL_Window *l_window = NULL;
	SDL_Renderer *pRenderer;

	loadMap(&l_map, "map.txt");
	generateGraph(l_map);
	printMap(l_map);

	l_position.x = 8;
	l_position.y = 5;
	l_solutionPath = dijkstra(l_map, l_position);
	printf("\n");
	printList(l_solutionPath);

	//loadInterface(l_interface);


	if (SDL_Init(SDL_INIT_VIDEO))
	{
		fprintf(stdout, "[SDL] Initialization Error (%s)\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	l_window = SDL_CreateWindow("-RACCOON ZANOS-", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);

	if (l_window) {
		pRenderer = SDL_CreateRenderer(l_window, -1, SDL_RENDERER_ACCELERATED);
		SDL_SetRenderDrawColor(pRenderer, 255, 0, 0, 255);	

		while (l_solutionPath && l_solutionPath->next) {

			SDL_RenderDrawLine(pRenderer, 50 * l_solutionPath->position.x, 50 * l_solutionPath->position.y, 50 * (l_solutionPath->next)->position.x, 50 * (l_solutionPath->next)->position.y);
			SDL_RenderPresent(pRenderer);

			l_solutionPath = l_solutionPath->next;
		}
		
		SDL_Delay(3000); 

		SDL_DestroyRenderer(pRenderer);
		SDL_DestroyWindow(l_window);
	}
	else {
		fprintf(stderr, "[SDL] Window creation error (%s)\n", SDL_GetError());
	}

	SDL_Quit();
	

	system("pause");
	return EXIT_SUCCESS;
}