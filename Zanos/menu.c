#include "menu.h"

void initFont(sText *p_text, SDL_Renderer *p_renderer, char* toWrite) {
	p_text->font = TTF_OpenFont("./assets/fonts/m12.ttf", 25);
	p_text->color.r = 0;
	p_text->color.g = 0;
	p_text->color.b = 0;
	p_text->surfaceText = TTF_RenderText_Blended(p_text->font, toWrite, p_text->color);

	p_text->posText.y = 100;
	p_text->posText.y = 200;

	p_text->fontTexture = SDL_CreateTextureFromSurface(p_renderer, p_text->surfaceText);
	SDL_QueryTexture(p_text->fontTexture, NULL, NULL, &(p_text->posText.w), &(p_text->posText.h));
	SDL_RenderCopy(p_renderer, p_text->fontTexture, NULL, &p_text->posText);
}

void createMenu(sInterface *p_interface, sText *p_text) {
	int continuer = 1, leftButtonState = 0;
	SDL_Rect l_posMouse, posBack;
	SDL_Surface* l_background;
	SDL_Texture* l_backTexture;

	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();

	p_interface->window = SDL_CreateWindow("ZANOS RACCOON", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,
		480,
		SDL_WINDOW_SHOWN);

	p_interface->renderer = SDL_CreateRenderer(p_interface->window, -1, SDL_RENDERER_ACCELERATED); // Cr�ation d'un SDL_Renderer utilisant l'acc�l�ration mat�rielle

	initFont(p_text, p_interface->renderer, "PLAY");

	l_background = SDL_LoadBMP("./assets/sprite/snow97.bmp");
	l_backTexture = SDL_CreateTextureFromSurface(p_interface->renderer, l_background); // Pr�paration du sprite	
	posBack.x = 640 / 2 - l_background->w / 2;
	posBack.y = 480 / 2 - l_background->h / 2;
	posBack.w = l_background->w;
	posBack.h = l_background->h;

	SDL_RenderCopy(p_interface->renderer, l_backTexture, NULL, &posBack);

	

	SDL_RenderPresent(p_interface->renderer); // Affichage
	SDL_Delay(3000); /* Attendre trois secondes, que l'utilisateur voit la fen�tre */


	while (continuer)
	{
		SDL_WaitEvent(&(p_interface->event));
		switch (p_interface->event.type)
		{
			case SDL_MOUSEBUTTONDOWN:
				SDL_GetMouseState(&(l_posMouse.x), &(l_posMouse.y));
				printf("(%d , %d)\n", l_posMouse.x, l_posMouse.y);
				leftButtonState = 1;
				break;

			case SDL_QUIT:
				continuer = 0;
				break;

		}
	}

	if (leftButtonState == 1) {
		//gameLoop();
		//if (posMouseX)
	}

}


void closeFonts(sText *p_text) {
	SDL_DestroyTexture(p_text->fontTexture); // Lib�ration de la m�moire associ�e � la texture
	SDL_FreeSurface(p_text->surfaceText);
	TTF_CloseFont(p_text->font);
	TTF_Quit();
}
