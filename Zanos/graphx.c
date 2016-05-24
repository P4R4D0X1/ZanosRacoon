#include "graphx.h"

int loadInterface(sInterface *p_interface, sMap *p_map) {
	int l_i;
	char l_casePath[50] = "./assets/sprite/case_01.bmp", l_persoPath[50] = "./assets/sprite/perso_0.bmp";

	SDL_Surface *l_sprite;

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

	for (l_i = 0; l_i < CASE_TYPE_AMOUNT; ++l_i) {
		l_casePath[21] = (int)(l_i / 10) + 48; 
		l_casePath[22] = (l_i - (int)(l_i / 10)*10) + 48;
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

	p_interface->playerGraphx.position.x = p_map->starting.x;
	p_interface->playerGraphx.position.y = p_map->starting.y;
	p_interface->playerGraphx.direction = DUP;

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



int gameLoop(sInterface *p_interface, sMap *p_map, sSonor *p_sonor) {
	
	bool l_loop = TRUE, l_solve = FALSE;
	
	loadInterface(p_interface, p_map);
	displayMap(p_interface, p_map);

	while (l_loop)
	{

		if(SDL_PollEvent(&(p_interface->event))) {
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
						case(SDLK_x):
							l_solve = !l_solve;
							break;
						case(SDLK_ESCAPE):
							l_loop = FALSE;
							break;
					}
					break;
			}
			while (SDL_PollEvent(&(p_interface->event)));
			if (l_solve) {
				displayMap(p_interface, p_map);
				solveGame(p_interface, p_map);
			}
		}
	}

	closeInterface(p_interface);
	Mix_FreeMusic(p_sonor->music);
	Mix_CloseAudio();
	SDL_Quit();

	return 0;
}

