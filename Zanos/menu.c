/**
* \file menu.c
* \brief Programme de rendu du menu de l'enigme
* \date 27 mai 2016
*
* Programme qui realise le rendu, l'affichage et l'interfacage du menu de l'enigme
*
*/
#include "graphx.h"
#include "menu.h"

/**
* \fn void displayText(SDL_Renderer *p_renderer, char *p_message, SDL_Color p_color, SDL_Rect p_position)
* \brief Fonction d'afficahge de text
*
* \param *p_renderer pointeur vers une structure de type SDL_Renderer
* \param *p_message chaine de caractère à afficher
* \param p_color structure de type SDL_Color représentant une couleur d'affichage
* \param p_position structure de type SDL_Rect représentant des positions réelles
*/
void displayText(SDL_Renderer *p_renderer, char *p_message, SDL_Color p_color, SDL_Rect p_position) {
	SDL_Surface *l_surface;
	TTF_Font *font;
	SDL_Texture *fontTexture;

	font = TTF_OpenFont("./assets/fonts/m12.ttf", 25);
	
	l_surface = TTF_RenderText_Blended(font, p_message, p_color);

	fontTexture = SDL_CreateTextureFromSurface(p_renderer, l_surface);
	SDL_QueryTexture(fontTexture, NULL, NULL, &(p_position.w), &(p_position.h));
	SDL_RenderCopy(p_renderer, fontTexture, NULL, &p_position);
	SDL_FreeSurface(l_surface);
	SDL_DestroyTexture(fontTexture); // Libération de la mémoire associée à la texture
	TTF_CloseFont(font);
	//TTF_Quit();

	return;
}

/**
* \fn void centrerPosition(SDL_Rect *p_posSprite, SDL_Rect p_offset)
* \brief Fonction de calcul de position
*
* \param *p_posSprite pointeur vers une structure de type SDL_Rect représentant une positions réelles
* \param *p_offset structure de type SDL_Rect représentant l'offset de la position
*/
void centrerPosition(SDL_Rect *p_posSprite, SDL_Rect p_offset) {
	p_posSprite->x = ((WINDOW_WIDTH - p_posSprite->w)/2) + (p_offset.w * (WINDOW_WIDTH / p_offset.x));
	p_posSprite->y = ((WINDOW_HEIGHT - p_posSprite->h)/2) + (p_offset.h * (WINDOW_HEIGHT / p_offset.y));
}

/**
* \fn void createMenu()
* \brief Fonction rendu graphique du menu
*/
void createMenu() {
	
	sMap *l_map = NULL;
	sInterface l_interface;
	bool l_loop = TRUE, l_littleLoop = TRUE;

	SDL_Rect l_posMouse = {0, 0, 20, 20};

	loadInterface(&l_interface);

	Mix_PlayMusic(l_interface.sonor.musicMenu, -1);

	while (l_loop) {

		while (SDL_PollEvent(&(l_interface.event))) {
			switch (l_interface.event.type) {
				case SDL_MOUSEBUTTONDOWN:
					SDL_GetMouseState(&(l_posMouse.x), &(l_posMouse.y));

					if (l_interface.effect.l_play->position.x < l_posMouse.x && l_posMouse.x < l_interface.effect.l_play->position.x + l_interface.effect.l_play->position.w && l_interface.effect.l_play->position.y < l_posMouse.y && l_posMouse.y < l_interface.effect.l_play->position.y + l_interface.effect.l_play->position.h) {
					
						Mix_PauseMusic();
						Mix_PlayMusic(l_interface.sonor.musicGame, -1);

						while (l_interface.effect.l_tuto->actualFrame != l_interface.effect.l_tuto->frameAmount - 1){
							updateAnimation(l_interface.effect.l_tuto, &l_interface);
							SDL_RenderPresent(l_interface.renderer);

							SDL_PumpEvents();
							while (!(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))) {
								SDL_PumpEvents();
							}
							SDL_Delay(100);
						} 

						loadMap(&l_map, "map2.txt");
						generateGraph(l_map);
						gameLoop(&l_interface, l_map);
						free(l_map);

						loadMap(&l_map, "map1.txt");
						generateGraph(l_map);
						gameLoop(&l_interface, l_map);
						free(l_map);

						loadMap(&l_map, "map0.txt");
						generateGraph(l_map);
						gameLoop(&l_interface, l_map);
						free(l_map);
						Mix_PauseMusic();
						Mix_PlayMusic(l_interface.sonor.musicMenu, -1);
					}
					break;

				case SDL_KEYDOWN:
					switch (l_interface.event.key.keysym.sym) {
						case SDLK_ESCAPE:
							l_loop = FALSE;
							break;
					}
					break;
				case SDL_QUIT:
					l_loop = FALSE;
					break;
			}
		}


		updateAnimation(l_interface.effect.l_mountain, &l_interface);
		updateAnimation(l_interface.effect.l_raccoon, &l_interface);
		updateAnimation(l_interface.effect.l_logo, &l_interface);
		
		SDL_GetMouseState(&(l_posMouse.x), &(l_posMouse.y));

		if (!(l_interface.effect.l_play->position.x < l_posMouse.x && l_posMouse.x < l_interface.effect.l_play->position.x + l_interface.effect.l_play->position.w && l_interface.effect.l_play->position.y < l_posMouse.y && l_posMouse.y < l_interface.effect.l_play->position.y + l_interface.effect.l_play->position.h)) {
			l_interface.effect.l_play->load = 1;
		}

		updateAnimation(l_interface.effect.l_play, &l_interface);

		l_posMouse.x -= l_posMouse.w / 2;
		l_posMouse.y -= l_posMouse.h / 2;

		SDL_RenderCopy(l_interface.renderer, l_interface.cursor, NULL, &(l_posMouse));
		SDL_RenderPresent(l_interface.renderer);
		SDL_Delay(SDL_ANIMATION_FRAMETIME);
	}

	
	closeInterface(&l_interface);
	SDL_Quit();
	return;
}

