#include "graphx.h"

int loadInterface(sInterface *p_interface, sMap *p_map) {
	int l_i;
	char l_casePath[50] = "./assets/sprite/case_01.bmp", l_persoPath[50] = "./assets/sprite/perso_0.bmp";

	SDL_Surface *l_sprite;

	printf("%p in initialisation fonction\n", p_interface);

	if (SDL_Init(SDL_INIT_EVERYTHING)) {
		fprintf(stdout, "[SDL] Initialization Error (%s)\n", SDL_GetError());
		return EXIT_FAILURE;
	}
	IMG_Init(IMG_INIT_PNG);

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
		p_interface->player.playerSprite[l_i] = SDL_CreateTextureFromSurface(p_interface->renderer, l_sprite);
		SDL_FreeSurface(l_sprite);
	}

	p_interface->player.mapPosition.x = p_map->starting.x;
	p_interface->player.mapPosition.y = p_map->starting.y;
	p_interface->player.realPosition = getRealPosition(p_interface->player.mapPosition);
	p_interface->player.realDestination = getRealPosition(p_interface->player.mapPosition);
	p_interface->player.isSliding = FALSE;
	p_interface->player.direction = DUP;


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
		SDL_DestroyTexture(p_interface->player.playerSprite[l_i]);
	}

	SDL_DestroyRenderer(p_interface->renderer);
	SDL_DestroyWindow(p_interface->window);

	return 0;
}

int gameLoop(sInterface *p_interface, sMap *p_map) {
	
	bool l_loop = TRUE, l_solve = FALSE;
	sSonor l_sonor;
	
	loadInterface(p_interface, p_map);
	displayMap(p_interface, p_map);
	playSonor(&l_sonor);

	while (l_loop){

		if(SDL_PollEvent(&(p_interface->event))) {
			switch (p_interface->event.type) {
				case(SDL_KEYDOWN):
					switch (p_interface->event.key.keysym.sym) {
						case(SDLK_z):
							Mix_PlayChannel(-1, l_sonor.slide, 0);
							updateGoal(p_interface, p_map, DUP);
							break;
						case(SDLK_d):
							Mix_PlayChannel(-1, l_sonor.slide, 0);
							updateGoal(p_interface, p_map, DRIGHT);
							break;
						case(SDLK_s):
							Mix_PlayChannel(-1, l_sonor.slide, 0);
							updateGoal(p_interface, p_map, DDOWN);
							break;
						case(SDLK_q):
							Mix_PlayChannel(-1, l_sonor.slide, 0);
							updateGoal(p_interface, p_map, DLEFT);			
							break;
						case(SDLK_x):
							l_solve = !l_solve;
							break;
						case(SDLK_ESCAPE):
							l_loop = FALSE;
							break;
					}
					while (SDL_PollEvent(&(p_interface->event)));
					l_loop = WinOrNot(p_interface, p_map);
					break;
			}
		}
		updateVision(p_interface, p_map);
		SDL_Delay(SDL_ANIMATION_FRAMETIME);
	}

	closeInterface(p_interface);
	SDL_Quit();

	return 0;
}

int updateGoal(sInterface *p_interface, sMap *p_map, eDirection p_direction) {
	sNode *l_neighbour = NULL;

	if (p_interface->player.isSliding)
		return 0;

	p_interface->player.direction = p_direction;

	switch (p_direction) {
		case(DUP):
			l_neighbour = p_map->path[p_interface->player.mapPosition.y][p_interface->player.mapPosition.x].node.neighbourUP;
			break;
		case(DRIGHT):
			l_neighbour = p_map->path[p_interface->player.mapPosition.y][p_interface->player.mapPosition.x].node.neighbourRIGHT;
			break;
		case(DDOWN):
			l_neighbour = p_map->path[p_interface->player.mapPosition.y][p_interface->player.mapPosition.x].node.neighbourDOWN;
			break;
		case(DLEFT):
			l_neighbour = p_map->path[p_interface->player.mapPosition.y][p_interface->player.mapPosition.x].node.neighbourLEFT;
			break;
	}

	if (!l_neighbour) {
		p_interface->player.realDestination = p_interface->player.realPosition;
	}else{
		p_interface->player.realDestination = getRealPosition(l_neighbour->position);
		p_interface->player.mapPosition = l_neighbour->position;
	}

	p_interface->player.isSliding = TRUE;

	return 0;
}

