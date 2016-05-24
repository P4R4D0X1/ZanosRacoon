#include "menu.h"

void createMenu() {
	TTF_Init();

	SDL_Surface *texte;
	TTF_Font *font = NULL;
	font = TTF_OpenFont("./assets/fonts/edosz.ttf", 30);
	SDL_Color noir = {0, 0, 0};

	texte = TTF_RenderText_Blended(font, "ZanosRaccoon", noir);


}


void closeFonts(font) {

	TTF_CloseFont(font);
	TTF_Quit();

}
