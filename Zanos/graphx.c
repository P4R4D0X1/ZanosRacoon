/**
* \file graphx.c
* \brief Programme de rendu de l'enigme et des graphismes
* \date 27 mai 2016
*
* Programme qui realise le rendu, l'affichage et l'interface avec l'utilisateur.
*
*/
#include "particle.h"
#include "menu.h"
#include "graphx.h"


/**
* \fn int loadInterface(sInterface *p_interface)
* \brief Fonction d'initialisation de structure de type sInterface
*
* \param *p_interface pointeur vers une structure de type sInterface
* \return int représentant le déroulement de la fonction
*/
int loadInterface(sInterface *p_interface) {
	int l_i;
	char l_casePath[50] = "./assets/sprite/case_01.png", l_persoPath[50] = "./assets/sprite/perso_0.png";

	SDL_Surface *l_sprite;
	SDL_Rect l_posAnim, l_offset;

	if (SDL_Init(SDL_INIT_EVERYTHING)) {
		fprintf(stdout, "[SDL] Initialization Error (%s)\n", SDL_GetError());
		return EXIT_FAILURE;
	}
	IMG_Init(IMG_INIT_PNG);
	TTF_Init();

	p_interface->window = SDL_CreateWindow("-RACCOON ZANOS-", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN );
	if (!(p_interface->window)) {
		fprintf(stderr, "[SDL] Window creation error (%s)\n", SDL_GetError());
		return EXIT_FAILURE;
	}
	SDL_ShowCursor(SDL_DISABLE);

	p_interface->renderer = SDL_CreateRenderer(p_interface->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);

	for (l_i = 0; l_i < CASE_TYPE_AMOUNT; ++l_i) {
		l_casePath[21] = (int)(l_i / 10) + 48; 
		l_casePath[22] = (l_i - (int)(l_i / 10)*10) + 48;
		l_sprite = IMG_Load(l_casePath);
		p_interface->caseSprite[l_i] = SDL_CreateTextureFromSurface(p_interface->renderer, l_sprite);
		SDL_FreeSurface(l_sprite);
	}

	for (l_i = 0; l_i < 4; ++l_i) {
		l_persoPath[22] = l_i + 48;
		l_sprite = IMG_Load(l_persoPath);
		p_interface->player.playerSprite[l_i] = SDL_CreateTextureFromSurface(p_interface->renderer, l_sprite);
		SDL_FreeSurface(l_sprite);
	}

	p_interface->effect.particle = NULL;
	l_sprite = IMG_Load("./assets/sprite/particle_0.png");
	p_interface->effect.particleSprite[0] = SDL_CreateTextureFromSurface(p_interface->renderer, l_sprite);
	l_sprite = IMG_Load("./assets/sprite/particle_1.png");
	p_interface->effect.particleSprite[1] = SDL_CreateTextureFromSurface(p_interface->renderer, l_sprite);
	l_sprite = IMG_Load("./assets/sprite/particle_2.png");
	p_interface->effect.particleSprite[2] = SDL_CreateTextureFromSurface(p_interface->renderer, l_sprite);
	SDL_FreeSurface(l_sprite);

	l_sprite = IMG_Load("./assets/sprite/cursor.png");
	p_interface->cursor = SDL_CreateTextureFromSurface(p_interface->renderer, l_sprite);
	SDL_FreeSurface(l_sprite);

	l_posAnim.x = 0;
	l_posAnim.y = 0;
	l_posAnim.h = WINDOW_HEIGHT;
	l_posAnim.w = WINDOW_WIDTH;
	loadAnimation(0, &(p_interface->effect.l_mountain), 159, l_posAnim, "./assets/sprite/anim/mountain_", p_interface, 3);
	loadAnimation(1, &(p_interface->effect.l_tuto), 8, l_posAnim, "./assets/sprite/anim/tuto_", p_interface, 1);
	loadAnimation(1, &(p_interface->effect.l_congrate), 4, l_posAnim, "./assets/sprite/anim/congratulation_", p_interface, 1);

	l_posAnim.h = 250;
	l_posAnim.w = 250;
	l_posAnim.x = WINDOW_HEIGHT - l_posAnim.h;
	l_posAnim.y = WINDOW_WIDTH - l_posAnim.w;
	l_offset.x = 1000;
	l_offset.y = 1000;
	l_offset.w = -1;
	l_offset.h = -1;
	loadAnimation(1, &(p_interface->effect.l_raccoon), 3, l_posAnim, "./assets/sprite/anim/raccoon-skate_", p_interface, 10);

	l_posAnim.h = 400;
	l_posAnim.w = 400;
	l_offset.x = 10;
	l_offset.y = 10;
	l_offset.w = 0;
	l_offset.h = -1;
	centrerPosition(&l_posAnim, l_offset);
	loadAnimation(1, &(p_interface->effect.l_logo), 2, l_posAnim, "./assets/sprite/anim/raccoonzanos_", p_interface, 100);

	l_posAnim.w = 200;
	l_posAnim.h = 100;
	l_offset.x = 10;
	l_offset.y = 10;
	l_offset.w = 0;
	l_offset.h = 0;
	centrerPosition(&l_posAnim, l_offset);
	loadAnimation(1, &(p_interface->effect.l_play), 4, l_posAnim, "./assets/sprite/anim/play_", p_interface, 5);

	p_interface->backgroundSprite = SDL_CreateTexture(p_interface->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, WINDOW_WIDTH, WINDOW_HEIGHT);


	p_interface->player.isSliding = FALSE;
	p_interface->player.direction = DUP;
	p_interface->compteur = 0;

	p_interface->solution = NULL;

	loadSonor(&(p_interface->sonor));

	SDL_SetRenderDrawColor(p_interface->renderer, 255, 0, 0, 255);
	SDL_RenderClear(p_interface->renderer);

	return 0;
}