int updateVision(sInterface *p_interface, sMap *p_map) {
	sPosition l_casePosition;
	SDL_Rect l_caseRealPosition;

	if (!(p_interface->player.isSliding))
		return 0;

	if (comparePositionRect(p_interface->player.realPosition, p_interface->player.realDestination)) {
		SDL_RenderCopy(p_interface->renderer, p_interface->caseSprite[p_map->path[p_interface->player.mapPosition.y][p_interface->player.mapPosition.x].type], NULL, &(p_interface->player.realDestination));
		SDL_RenderCopy(p_interface->renderer, p_interface->player.playerSprite[p_interface->player.direction], NULL, &(p_interface->player.realPosition));
		p_interface->player.isSliding = FALSE;
	}else {
		
		//Blit case basse et case haute
		l_casePosition = getMapPosition(p_interface->player.realPosition);

		l_caseRealPosition = getRealPosition(l_casePosition);
		SDL_RenderCopy(p_interface->renderer, p_interface->caseSprite[p_map->path[l_casePosition.y][l_casePosition.x].type], NULL, &(l_caseRealPosition));
		
		if(p_interface->player.direction == DUP)
			l_casePosition.y -= 1;
		if (p_interface->player.direction == DRIGHT)
			l_casePosition.x += 1;
		if (p_interface->player.direction == DDOWN)
			l_casePosition.y += 1;
		if (p_interface->player.direction == DLEFT)
			l_casePosition.x -= 1;
		
		l_caseRealPosition = getRealPosition(l_casePosition);
		SDL_RenderCopy(p_interface->renderer, p_interface->caseSprite[p_map->path[l_casePosition.y][l_casePosition.x].type], NULL, &(l_caseRealPosition));
				
		//Blit player	
		SDL_RenderCopy(p_interface->renderer, p_interface->player.playerSprite[p_interface->player.direction], NULL, &(p_interface->player.realPosition));
		
		if(p_interface->player.direction == DUP)
			p_interface->player.realPosition.y -= ((WINDOW_HEIGHT / CASE_LINE_AMOUNT) / SDL_ANIMATION_SLIDE_FRAMEAMOUNT);
		if (p_interface->player.direction == DRIGHT)
			p_interface->player.realPosition.x += ((WINDOW_WIDTH / CASE_COLUMN_AMOUNT) / SDL_ANIMATION_SLIDE_FRAMEAMOUNT);
		if (p_interface->player.direction == DDOWN)
			p_interface->player.realPosition.y += ((WINDOW_HEIGHT / CASE_LINE_AMOUNT) / SDL_ANIMATION_SLIDE_FRAMEAMOUNT);
		if (p_interface->player.direction == DLEFT)
			p_interface->player.realPosition.x -= ((WINDOW_WIDTH / CASE_COLUMN_AMOUNT) / SDL_ANIMATION_SLIDE_FRAMEAMOUNT);	
	}

	SDL_RenderPresent(p_interface->renderer);

	return 0;
}