/**
* \fn void loadAnimation(int type, sAnimation **p_animation, int p_frameAmount, SDL_Rect p_position, char *p_path, struct s_interface *p_interface, int p_speed)
* \brief Fonction d'initialisation d'animation
*
* \param type à 0 si l'animation est composée de BMP, à 1 si elle est composée de PNG
* \param **p_animation double pointeur vers une animation
* \param p_frameAmount nombre de frame que contient l'animation
* \param p_position position d'affichage de l'animation
* \param *p_path prefixe du chemin des fichiers d'animations
* \param *p_interface interface de l'enigme
* \param p_speed vitesse d'animation 
*/
void loadAnimation(int type, sAnimation **p_animation, int p_frameAmount, SDL_Rect p_position, char *p_path, struct s_interface *p_interface, int p_speed) {
	int l_i, l_j, l_digitAmount = 0, l_tmp = p_frameAmount;
	char l_path[100] = "", l_tmpy[50] = "";

	SDL_Surface *l_sprite = NULL;

	strcpy_s(l_path, sizeof(l_path), p_path);
	
	*p_animation = malloc(sizeof(sAnimation));

	(*p_animation)->frameAmount = p_frameAmount;
	(*p_animation)->actualFrame = 0;
	(*p_animation)->position = p_position;
	(*p_animation)->sprite = malloc(p_frameAmount * sizeof(SDL_Texture*));
	(*p_animation)->speed = p_speed;
	(*p_animation)->load = 0;

	while (l_tmp != 0) {
		l_digitAmount++;
		l_tmp /= 10;
	}

	for (l_i = 0; l_i < p_frameAmount; ++l_i) {
		strcpy_s(l_path, sizeof(l_path), "");
		strcat_s(l_path, sizeof(l_path), p_path);

		for (l_j = l_digitAmount-1; l_j >= 0; l_j--) {
			memset(l_tmpy, getDigit(l_i, l_j)+48, 1);
			strcat_s(l_path, sizeof(l_path), l_tmpy);
		}

		if (type == 0) {
			strcat_s(l_path, sizeof(l_path), ".bmp");
			l_sprite = SDL_LoadBMP(l_path);
		}
		else if (type == 1) {
			strcat_s(l_path, sizeof(l_path), ".png");
			l_sprite = IMG_Load(l_path);
		}
		
		(*p_animation)->sprite[l_i] = SDL_CreateTextureFromSurface(p_interface->renderer, l_sprite);
		SDL_FreeSurface(l_sprite);

		printf("%s\n", l_path);
	}
	
}

/**
* \fn void freeAnimation(sAnimation *p_animation)
* \brief Fonction de desallocation d'animation
*
* \param *p_animation une animation
*/
void freeAnimation(sAnimation *p_animation) {
	int l_i;

	for (l_i = 0; l_i < p_animation->frameAmount; ++l_i) {
		SDL_DestroyTexture(p_animation->sprite[l_i]);
	}
	
	free(p_animation->sprite);
	p_animation->sprite = NULL;
	free(p_animation);
}

/**
* \fn void updateAnimation(sAnimation *p_animation, struct s_interface *p_interface)
* \brief Fonction qui met a jour une animation
*
* \param type à 0 si l'animation est composée de BMP, à 1 si elle est composée de PNG
* \param *p_animation pointeur vers une animation
* \param *p_interface interface de l'enigme
*/
void updateAnimation(sAnimation *p_animation, struct s_interface *p_interface) {
	if (p_animation->load == 0) {
		p_animation->actualFrame++;
		p_animation->actualFrame %= p_animation->frameAmount;
		p_animation->load++;
	}

	else {
		p_animation->load++;
		p_animation->load %= p_animation->speed;
	}
	SDL_RenderCopy(p_interface->renderer, p_animation->sprite[p_animation->actualFrame], NULL, &(p_animation->position));
}

/**
* \fn int getDigit(int p_number, int p_digit)
* \brief Fonction qui récupère un chiffre à un index donné dans un nombre
*
* \param p_number un nombre dont on veut extraire un chiffre
* \param p_digit index du chiffre que l'ont  veut extraire
*/
int getDigit(int p_number, int p_digit) {
	return (int)(((p_number / (int)pow(10, p_digit)) - (((p_number / (int)pow(10, p_digit)) /10) * 10)));
}