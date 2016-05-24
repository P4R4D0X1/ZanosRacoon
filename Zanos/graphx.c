#include "graphx.h"

int loadInterface(sInterface *p_interface) {
	int l_i;
	char l_casePath[50] = "./assets/sprite/case_01.bmp", l_persoPath[50] = "./assets/sprite/perso_0.bmp";

	SDL_Surface *l_sprite;

	//p_interface = malloc(sizeof(sInterface));
	//p_interface->playerGraphx = malloc(sizeof(sPlayer));

	printf("%p in initialisation fonction\n", p_interface);

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
	
	//p_interface->caseSprite = malloc(sizeof(SDL_Texture*) * CASE_TYPE_AMOUNT);
	//p_interface->playerGraphx.playerSprite = malloc(sizeof(SDL_Texture*) * 4);

	for (l_i = 0; l_i < CASE_TYPE_AMOUNT; ++l_i) {
		l_casePath[21] = (int)(l_i / 10) + 48; 
		l_casePath[22] = (l_i - (int)(l_i / 10)*10) + 48;
		printf("%s \n", l_casePath);
		l_sprite = SDL_LoadBMP(l_casePath);
		p_interface->caseSprite[l_i] = SDL_CreateTextureFromSurface(p_interface->renderer, l_sprite);
		SDL_FreeSurface(l_sprite);
	}

	for (l_i = 0; l_i < 4; ++l_i) {
		l_persoPath[22] = l_i + 48;
		l_sprite = SDL_LoadBMP(l_persoPath);
		SDL_SetColorKey(l_sprite, SDL_TRUE, SDL_MapRGB(l_sprite->format, 12, 255, 0));
		p_interface->playerGraphx.playerSprite[l_i] = SDL_CreateTextureFromSurface(p_interface->renderer, l_sprite);
		SDL_FreeSurface(l_sprite);
	}

	SDL_SetRenderDrawColor(p_interface->renderer, 255, 255, 255, 255);
	SDL_RenderClear(p_interface->renderer);

	return 0;
}

int closeInterface(sInterface *p_interface) {
	int l_i;

	for (l_i = 0; l_i < CASE_TYPE_AMOUNT; ++l_i) {
		SDL_DestroyTexture(p_interface->caseSprite[l_i]);
	}

	for (l_i = 0; l_i < 4; ++l_i) {
		SDL_DestroyTexture(p_interface->playerGraphx.playerSprite[l_i]);
	}

	SDL_DestroyRenderer(p_interface->renderer);
	SDL_DestroyWindow(p_interface->window);

	return 0;
}

int gameLoop(sInterface *p_interface, sMap *p_map) {
	int l_i;
	bool l_loop = TRUE;

	displayMap(p_interface, p_map);

	while (l_loop) {
		while (SDL_PollEvent(&(p_interface->event))) {
			
			switch (p_interface->event.type) {
				case(SDL_KEYDOWN):
					switch (p_interface->event.key.keysym.sym) {
						case(SDLK_z):
							moovePlayer(p_interface, p_map, DUP);
							break;
						case(SDLK_d):
							moovePlayer(p_interface, p_map, DRIGHT);
							break;
						case(SDLK_s):
							moovePlayer(p_interface, p_map, DDOWN);
							break;
						case(SDLK_q):
							moovePlayer(p_interface, p_map, DLEFT);
							break;
						case(SDLK_ESCAPE):
							l_loop = FALSE;
							break;
					}
					break;
					
			}
		}
	}

	closeInterface(p_interface);
	SDL_Quit();

	return 0;
}

int moovePlayer(sInterface *p_interface, sMap *p_map, eDirection p_direction) {
	int l_i;

	p_interface->playerGraphx.position.x = 0;
	p_interface->playerGraphx.position.y = 0;

	SDL_Rect l_playerPosition = {p_interface->playerGraphx.position.x, p_interface->playerGraphx.position.y, WINDOW_WIDTH / 10, WINDOW_HEIGHT/ 10 };
	
	SDL_RenderCopy(p_interface->renderer, p_interface->caseSprite[p_map->path[(int)(p_interface->playerGraphx.position.x)][(int)(p_interface->playerGraphx.position.y)].type], NULL, &l_playerPosition);
	SDL_RenderCopy(p_interface->renderer, p_interface->playerGraphx.playerSprite[p_direction], NULL, &l_playerPosition);
	SDL_RenderPresent(p_interface->renderer);

	switch (p_direction) {
		case(DUP):

			break;
		case(DRIGHT):

			break;
		case(DDOWN):

			break;
		case(DLEFT):

			break;
	}

	SDL_RenderPresent(p_interface->renderer);
	return 0;
}


int displayMap(sInterface *p_interface, sMap *p_map) {
	int l_i, l_j;
	SDL_Rect posCase;
	
	posCase.x = 0;
	posCase.y = 0;
	posCase.h = WINDOW_HEIGHT / 10;
	posCase.w = WINDOW_WIDTH / 10;

	for (l_i = 0; l_i < p_map->mapDimension.height; ++l_i) {
		for (l_j = 0; l_j < p_map->mapDimension.width; ++l_j) {
			SDL_RenderCopy(p_interface->renderer, p_interface->caseSprite[ p_map->path[l_i][l_j].type ], NULL, &posCase );
			posCase.x += WINDOW_WIDTH / 10;
			printf("%d %d T: %d\n", l_i, l_j, p_map->path[l_i][l_j].type);
		}
		posCase.x = 0;
		posCase.y += WINDOW_HEIGHT / 10;
	}
	SDL_RenderPresent(p_interface->renderer); 

	return 0;
}	