int moovePlayer(sInterface *p_interface, sMap *p_map, eDirection p_direction) {

	sCase *l_currentCase;

	SDL_Rect l_playerPosition = { (float)(p_interface->player.mapPosition.x * (WINDOW_WIDTH / 10)), (float)(p_interface->player.mapPosition.y * (WINDOW_HEIGHT / 10)), WINDOW_WIDTH / 10, WINDOW_HEIGHT / 10 };
	SDL_Rect l_casePosition = { 0, 0, WINDOW_WIDTH / 10, WINDOW_HEIGHT / 10 };
	SDL_Rect l_casePositionNext = { 0, 0, WINDOW_WIDTH / 10, WINDOW_HEIGHT / 10 };

	SDL_RenderCopy(p_interface->renderer, p_interface->caseSprite[p_map->path[(int)(p_interface->player.mapPosition.y)][(int)(p_interface->player.mapPosition.x)].type], NULL, &l_playerPosition);
	SDL_RenderCopy(p_interface->renderer, p_interface->player.playerSprite[p_direction], NULL, &l_playerPosition);
	SDL_RenderPresent(p_interface->renderer);


	l_currentCase = &(p_map->path[(int)(p_interface->player.mapPosition.y)][(int)(p_interface->player.mapPosition.x)]);
	p_interface->player.direction = p_direction;

	switch (p_direction) {
	case(DUP):
		if (l_currentCase->node.neighbourUP) {
			for (p_interface->player.mapPosition.y; p_interface->player.mapPosition.y > l_currentCase->node.neighbourUP->position.y; p_interface->player.mapPosition.y--) {
				l_playerPosition.y = p_interface->player.mapPosition.y * (WINDOW_HEIGHT / 10);
				l_casePosition.x = p_interface->player.mapPosition.x * (WINDOW_WIDTH / 10);
				l_casePosition.y = p_interface->player.mapPosition.y * (WINDOW_HEIGHT / 10);
				l_casePositionNext.x = l_casePosition.x;
				l_casePositionNext.y = l_casePosition.y - (WINDOW_HEIGHT / 10);

				for (l_playerPosition.y; l_playerPosition.y >= l_casePositionNext.y; l_playerPosition.y -= ((WINDOW_HEIGHT / 10)) / SDL_ANIMATION_SLIDE_FRAMEAMOUNT) {
					SDL_RenderCopy(p_interface->renderer, p_interface->caseSprite[p_map->path[(int)(p_interface->player.mapPosition.y)][(int)(p_interface->player.mapPosition.x)].type], NULL, &l_casePosition);
					SDL_RenderCopy(p_interface->renderer, p_interface->caseSprite[p_map->path[(int)(p_interface->player.mapPosition.y - 1)][(int)(p_interface->player.mapPosition.x)].type], NULL, &l_casePositionNext);
					SDL_RenderCopy(p_interface->renderer, p_interface->player.playerSprite[p_direction], NULL, &l_playerPosition);
					SDL_RenderPresent(p_interface->renderer);
					SDL_Delay(SDL_ANIMATION_FRAMETIME);
				}
			}
		}
		break;

	case(DRIGHT):
		if (l_currentCase->node.neighbourRIGHT) {
			for (p_interface->player.mapPosition.x; p_interface->player.mapPosition.x < l_currentCase->node.neighbourRIGHT->position.x; p_interface->player.mapPosition.x++) {
				l_playerPosition.x = p_interface->player.mapPosition.x * (WINDOW_HEIGHT / 10);
				l_casePosition.x = p_interface->player.mapPosition.x * (WINDOW_WIDTH / 10);
				l_casePosition.y = p_interface->player.mapPosition.y * (WINDOW_HEIGHT / 10);
				l_casePositionNext.x = l_casePosition.x + (WINDOW_HEIGHT / 10);
				l_casePositionNext.y = l_casePosition.y;
				for (l_playerPosition.x; l_playerPosition.x <= l_casePositionNext.x; l_playerPosition.x += ((WINDOW_HEIGHT / 10)) / SDL_ANIMATION_SLIDE_FRAMEAMOUNT) {
					SDL_RenderCopy(p_interface->renderer, p_interface->caseSprite[p_map->path[(int)(p_interface->player.mapPosition.y)][(int)(p_interface->player.mapPosition.x)].type], NULL, &l_casePosition);
					SDL_RenderCopy(p_interface->renderer, p_interface->caseSprite[p_map->path[(int)(p_interface->player.mapPosition.y)][(int)(p_interface->player.mapPosition.x + 1)].type], NULL, &l_casePositionNext);
					SDL_RenderCopy(p_interface->renderer, p_interface->player.playerSprite[p_direction], NULL, &l_playerPosition);
					SDL_RenderPresent(p_interface->renderer);
					SDL_Delay(SDL_ANIMATION_FRAMETIME);
				}
			}
		}
		break;

	case(DDOWN):
		if (l_currentCase->node.neighbourDOWN) {

			for (p_interface->player.mapPosition.y; p_interface->player.mapPosition.y < l_currentCase->node.neighbourDOWN->position.y; p_interface->player.mapPosition.y++) {
				l_playerPosition.y = p_interface->player.mapPosition.y * (WINDOW_HEIGHT / 10);
				l_casePosition.x = p_interface->player.mapPosition.x * (WINDOW_WIDTH / 10);
				l_casePosition.y = p_interface->player.mapPosition.y * (WINDOW_HEIGHT / 10);
				l_casePositionNext.x = l_casePosition.x;
				l_casePositionNext.y = l_casePosition.y + (WINDOW_HEIGHT / 10);
				for (l_playerPosition.y; l_playerPosition.y <= l_casePositionNext.y; l_playerPosition.y += ((WINDOW_HEIGHT / 10)) / SDL_ANIMATION_SLIDE_FRAMEAMOUNT) {
					SDL_RenderCopy(p_interface->renderer, p_interface->caseSprite[p_map->path[(int)(p_interface->player.mapPosition.y)][(int)(p_interface->player.mapPosition.x)].type], NULL, &l_casePosition);
					SDL_RenderCopy(p_interface->renderer, p_interface->caseSprite[p_map->path[(int)(p_interface->player.mapPosition.y + 1)][(int)(p_interface->player.mapPosition.x)].type], NULL, &l_casePositionNext);
					SDL_RenderCopy(p_interface->renderer, p_interface->player.playerSprite[p_direction], NULL, &l_playerPosition);
					SDL_RenderPresent(p_interface->renderer);
					SDL_Delay(SDL_ANIMATION_FRAMETIME);
				}
			}
		}
		break;

	case(DLEFT):
		if (l_currentCase->node.neighbourLEFT) {
			for (p_interface->player.mapPosition.x; p_interface->player.mapPosition.x > l_currentCase->node.neighbourLEFT->position.x; p_interface->player.mapPosition.x--) {
				l_playerPosition.x = p_interface->player.mapPosition.x * (WINDOW_HEIGHT / 10);
				l_casePosition.x = p_interface->player.mapPosition.x * (WINDOW_WIDTH / 10);
				l_casePosition.y = p_interface->player.mapPosition.y * (WINDOW_HEIGHT / 10);
				l_casePositionNext.x = l_casePosition.x - (WINDOW_HEIGHT / 10);
				l_casePositionNext.y = l_casePosition.y;
				for (l_playerPosition.x; l_playerPosition.x >= l_casePositionNext.x; l_playerPosition.x -= ((WINDOW_HEIGHT / 10)) / SDL_ANIMATION_SLIDE_FRAMEAMOUNT) {
					SDL_RenderCopy(p_interface->renderer, p_interface->caseSprite[p_map->path[(int)(p_interface->player.mapPosition.y)][(int)(p_interface->player.mapPosition.x)].type], NULL, &l_casePosition);
					SDL_RenderCopy(p_interface->renderer, p_interface->caseSprite[p_map->path[(int)(p_interface->player.mapPosition.y)][(int)(p_interface->player.mapPosition.x - 1)].type], NULL, &l_casePositionNext);
					SDL_RenderCopy(p_interface->renderer, p_interface->player.playerSprite[p_direction], NULL, &l_playerPosition);
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
	
	SDL_Rect l_playerPosition = { p_interface->player.mapPosition.x * (WINDOW_WIDTH / 10), p_interface->player.mapPosition.y * (WINDOW_HEIGHT / 10), WINDOW_WIDTH / 10, WINDOW_HEIGHT / 10 };

	l_solutionPath = dijkstra(p_map, p_interface->player.mapPosition);
	while (l_solutionPath && l_solutionPath->next) {

		SDL_RenderDrawLine(p_interface->renderer, ((WINDOW_WIDTH / 10) * l_solutionPath->position.x) + (WINDOW_WIDTH / 20), ((WINDOW_HEIGHT / 10) * l_solutionPath->position.y) + (WINDOW_HEIGHT/20), ((WINDOW_WIDTH / 10) * (l_solutionPath->next)->position.x) + (WINDOW_WIDTH/20), ((WINDOW_HEIGHT / 10) * (l_solutionPath->next)->position.y) + (WINDOW_HEIGHT/20));
		SDL_RenderPresent(p_interface->renderer);

		l_solutionPath = l_solutionPath->next;
	}


	SDL_RenderCopy(p_interface->renderer, p_interface->player.playerSprite[p_interface->player.direction], NULL, &l_playerPosition);
	SDL_RenderPresent(p_interface->renderer);
	return 0;
}

bool WinOrNot(sInterface *p_interface, sMap *p_map) {
	SDL_Surface *l_sprite = NULL;
	SDL_Texture *l_texture = NULL;

	SDL_Rect l_position = { 0, 0, 500, 500 };

	if (p_interface->player.mapPosition.x == p_map->ending.x && p_interface->player.mapPosition.y == p_map->ending.y) {
		l_sprite = IMG_Load("./assets/sprite/congratulation.png");
		SDL_SetColorKey(l_sprite, SDL_TRUE, SDL_MapRGB(l_sprite->format, 12, 255, 0));
		l_texture = SDL_CreateTextureFromSurface(p_interface->renderer, l_sprite);
		SDL_RenderCopy(p_interface->renderer, l_texture, NULL, &l_position);
		SDL_RenderPresent(p_interface->renderer);
		SDL_Delay(1000);
		SDL_DestroyTexture(l_texture);
		SDL_FreeSurface(l_sprite);
		return FALSE;
	}

	return TRUE;
}

SDL_Rect getRealPosition(sPosition p_position) {
	SDL_Rect l_position;

	l_position.x = (p_position.x * (WINDOW_WIDTH / CASE_COLUMN_AMOUNT));
	l_position.y = (p_position.y * (WINDOW_HEIGHT / CASE_LINE_AMOUNT));
	l_position.h = (WINDOW_HEIGHT / CASE_LINE_AMOUNT);
	l_position.w = (WINDOW_WIDTH / CASE_COLUMN_AMOUNT);

	return l_position;
}

sPosition getMapPosition(SDL_Rect p_position) {
	sPosition l_position;

	l_position.x = p_position.x / (WINDOW_WIDTH / CASE_COLUMN_AMOUNT);
	l_position.y = p_position.y / (WINDOW_HEIGHT / CASE_LINE_AMOUNT);

	return l_position;
}

bool comparePositionRect(SDL_Rect p_firstPosition, SDL_Rect p_secondPosition) {
	if (p_firstPosition.x != p_secondPosition.x || p_firstPosition.y != p_secondPosition.y) {
		return FALSE;
	}

	return TRUE;
}