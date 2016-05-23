#include <stdlib.h>
#include <stdio.h>

#include "liste.h"
#include "map.h"
#include "pathfinding.h"

#include "include\SDL2\SDL.h"
#include "include\SDL2\SDL_image.h"

//Coucou la famille

int main(int argc, char **argv) {
	int l_i;
	bool l_loop = TRUE;

	sMap *l_map = NULL;
	sList *l_solutionPath = NULL;

	SDL_Window *l_window = NULL;
	SDL_Event ev;
	SDL_Renderer *pRenderer;
	SDL_Surface *pSprite;
	SDL_Texture *pTexture;

	loadMap(&l_map, "map.txt");
	generateGraph(l_map);
	printMap(l_map);

	l_solutionPath = dijkstra(l_map);
	printf("\n");
	printList(l_solutionPath);
/*
	if (SDL_Init(SDL_INIT_VIDEO))
	{
		fprintf(stdout, "[SDL] Initialization Error (%s)\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	l_window = SDL_CreateWindow("-RACCOON ZANOS-", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);

	if (l_window) {
		pRenderer = SDL_CreateRenderer(l_window, -1, SDL_RENDERER_ACCELERATED);
		pSprite = SDL_LoadBMP("./assets/sprite/perso_front.bmp");
		SDL_SetColorKey(pSprite, SDL_TRUE, SDL_MapRGB(pSprite->format, 12, 255, 0) );
		pTexture = SDL_CreateTextureFromSurface(pRenderer, pSprite);

		SDL_SetRenderDrawColor(pRenderer, 255, 0, 0, 255);
	//	SDL_RenderClear(pRenderer);

		SDL_Rect dest = { 640 / 2 - pSprite->w / 2,480 / 2 - pSprite->h / 2, pSprite->w, pSprite->h };
	
		while (l_loop) {
			while (SDL_PollEvent(&ev)) {
				switch (ev.type) {
					case(SDL_KEYDOWN):
						switch (ev.key.keysym.sym) {
							case(SDLK_z) :
								dest.y -= 10;
								break;
							case(SDLK_d) :
								dest.x += 10;
								break;
							case(SDLK_s) :
								dest.y += 10;
								break;
							case(SDLK_q) :
								dest.x -= 10;
								break;
							case(SDLK_x) :
								l_loop = FALSE;
								break;
						}
						break;
				}

				SDL_RenderClear(pRenderer);
				SDL_RenderCopy(pRenderer, pTexture, NULL, &dest);
				SDL_RenderPresent(pRenderer);

			}
		}
		
			SDL_RenderClear(pRenderer);

		while (l_solutionPath && l_solutionPath->next) {

			SDL_RenderDrawLine(pRenderer, 50 * l_solutionPath->position.x, 50 * l_solutionPath->position.y, 50 * (l_solutionPath->next)->position.x, 50 * (l_solutionPath->next)->position.y);
			SDL_RenderPresent(pRenderer);

			l_solutionPath = l_solutionPath->next;
		}
		
		SDL_Delay(30000); 

		SDL_DestroyTexture(pTexture);
		SDL_FreeSurface(pSprite);
		SDL_DestroyRenderer(pRenderer);

		SDL_DestroyWindow(l_window);
	}
	else {
		fprintf(stderr, "[SDL] Window creation error (%s)\n", SDL_GetError());
	}

	SDL_Quit();
	*/

	system("pause");
	return EXIT_SUCCESS;
}