/**
* \fn int closeInterface(sInterface *p_interface)
* \brief Fonction de desallocation de structure de type sInterface
*
* \param *p_interface pointeur vers une structure de type sInterface
* \return int représentant le déroulement de la fonction
*/
int closeInterface(sInterface *p_interface) {
	int l_i;

	for (l_i = 0; l_i < CASE_TYPE_AMOUNT; ++l_i) {
		SDL_DestroyTexture(p_interface->caseSprite[l_i]);
	}

	for (l_i = 0; l_i < 4; ++l_i) {
		SDL_DestroyTexture(p_interface->player.playerSprite[l_i]);
	}

	freeAnimation(p_interface->effect.l_mountain);
	freeAnimation(p_interface->effect.l_tuto);
	freeAnimation(p_interface->effect.l_raccoon);
	freeAnimation(p_interface->effect.l_logo);
	freeAnimation(p_interface->effect.l_play);
	freeAnimation(p_interface->effect.l_congrate);

	SDL_DestroyRenderer(p_interface->renderer);
	SDL_DestroyWindow(p_interface->window);

	return 0;
}

/**
* \fn int gameLoop(sInterface *p_interface, sMap *p_map)
* \brief Fonction de rendu de l'enigme et d'interfacage avec l'utilisateur
*
* \param *p_interface pointeur vers une structure de type sInterface
* \param *p_map pointeur vers une structure de type sMap
* \return int représentant le déroulement de la fonction
*/
int gameLoop(sInterface *p_interface, sMap *p_map) {
	
	bool l_loop = TRUE, l_solve = FALSE;
	char txtCmpt[32] = "";

	SDL_Rect l_posText = {(WINDOW_WIDTH / CASE_COLUMN_AMOUNT)/2, (WINDOW_HEIGHT / CASE_LINE_AMOUNT)/2, 50, 50};
	SDL_Color l_color = {255, 0, 0};

	p_interface->player.mapPosition.x = p_map->starting.x;
	p_interface->player.mapPosition.y = p_map->starting.y;
	p_interface->player.realPosition = getRealPosition(p_interface->player.mapPosition);
	p_interface->player.realDestination = getRealPosition(p_interface->player.mapPosition);

	displayMap(p_interface, p_map);

	while (l_loop){
		if(SDL_PollEvent(&(p_interface->event))) {
			switch (p_interface->event.type) {
				case(SDL_KEYDOWN):
					switch (p_interface->event.key.keysym.sym) {
						case(SDLK_z):
							updateGoal(p_interface, p_map, DUP);
							break;

						case(SDLK_d):
							updateGoal(p_interface, p_map, DRIGHT);
							break;

						case(SDLK_s):
							updateGoal(p_interface, p_map, DDOWN);
							break;

						case(SDLK_q):
							updateGoal(p_interface, p_map, DLEFT);	
							break;

						case(SDLK_x):
							l_solve = !l_solve;
							break;

						case(SDLK_ESCAPE):
							l_loop = FALSE;
							break;
					}
					break;

				case(SDL_MOUSEBUTTONDOWN):
					break;
			}
			while (SDL_PollEvent(&(p_interface->event)));
		}

		SDL_RenderClear(p_interface->renderer);
		SDL_RenderCopy(p_interface->renderer, p_interface->backgroundSprite, NULL, NULL);

		if(l_solve)
			showSolution(p_interface, p_interface->solution);
		renderParticle(&(p_interface->effect.particle), p_interface, p_map, TRUE);

		updateVision(p_interface, p_map);

		sprintf_s(txtCmpt, 30, "%d", p_interface->compteur);
		displayText(p_interface->renderer, txtCmpt, l_color, l_posText);


		SDL_RenderPresent(p_interface->renderer);
		if (WinOrNot(p_interface, p_map)) {
			l_loop = FALSE;
		}
		SDL_Delay(SDL_ANIMATION_FRAMETIME);
	}


	return 0;
}

