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
	SDL_RenderCopy(p_renderer, p_text->fontTexture, NULL, &p_text->posText);

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

	SDL_Rect l_posMouse, l_positionBG;
	SDL_Surface* l_background;
	SDL_Texture* l_backTexture;

	loadInterface(p_interface, p_map);
	gameLoop(p_interface, p_map);
	
	createFont(&l_play, p_interface->renderer, "PLAY");

	SDL_RenderPresent(p_interface->renderer); // Affichage


	while (l_loop){
		SDL_WaitEvent(&(p_interface->event));
		
		switch (p_interface->event.type){
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
						l_loop = 0;
						break;
				}
			case SDL_QUIT:
				l_loop = 0;
				break;
		}
	}

	closeFonts(l_play);
	closeInterface(p_interface);
	SDL_Quit();
	return;
}

void loadAnimation(sAnimation *p_animation, int p_frameAmount, SDL_Rect p_position, int p_idIndex, char *p_path) {

}

