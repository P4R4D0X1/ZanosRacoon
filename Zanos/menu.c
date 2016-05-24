#include "menu.h"

void createMenu() {

	//-----Partie test d'Aurore------------------------------------------------------
	SDL_Surface *texte = NULL;
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


	TTF_Font *font = NULL;
	font = TTF_OpenFont("./assets/fonts/m12.ttf", 25);
	SDL_Color noir = { 0, 0, 0 };

	texte = TTF_RenderText_Blended(font, "PLAY", noir);
	SDL_Rect posTxt = { 640 / 2 - pSprite->w / 2 + 100, 480 / 2 - pSprite->h / 2 + 200, 0, 0 };
	SDL_Texture *fontTexture = SDL_CreateTextureFromSurface(pRenderer, texte);
	SDL_QueryTexture(fontTexture, NULL, NULL, &posTxt.w, &posTxt.h);


	SDL_RenderCopy(pRenderer, pTexture, NULL, &posSnow); // Copie du sprite grâce au SDL_Renderer
	SDL_RenderCopy(pRenderer, fontTexture, NULL, &posTxt);

	SDL_RenderPresent(pRenderer); // Affichage
	SDL_Delay(3000); /* Attendre trois secondes, que l'utilisateur voit la fenêtre */


	while (continuer)
	{
		SDL_WaitEvent(&event);
		switch (event.type)
		{
		case SDL_MOUSEBUTTONDOWN:
			SDL_GetMouseState(&posMouseX, &posMouseY);
			if (posTxt.x <= posMouseX <= posTxt.x + posTxt.w && posTxt.y <= posMouseY <= posTxt.y + posTxt.h)
				printf("\nOKAY\n");
			break;

		case SDL_QUIT:
			continuer = 0;
			break;
		}

	}

	SDL_DestroyTexture(pTexture); // Libération de la mémoire associée à la texture
	SDL_FreeSurface(pSprite); // Libération de la ressource occupée par le sprite

	TTF_CloseFont(font);
	TTF_Quit();
	SDL_FreeSurface(texte);
	SDL_Quit();
}


void closeFonts(font) {

	TTF_CloseFont(font);
	TTF_Quit();

}
