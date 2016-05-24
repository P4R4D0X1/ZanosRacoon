#include "menu.h"

void initFont(sText *p_text, SDL_Renderer *p_renderer, char* toWrite) {
	p_text->font = TTF_OpenFont("./assets/fonts/m12.ttf", 25);
	p_text->color.r = 0;
	p_text->color.g = 0;
	p_text->color.b = 0;
	p_text->surfaceText = TTF_RenderText_Blended(p_text->font, toWrite, p_text->color);

	//p_text->posText.y = 640 / 2 - pSprite->w / 2 + 100;
	//p_text->posText.y = 480 / 2 - pSprite->h / 2 + 200;

	p_text->fontTexture = SDL_CreateTextureFromSurface(p_renderer, p_text);
	SDL_QueryTexture(p_text->fontTexture, NULL, NULL, &(p_text->posText.w), &(p_text->posText.h));
	SDL_RenderCopy(p_renderer, p_text->fontTexture, NULL, &p_text->posText);
}

void createWindow() {
	SDL_Event event;

	int continuer = 1;
	int posMouseX, posMouseY;

	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();

	SDL_Window* pWindow = NULL;
	pWindow = SDL_CreateWindow("ZANOS RACCOON", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,
		480,
		SDL_WINDOW_SHOWN);

	SDL_Renderer *pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED); // Création d'un SDL_Renderer utilisant l'accélération matérielle

	SDL_Surface* pSprite = SDL_LoadBMP("./assets/sprite/snow97.bmp");
	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pSprite); // Préparation du sprite	
	SDL_Rect posSnow = { 640 / 2 - pSprite->w / 2,480 / 2 - pSprite->h / 2, pSprite->w, pSprite->h };
	SDL_RenderCopy(pRenderer, pTexture, NULL, &posSnow);

	SDL_RenderPresent(pRenderer); // Affichage
	SDL_Delay(3000); /* Attendre trois secondes, que l'utilisateur voit la fenêtre */


	while (continuer)
	{
		SDL_WaitEvent(&event);
		switch (event.type)
		{
		case SDL_MOUSEBUTTONDOWN:
			SDL_GetMouseState(&posMouseX, &posMouseY);
			/*if (p_text->posText.x <= posMouseX <= posTxt.x + posTxt.w && posTxt.y <= posMouseY <= posTxt.y + posTxt.h)
				printf("\nOKAY\n");*/
			break;

		case SDL_QUIT:
			continuer = 0;
			break;
		}

	}
}

void createMenu(sText *p_text) {



}


void closeFonts(sText *p_text) {
	SDL_DestroyTexture(p_text->fontTexture); // Libération de la mémoire associée à la texture
	SDL_FreeSurface(p_text->surfaceText);
	TTF_CloseFont(p_text->font);
	TTF_Quit();

}
