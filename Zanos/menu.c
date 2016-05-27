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
* \param *p_message chaine de caract�re � afficher
* \param p_color structure de type SDL_Color repr�sentant une couleur d'affichage
* \param p_position structure de type SDL_Rect repr�sentant des positions r�elles
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
	SDL_DestroyTexture(fontTexture); // Lib�ration de la m�moire associ�e � la texture
	TTF_CloseFont(font);
	//TTF_Quit();

	return;
}

/**
* \fn void centrerPosition(SDL_Rect *p_posSprite, SDL_Rect p_offset)
* \brief Fonction de calcul de position
*
* \param *p_posSprite pointeur vers une structure de type SDL_Rect repr�sentant une positions r�elles
* \param *p_offset structure de type SDL_Rect repr�sentant l'offset de la position
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
	sAnimation *l_animation = NULL, *l_raccoon = NULL, *l_logo = NULL, *l_play = NULL, *l_tuto = NULL;

	SDL_Rect l_posMouse, l_posBG, l_posRaccoon, l_posLogo, l_offset, l_posPlay;

	loadInterface(&l_interface);

	l_posBG.x = 0;
	l_posBG.y = 0;
	l_posBG.h = WINDOW_HEIGHT;
	l_posBG.w = WINDOW_WIDTH;

	l_posRaccoon.h = 250;
	l_posRaccoon.w = 250;
	l_posRaccoon.x = WINDOW_HEIGHT - l_posRaccoon.h;
	l_posRaccoon.y = WINDOW_WIDTH - l_posRaccoon.w;
	l_offset.x = 1000;
	l_offset.y = 1000;
	l_offset.w = -1;
	l_offset.h = -1;

	l_posLogo.h = 400;
	l_posLogo.w = 400;
	l_offset.x = 10;
	l_offset.y = 10;
	l_offset.w = 0;
	l_offset.h = -1;
	centrerPosition(&l_posLogo, l_offset);

	l_posPlay.w = 200;
	l_posPlay.h = 100;
	l_offset.x = 10;
	l_offset.y = 10;
	l_offset.w = 0;
	l_offset.h = 0;
	centrerPosition(&l_posPlay, l_offset);

	l_posMouse.w = 19;
	l_posMouse.h = 19;

	loadAnimation(0, &l_animation, 159, l_posBG, "./assets/sprite/anim/mountain_", &l_interface, 3);
	loadAnimation(1, &l_raccoon, 3, l_posRaccoon, "./assets/sprite/anim/raccoon-skate_", &l_interface, 10);
	loadAnimation(1, &l_logo, 2, l_posLogo, "./assets/sprite/anim/raccoonzanos_", &l_interface, 100);
	loadAnimation(1, &l_play, 4, l_posPlay, "./assets/sprite/anim/play_", &l_interface, 5);
	loadAnimation(1, &l_tuto, 8, l_posBG, "./assets/sprite/anim/tuto_", &l_interface, 1);

	Mix_PlayMusic(l_interface.sonor.musicMenu, -1);

	while (l_loop) {

		while (SDL_PollEvent(&(l_interface.event))) {
			switch (l_interface.event.type) {
				case SDL_MOUSEBUTTONDOWN:
					SDL_GetMouseState(&(l_posMouse.x), &(l_posMouse.y));

					if (l_posPlay.x < l_posMouse.x && l_posMouse.x < l_posPlay.x + l_posPlay.w && l_posPlay.y < l_posMouse.y && l_posMouse.y < l_posPlay.y + l_posPlay.h) {
					
						Mix_PauseMusic();
						Mix_PlayMusic(l_interface.sonor.musicGame, -1);

						while (l_tuto->actualFrame != l_tuto->frameAmount - 1){
							updateAnimation(l_tuto, &l_interface);
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


		updateAnimation(l_animation, &l_interface);
		updateAnimation(l_raccoon, &l_interface);
		updateAnimation(l_logo, &l_interface);
		
		SDL_GetMouseState(&(l_posMouse.x), &(l_posMouse.y));

		if (!(l_posPlay.x < l_posMouse.x && l_posMouse.x < l_posPlay.x + l_posPlay.w && l_posPlay.y < l_posMouse.y && l_posMouse.y < l_posPlay.y + l_posPlay.h)) {
			l_play->load = 1;
		}

		updateAnimation(l_play, &l_interface);

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
* \param type � 0 si l'animation est compos�e de BMP, � 1 si elle est compos�e de PNG
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
* \fn void updateAnimation(sAnimation *p_animation, struct s_interface *p_interface)
* \brief Fonction qui met a jour une animation
*
* \param type � 0 si l'animation est compos�e de BMP, � 1 si elle est compos�e de PNG
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
* \brief Fonction qui r�cup�re un chiffre � un index donn� dans un nombre
*
* \param p_number un nombre dont on veut extraire un chiffre
* \param p_digit index du chiffre que l'ont  veut extraire
*/
int getDigit(int p_number, int p_digit) {
	return (int)(((p_number / (int)pow(10, p_digit)) - (((p_number / (int)pow(10, p_digit)) /10) * 10)));
}