int moovePlayer(sInterface *p_interface, sMap *p_map, eDirection p_direction) {

	sCase *l_currentCase;

	SDL_Rect l_playerPosition = { (float)(p_interface->playerGraphx.position.x * (WINDOW_WIDTH / 10)), (float)(p_interface->playerGraphx.position.y * (WINDOW_HEIGHT / 10)), WINDOW_WIDTH / 10, WINDOW_HEIGHT / 10 };
	SDL_Rect l_casePosition = { 0, 0, WINDOW_WIDTH / 10, WINDOW_HEIGHT / 10 };
	SDL_Rect l_casePositionNext = { 0, 0, WINDOW_WIDTH / 10, WINDOW_HEIGHT / 10 };

	SDL_RenderCopy(p_interface->renderer, p_interface->caseSprite[p_map->path[(int)(p_interface->playerGraphx.position.y)][(int)(p_interface->playerGraphx.position.x)].type], NULL, &l_playerPosition);
	SDL_RenderCopy(p_interface->renderer, p_interface->playerGraphx.playerSprite[p_direction], NULL, &l_playerPosition);
	SDL_RenderPresent(p_interface->renderer);


	l_currentCase = &(p_map->path[(int)(p_interface->playerGraphx.position.y)][(int)(p_interface->playerGraphx.position.x)]);
	p_interface->playerGraphx.direction = p_direction;

	switch (p_direction) {
	case(DUP):
		if (l_currentCase->node.neighbourUP) {
			for (p_interface->playerGraphx.position.y; p_interface->playerGraphx.position.y > l_currentCase->node.neighbourUP->position.y; p_interface->playerGraphx.position.y--) {
				l_playerPosition.y = p_interface->playerGraphx.position.y * (WINDOW_HEIGHT / 10);
				l_casePosition.x = p_interface->playerGraphx.position.x * (WINDOW_WIDTH / 10);
				l_casePosition.y = p_interface->playerGraphx.position.y * (WINDOW_HEIGHT / 10);
				l_casePositionNext.x = l_casePosition.x;
				l_casePositionNext.y = l_casePosition.y - (WINDOW_HEIGHT / 10);

				for (l_playerPosition.y; l_playerPosition.y >= l_casePositionNext.y; l_playerPosition.y -= ((WINDOW_HEIGHT / 10)) / 10) {
					SDL_RenderCopy(p_interface->renderer, p_interface->caseSprite[p_map->path[(int)(p_interface->playerGraphx.position.y)][(int)(p_interface->playerGraphx.position.x)].type], NULL, &l_casePosition);
					SDL_RenderCopy(p_interface->renderer, p_interface->caseSprite[p_map->path[(int)(p_interface->playerGraphx.position.y - 1)][(int)(p_interface->playerGraphx.position.x)].type], NULL, &l_casePositionNext);
					SDL_RenderCopy(p_interface->renderer, p_interface->playerGraphx.playerSprite[p_direction], NULL, &l_playerPosition);
					SDL_RenderPresent(p_interface->renderer);
					SDL_Delay(SDL_ANIMATION_FRAMETIME);
				}
			}
		}
		break;

	case(DRIGHT):
		if (l_currentCase->node.neighbourRIGHT) {
			for (p_interface->playerGraphx.position.x; p_interface->playerGraphx.position.x < l_currentCase->node.neighbourRIGHT->position.x; p_interface->playerGraphx.position.x++) {
				l_playerPosition.x = p_interface->playerGraphx.position.x * (WINDOW_HEIGHT / 10);
				l_casePosition.x = p_interface->playerGraphx.position.x * (WINDOW_WIDTH / 10);
				l_casePosition.y = p_interface->playerGraphx.position.y * (WINDOW_HEIGHT / 10);
				l_casePositionNext.x = l_casePosition.x + (WINDOW_HEIGHT / 10);
				l_casePositionNext.y = l_casePosition.y;
				for (l_playerPosition.x; l_playerPosition.x <= l_casePositionNext.x; l_playerPosition.x += ((WINDOW_HEIGHT / 10)) / 10) {
					SDL_RenderCopy(p_interface->renderer, p_interface->caseSprite[p_map->path[(int)(p_interface->playerGraphx.position.y)][(int)(p_interface->playerGraphx.position.x)].type], NULL, &l_casePosition);
					SDL_RenderCopy(p_interface->renderer, p_interface->caseSprite[p_map->path[(int)(p_interface->playerGraphx.position.y)][(int)(p_interface->playerGraphx.position.x + 1)].type], NULL, &l_casePositionNext);
					SDL_RenderCopy(p_interface->renderer, p_interface->playerGraphx.playerSprite[p_direction], NULL, &l_playerPosition);
					SDL_RenderPresent(p_interface->renderer);
					SDL_Delay(SDL_ANIMATION_FRAMETIME);
				}
			}
		}
		break;

	case(DDOWN):
		if (l_currentCase->node.neighbourDOWN) {

			for (p_interface->playerGraphx.position.y; p_interface->playerGraphx.position.y < l_currentCase->node.neighbourDOWN->position.y; p_interface->playerGraphx.position.y++) {
				l_playerPosition.y = p_interface->playerGraphx.position.y * (WINDOW_HEIGHT / 10);
				l_casePosition.x = p_interface->playerGraphx.position.x * (WINDOW_WIDTH / 10);
				l_casePosition.y = p_interface->playerGraphx.position.y * (WINDOW_HEIGHT / 10);
				l_casePositionNext.x = l_casePosition.x;
				l_casePositionNext.y = l_casePosition.y + (WINDOW_HEIGHT / 10);
				for (l_playerPosition.y; l_playerPosition.y <= l_casePositionNext.y; l_playerPosition.y += ((WINDOW_HEIGHT / 10)) / 10) {
					SDL_RenderCopy(p_interface->renderer, p_interface->caseSprite[p_map->path[(int)(p_interface->playerGraphx.position.y)][(int)(p_interface->playerGraphx.position.x)].type], NULL, &l_casePosition);
					SDL_RenderCopy(p_interface->renderer, p_interface->caseSprite[p_map->path[(int)(p_interface->playerGraphx.position.y + 1)][(int)(p_interface->playerGraphx.position.x)].type], NULL, &l_casePositionNext);
					SDL_RenderCopy(p_interface->renderer, p_interface->playerGraphx.playerSprite[p_direction], NULL, &l_playerPosition);
					SDL_RenderPresent(p_interface->renderer);
					SDL_Delay(SDL_ANIMATION_FRAMETIME);
				}
			}
		}
		break;

	case(DLEFT):
		if (l_currentCase->node.neighbourLEFT) {
			for (p_interface->playerGraphx.position.x; p_interface->playerGraphx.position.x > l_currentCase->node.neighbourLEFT->position.x; p_interface->playerGraphx.position.x--) {
				l_playerPosition.x = p_interface->playerGraphx.position.x * (WINDOW_HEIGHT / 10);
				l_casePosition.x = p_interface->playerGraphx.position.x * (WINDOW_WIDTH / 10);
				l_casePosition.y = p_interface->playerGraphx.position.y * (WINDOW_HEIGHT / 10);
				l_casePositionNext.x = l_casePosition.x - (WINDOW_HEIGHT / 10);
				l_casePositionNext.y = l_casePosition.y;
				for (l_playerPosition.x; l_playerPosition.x >= l_casePositionNext.x; l_playerPosition.x -= ((WINDOW_HEIGHT / 10)) / 10) {
					SDL_RenderCopy(p_interface->renderer, p_interface->caseSprite[p_map->path[(int)(p_interface->playerGraphx.position.y)][(int)(p_interface->playerGraphx.position.x)].type], NULL, &l_casePosition);
					SDL_RenderCopy(p_interface->renderer, p_interface->caseSprite[p_map->path[(int)(p_interface->playerGraphx.position.y)][(int)(p_interface->playerGraphx.position.x - 1)].type], NULL, &l_casePositionNext);
					SDL_RenderCopy(p_interface->renderer, p_interface->playerGraphx.playerSprite[p_direction], NULL, &l_playerPosition);
					SDL_RenderPresent(p_interface->renderer);
					SDL_Delay(SDL_ANIMATION_FRAMETIME);
				}
			}
		}
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
			SDL_RenderCopy(p_interface->renderer, p_interface->caseSprite[p_map->path[l_i][l_j].type], NULL, &posCase);
			posCase.x += WINDOW_WIDTH / 10;
		}
		posCase.x = 0;
		posCase.y += WINDOW_HEIGHT / 10;
	}

	SDL_RenderPresent(p_interface->renderer);

	return 0;
}	