/**
* \fn int updateGoal(sInterface *p_interface, sMap *p_map, eDirection p_direction)
* \brief Fonction de gestion des deplacements du personnage
*
* \param *p_interface pointeur vers une structure de type sInterface
* \param *p_map pointeur vers une structure de type sMap
* \param p_direction enum de type eDirection definissant le sens du deplacement
* \return int représentant le déroulement de la fonction
*/
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
		Mix_PlayChannel(-1, p_interface->sonor.slide, 0);
		p_interface->compteur += 1;
		p_interface->player.realDestination = getRealPosition(l_neighbour->position);
		p_interface->player.mapPosition = l_neighbour->position;
	}

	p_interface->player.isSliding = TRUE;

	return 0;
}

/**
* \fn int updateVision(sInterface *p_interface, sMap *p_map)
* \brief Fonction de mise à jour de la position du joueur
*
* \param *p_interface pointeur vers une structure de type sInterface
* \param *p_map pointeur vers une structure de type sMap
* \return int représentant le déroulement de la fonction
*/
int updateVision(sInterface *p_interface, sMap *p_map) {

	if (!(p_interface->player.isSliding)) {
		SDL_RenderCopy(p_interface->renderer, p_interface->player.playerSprite[p_interface->player.direction], NULL, &(p_interface->player.realPosition));
		return 0;
	}


	if (comparePositionRect(p_interface->player.realPosition, p_interface->player.realDestination)) {
		SDL_RenderCopy(p_interface->renderer, p_interface->player.playerSprite[p_interface->player.direction], NULL, &(p_interface->player.realPosition));
		p_interface->solution = dijkstra(p_map, getMapPosition(p_interface->player.realPosition));
		p_interface->player.isSliding = FALSE;
	}else {
		if(!(p_interface->effect.particle))
			initParticleSystem(&(p_interface->effect.particle), PATRICLE_SYSTEM_LIFETIME, PARTICLE_AMOUNT, p_interface->player.realPosition, p_interface->player.direction);

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

	return 0;
}

/**
* \fn int displayMap(sInterface *p_interface, sMap *p_map)
* \brief Fonction qui initialise les graphismes de la map
*
* \param *p_interface pointeur vers une structure de type sInterface
* \param *p_map pointeur vers une structure de type sMap
* \return int représentant le déroulement de la fonction
*/
int displayMap(sInterface *p_interface, sMap *p_map) {
	int l_i, l_j;
	
	SDL_Rect l_posCase, l_arbre;
	SDL_Surface *l_sprite;
	SDL_Texture *l_texture;

	l_posCase.x = 0;
	l_posCase.y = 0;
	l_posCase.h = WINDOW_HEIGHT / CASE_LINE_AMOUNT;
	l_posCase.w = WINDOW_WIDTH / CASE_COLUMN_AMOUNT;

	SDL_SetRenderTarget(p_interface->renderer, p_interface->backgroundSprite);
	SDL_SetRenderDrawColor(p_interface->renderer, 0, 0, 0, 0);
	SDL_RenderClear(p_interface->renderer);

	for (l_i = 0; l_i < p_map->mapDimension.height; ++l_i) {
			for (l_j = 0; l_j < p_map->mapDimension.width; ++l_j) {
						
				SDL_RenderCopy(p_interface->renderer, p_interface->caseSprite[0], NULL, &l_posCase);
				SDL_RenderCopy(p_interface->renderer, p_interface->caseSprite[p_map->path[l_i][l_j].type], NULL, &l_posCase );
				if ((l_i == 0 || l_j == 0 || l_i == 9 || l_j == 9) && (p_map->path[l_i][l_j].type == 2)) {
					l_arbre = l_posCase;
					//l_arbre.x += (rand() % 10) - 5;
					//l_arbre.y += (rand() % 10) - 5;
					l_sprite = IMG_Load("./assets/sprite/tree_0.png");
					l_texture = SDL_CreateTextureFromSurface(p_interface->renderer, l_sprite);
					SDL_FreeSurface(l_sprite);
					SDL_RenderCopy(p_interface->renderer, l_texture, NULL, &l_arbre);
				}

			if (p_map->starting.y == l_i && p_map->starting.x == l_j) {
				l_sprite = IMG_Load("./assets/sprite/start.png");
				l_texture = SDL_CreateTextureFromSurface(p_interface->renderer, l_sprite);
				SDL_FreeSurface(l_sprite);
				SDL_RenderCopy(p_interface->renderer, l_texture, NULL, &l_posCase);
			}
			if (p_map->ending.y == l_i && p_map->ending.x == l_j) {
				l_sprite = IMG_Load("./assets/sprite/goal.png");
				l_texture = SDL_CreateTextureFromSurface(p_interface->renderer, l_sprite);
				SDL_FreeSurface(l_sprite);
				SDL_RenderCopy(p_interface->renderer, l_texture, NULL, &l_posCase);
			}
			l_posCase.x += WINDOW_WIDTH / CASE_COLUMN_AMOUNT;
		}
		l_posCase.x = 0;
		l_posCase.y += WINDOW_HEIGHT / CASE_LINE_AMOUNT;
	}

	SDL_SetRenderTarget(p_interface->renderer, NULL);

	return 0;
}	

/**
* \fn int showSolution(sInterface *p_interface, sList *p_solutionPath)
* \brief Fonction qui permet l'affichage de la solution du labyrinthe
*
* \param *p_interface pointeur vers une structure de type sInterface
* \param *p_solutionPath pointeur vers une structure de type sList, structure de listes chainées
* \return int représentant le déroulement de la fonction
*/
int showSolution(sInterface *p_interface, sList *p_solutionPath) {

	SDL_Rect l_posA, l_posB, l_middleOffset;

	l_middleOffset.x = (WINDOW_WIDTH / CASE_COLUMN_AMOUNT) / 2;
	l_middleOffset.y = (WINDOW_HEIGHT / CASE_LINE_AMOUNT) / 2;

	if (p_solutionPath && p_solutionPath->next) {
		p_solutionPath = p_solutionPath->next;

		l_posA = getRealPosition(p_solutionPath->position);
		SDL_RenderDrawLine(p_interface->renderer, p_interface->player.realPosition.x + l_middleOffset.x, p_interface->player.realPosition.y + l_middleOffset.y, l_posA.x + l_middleOffset.x, l_posA.y + l_middleOffset.y);

		while (p_solutionPath->next) {
			l_posB = getRealPosition((p_solutionPath->next)->position);
			SDL_RenderDrawLine(p_interface->renderer, l_posA.x + l_middleOffset.x, l_posA.y + l_middleOffset.y, l_posB.x + l_middleOffset.x, l_posB.y + l_middleOffset.y);
			l_posA.x = l_posB.x;
			l_posA.y = l_posB.y;
			p_solutionPath = p_solutionPath->next;
		}
	}
	return 0;
}

/**
* \fn bool WinOrNot(sInterface *p_interface, sMap *p_map)
* \brief Fonction qui deduit si l'utilisateur a gagné ou non
*
* \param *p_interface pointeur vers une structure de type sInterface
* \param *p_map pointeur vers une structure de type sMap
* \return bool enum de type eBool vaut 1 si l'utilisateur a gagné 0 sinon
*/
bool WinOrNot(sInterface *p_interface, sMap *p_map) {

	if (comparePositionRect(getRealPosition(p_map->ending), p_interface->player.realPosition)) {
		Mix_PlayChannel(-1, p_interface->sonor.applause, 0);
		while (p_interface->effect.l_congrate->actualFrame != p_interface->effect.l_congrate->frameAmount - 1) {
			SDL_RenderCopy(p_interface->renderer, p_interface->backgroundSprite, NULL, NULL);
			updateAnimation(p_interface->effect.l_congrate, p_interface);
			SDL_RenderPresent(p_interface->renderer);
			SDL_Delay(100);
		}
		p_interface->effect.l_congrate->actualFrame = 0;

		SDL_Delay(1000);
		return TRUE;
	}

	return FALSE;
}

/**
* \fn SDL_Rect getRealPosition(sPosition p_position)
* \brief Fonction qui convertit des position d'index en position réelles
*
* \param p_position structure de type sPosition
* \return SDL_Rect structure représentant des positions réelles
*/
SDL_Rect getRealPosition(sPosition p_position) {
	SDL_Rect l_position;

	l_position.x = (p_position.x * (WINDOW_WIDTH / CASE_COLUMN_AMOUNT));
	l_position.y = (p_position.y * (WINDOW_HEIGHT / CASE_LINE_AMOUNT));
	l_position.h = (WINDOW_HEIGHT / CASE_LINE_AMOUNT);
	l_position.w = (WINDOW_WIDTH / CASE_COLUMN_AMOUNT);

	return l_position;
}

/**
* \fn sPosition getMapPosition(SDL_Rect p_position)
* \brief Fonction qui convertit des réelles en position d'index
*
* \param p_position structure représentant des positions réelles
* \return sPosition structure de type sPosition
*/
sPosition getMapPosition(SDL_Rect p_position) {
	sPosition l_position;

	l_position.x = p_position.x / (WINDOW_WIDTH / CASE_COLUMN_AMOUNT);
	l_position.y = p_position.y / (WINDOW_HEIGHT / CASE_LINE_AMOUNT);

	return l_position;
}

/**
* \fn bool comparePositionRect(SDL_Rect p_firstPosition, SDL_Rect p_secondPosition)
* \brief Fonction qui compare des position réelles
*
* \param p_firstPosition structure représentant une position réelle
* \param p_secondPosition structure représentant une position réelle
* \return bool enum de type eBool vaut 1 si les positions son égales 0 sinon
*/
bool comparePositionRect(SDL_Rect p_firstPosition, SDL_Rect p_secondPosition) {
	if (p_firstPosition.x != p_secondPosition.x || p_firstPosition.y != p_secondPosition.y) {
		return FALSE;
	}

	return TRUE;
}

/**
* \fn bool comparePositionMap(sPosition p_firstPosition, sPosition p_secondPosition)
* \brief Fonction qui compare des position d'index
*
* \param p_firstPosition structure représentant une position d'index
* \param p_secondPosition structure représentant une position d'index
* \return bool enum de type eBool vaut 1 si les positions son égales 0 sinon
*/
bool comparePositionMap(sPosition p_firstPosition, sPosition p_secondPosition) {
	if (p_firstPosition.x != p_secondPosition.x || p_firstPosition.y != p_secondPosition.y) {
		return FALSE;
	}

	return TRUE;
}
