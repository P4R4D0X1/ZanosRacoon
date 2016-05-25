#include "graphx.h"
#include "menu.h"

void createFont(sText *p_text, SDL_Renderer *p_renderer, char *p_message) {
	p_text->font = TTF_OpenFont("./assets/fonts/m12.ttf", 25);
	p_text->color.r = 0;
	p_text->color.g = 0;
	p_text->color.b = 0;

	p_text->posText.w = 50;
	p_text->posText.h = 50;
	p_text->posText.x = (WINDOW_WIDTH / 2) - (p_text->posText.w / 2);
	p_text->posText.y = WINDOW_HEIGHT - (WINDOW_HEIGHT/20);
	
	p_text->surfaceText = TTF_RenderText_Blended(p_text->font, p_message, p_text->color);


	p_text->fontTexture = SDL_CreateTextureFromSurface(p_renderer, p_text->surfaceText);
	SDL_QueryTexture(p_text->fontTexture, NULL, NULL, &(p_text->posText.w), &(p_text->posText.h));

	return;
}

void closeFonts(sText p_text) {
	SDL_DestroyTexture(p_text.fontTexture); // Libération de la mémoire associée à la texture
	SDL_FreeSurface(p_text.surfaceText);
	TTF_CloseFont(p_text.font);
	TTF_Quit();

}

void createMenu(struct s_interface *p_interface, sMap *p_map) {
	bool l_loop = TRUE;

	sText l_play;
	sAnimation *l_animation = NULL;

	SDL_Rect l_posMouse, l_posBG;

	loadInterface(p_interface, p_map);	
	createFont(&l_play, p_interface->renderer, "PLAY");
	
	l_posBG.x = 0;
	l_posBG.y = 0;
	l_posBG.h = WINDOW_HEIGHT;
	l_posBG.w = WINDOW_WIDTH;

	loadAnimation(&l_animation, 3, l_posBG, 30,"./assets/sprite/anim/mountain_", p_interface);

	while (l_loop) {

		while (SDL_PollEvent(&(p_interface->event))) {
			switch (p_interface->event.type) {
				case SDL_MOUSEBUTTONDOWN:
					SDL_GetMouseState(&(l_posMouse.x), &(l_posMouse.y));

					if (l_play.posText.x < l_posMouse.x && l_posMouse.x < l_play.posText.x + l_play.posText.w && l_play.posText.y < l_posMouse.y && l_posMouse.y < l_play.posText.y + l_play.posText.h) {
						gameLoop(p_interface, p_map);
						l_loop = 0;
					}
					break;
				case SDL_KEYDOWN:
					switch (p_interface->event.key.keysym.sym) {
						case SDLK_ESCAPE:
							l_loop = FALSE;
							break;
					}
				case SDL_QUIT:
					l_loop = FALSE;
					break;
			}
		}

		updateAnimation(l_animation, p_interface);
		SDL_RenderCopy(p_interface->renderer, l_play.fontTexture, NULL, &l_play.posText);
		SDL_RenderPresent(p_interface->renderer);
	}

	closeFonts(l_play);
	closeInterface(p_interface);
	SDL_Quit();
	return;
}

void loadAnimation(sAnimation **p_animation, int p_frameAmount, SDL_Rect p_position, int p_idIndex, char *p_path, struct s_interface *p_interface) {
	int l_i, l_j, l_digitAmount = 0, l_tmp = p_frameAmount;
	char l_path[100] = "", l_tmpy[50] = "";

	SDL_Surface *l_sprite;

	strcpy_s(l_path, sizeof(l_path), p_path);
	
	*p_animation = malloc(sizeof(sAnimation));

	(*p_animation)->frameAmount = p_frameAmount;
	(*p_animation)->actualFrame = 0;
	(*p_animation)->position = p_position;
	(*p_animation)->sprite = malloc(sizeof(SDL_Texture*) * p_frameAmount);

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
		strcat_s(l_path, sizeof(l_path), ".bmp");

		l_sprite = SDL_LoadBMP(l_path);
		(*p_animation)->sprite[l_i] = SDL_CreateTextureFromSurface(p_interface->renderer, l_sprite);
		SDL_FreeSurface(l_sprite);

		printf("%s\n", l_path);
	}
	
}

void updateAnimation(sAnimation *p_animation, struct s_interface *p_interface) {
	SDL_RenderCopy(p_interface->renderer, p_animation->sprite[p_animation->actualFrame], NULL, &(p_animation->position));
	p_animation->actualFrame++;
	p_animation->actualFrame %= p_animation->frameAmount;
}

int getDigit(int p_number, int p_digit) {
	return (int)(((p_number / pow(10, p_digit)) - ((p_number/10) * 10)));
}