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
	sList *l_solutionPath = NULL;
	sInterface *l_interface = NULL;

	loadMap(&l_map, "map.txt");
	generateGraph(l_map);

	loadInterface(l_interface);
	gameLoop(l_interface, l_map);
	closeInterface(l_interface);

/*
	SDL_Window *l_window = NULL;
	SDL_Renderer *pRenderer;

	SDL_Init(SDL_INIT_VIDEO);
	l_window = SDL_CreateWindow("-RACCOON ZANOS-", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);

	pRenderer = SDL_CreateRenderer(l_window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(pRenderer, 255, 0, 0, 255);	

	l_solutionPath = dijkstra(l_map, l_position);
	while (l_solutionPath && l_solutionPath->next) {

		SDL_RenderDrawLine(pRenderer, 50 * l_solutionPath->position.x, 50 * l_solutionPath->position.y, 50 * (l_solutionPath->next)->position.x, 50 * (l_solutionPath->next)->position.y);
		SDL_RenderPresent(pRenderer);

		l_solutionPath = l_solutionPath->next;
	}
		
	SDL_Delay(3000); 

	SDL_DestroyRenderer(pRenderer);
	SDL_DestroyWindow(l_window);
	SDL_Quit();
	
	*/

	system("pause");
	return EXIT_SUCCESS;
}