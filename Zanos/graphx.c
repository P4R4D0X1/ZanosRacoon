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
		l_casePath[22] = (l_i - (int)(l_i / 10)) + 48;
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
		SDL_DestroyTexture(p_interface->playerGraphx.playerSprite[l_i]);
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

	//displayMap(p_interface, p_map);

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
	
	for (l_i = 0; l_i < p_map->mapDimension.height; ++l_i) {
		for (l_j = 0; l_j < p_map->mapDimension.width; ++l_j) {


		}
	}
	

	//Coucou ma belle il est tard je te fait des petits TODO parceque je t'aime fort
	//T'es adorable quand tu dort

	//TODO : Afficher la map en parcourant le tableau de case

	/*[ALGORITHME]
		ENTIER: i, j
		POSITION: positionCase

		positionCase.x <= 0
		positionCase.y <= 0

		TANT QUE i PLUS PETIT QUE hauteur tableau FAIRE
			TANT QUE j PLUS PETIT QUE largeur tableau FAIRE
				rendercopy() de la texture corespondant au type de la case du tableau en positionCase
				positionCase.x += tailleCase
			FIN TANT QUE
				positionCase.y += tailleCase
		FIN TANT QUE
		renderpresent() pour afficher le rendu

		[FIN ALGORITHME]

		(*)AIDE(*)
			*obtenir la hauteur du tableau*
				-la structure p_map contient une structure sDimension qui contient la hauteur : p_map->mapDimension.height
			
			*obtenir la largeur du tableau*
				-la structure p_map contient une structure sDimension qui contient la largeur : p_map->mapDimension.width
			*obtenir le type de la case à l'index (i,j)*
				-la structure sMap contien un tableau de sCase accesible par : p_map->path[i][j].type
			
			*rendercopy()*
				SDL_RenderCopy(renderer, texture, NULL, &position)
				(cette fonction te permet de charger dans le renderer un sprite a afficher à une certaine position)
				-le renderer est contenu dans la structure sInterface : p_interface->renderer
				-la texture de type x est stocké dans la structure d'interface : p_interface->caseSprite[x]
				-la position est un type SDL_Rect

			*renderpresent()*
				SDL_RenderPresent(renderer);
				(cette fonction affiche enfin à l'ecran toute les texture que tu aura chargé dans le renderer au cour de la double boucle)
				-le renderer est contenu dans la structure sInterface : p_interface->renderer
				
	*/

	return 0;
}	