int solveGame(sInterface *p_interface, sMap *p_map) {
	sList *l_solutionPath = NULL;
	
	SDL_Rect l_playerPosition = { (float)(p_interface->playerGraphx.position.x * (WINDOW_WIDTH / 10)), (float)(p_interface->playerGraphx.position.y * (WINDOW_HEIGHT / 10)), WINDOW_WIDTH / 10, WINDOW_HEIGHT / 10 };

	l_solutionPath = dijkstra(p_map, p_interface->playerGraphx.position);
	while (l_solutionPath && l_solutionPath->next) {

		SDL_RenderDrawLine(p_interface->renderer, ((WINDOW_WIDTH / 10) * l_solutionPath->position.x) + (WINDOW_WIDTH / 20), ((WINDOW_HEIGHT / 10) * l_solutionPath->position.y) + (WINDOW_HEIGHT/20), ((WINDOW_WIDTH / 10) * (l_solutionPath->next)->position.x) + (WINDOW_WIDTH/20), ((WINDOW_HEIGHT / 10) * (l_solutionPath->next)->position.y) + (WINDOW_HEIGHT/20));
		SDL_RenderPresent(p_interface->renderer);

		l_solutionPath = l_solutionPath->next;
	}


	SDL_RenderCopy(p_interface->renderer, p_interface->playerGraphx.playerSprite[p_interface->playerGraphx.direction], NULL, &l_playerPosition);
	SDL_RenderPresent(p_interface->renderer);
	return 0;
}
