#include "graphx.h"

int loadInterface(sInterface *p_interface) {
	int l_i;
	char l_casePath[50] = "./assets/sprite/case_01.bmp", l_persoPath[50] = "./assets/sprite/perso_0.bmp";

	SDL_Surface *l_sprite;

	p_interface = malloc(sizeof(sInterface));
	p_interface->playerGraphx = malloc(sizeof(sPlayer));

	if (SDL_Init(SDL_INIT_VIDEO)){
		fprintf(stdout, "[SDL] Initialization Error (%s)\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	p_interface->window = SDL_CreateWindow("-RACCOON ZANOS-", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	if (!(p_interface->window)) {
		fprintf(stderr, "[SDL] Window creation error (%s)\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	p_interface->renderer = SDL_CreateRenderer(p_interface->window, -1, SDL_RENDERER_ACCELERATED);
	
	p_interface->caseSprite = malloc(sizeof(SDL_Texture*) * CASE_TYPE_AMOUNT);
	p_interface->playerGraphx->playerSprite = malloc(sizeof(SDL_Texture*) * 4);

	l_sprite = SDL_LoadBMP(l_casePath);
	p_interface->caseSprite[0] = SDL_CreateTextureFromSurface(p_interface->renderer, l_sprite);
	SDL_FreeSurface(l_sprite);

	for (l_i = 1; l_i < CASE_TYPE_AMOUNT; ++l_i) {
		l_casePath[21] = (int)(l_i / 10) + 48; 
		l_casePath[22] = (l_i - (int)(l_i / 10)) + 48;
		l_sprite = SDL_LoadBMP(l_casePath);
		p_interface->caseSprite[l_i] = SDL_CreateTextureFromSurface(p_interface->renderer, l_sprite);
		SDL_FreeSurface(l_sprite);
	}

	for (l_i = 0; l_i < 4; ++l_i) {
		l_persoPath[22] = l_i + 48;
		l_sprite = SDL_LoadBMP(l_persoPath);
		SDL_SetColorKey(l_sprite, SDL_TRUE, SDL_MapRGB(l_sprite->format, 12, 255, 0));
		p_interface->playerGraphx->playerSprite[l_i] = SDL_CreateTextureFromSurface(p_interface->renderer, l_sprite);
		SDL_FreeSurface(l_sprite);
	}

	SDL_SetRenderDrawColor(p_interface->renderer, 0, 0, 0, 255);
	SDL_RenderClear(p_interface->renderer);

	/*
	SDL_Rect dest = { 10, 10, 50, 50 };
	for (l_i = 0; l_i < CASE_TYPE_AMOUNT; ++l_i) {
		SDL_RenderCopy(p_interface->renderer, p_interface->caseSprite[l_i], NULL, &dest);
		SDL_RenderPresent(p_interface->renderer);
		SDL_Delay(1000);
	}
	*/

	return 0;
}

/*
int displayMap(sInterface *p_interface, sMap *p_map) {
	int i, j;

	for (i = 0; i < p_map->mapDimension.height; ++i) {
		for (j = 0; j < p_map->mapDimension.width; ++j) {
			p_interface->caseSprite[p_map->path[i][j].type];


		}

	}


}	
*/