#include "graphx.h"
#include "menu.h"

void createFont(sText *p_text, SDL_Renderer *p_renderer, char* toWrite) {
	p_text->font = TTF_OpenFont("./assets/fonts/m12.ttf", 25);
	p_text->color.r = 0;
	p_text->color.g = 0;
	p_text->color.b = 0;

	p_text->posText.x = 100;
	p_text->posText.y = 180;
	p_text->posText.w = 50;
	p_text->posText.h = 50;

	p_text->surfaceText = TTF_RenderText_Blended(p_text->font, toWrite, p_text->color);


	p_text->fontTexture = SDL_CreateTextureFromSurface(p_renderer, p_text->surfaceText);
	SDL_QueryTexture(p_text->fontTexture, NULL, NULL, &(p_text->posText.w), &(p_text->posText.h));
	SDL_RenderCopy(p_renderer, p_text->fontTexture, NULL, &p_text->posText);
}

void createMenu(struct s_interface *p_interface, sMap *p_map) {
	int continuer = 1, leftButtonState = 0;
	SDL_Rect l_posMouse, posBack;
	SDL_Surface* l_background;
	SDL_Texture* l_backTexture;
	sText l_play;

	loadInterface(p_interface, p_map);

	l_background = SDL_LoadBMP("./assets/sprite/snowRaccoon.bmp");
	l_backTexture = SDL_CreateTextureFromSurface(p_interface->renderer, l_background); // Préparation du sprite	
	posBack.x = 640 / 2 - l_background->w / 2;
	posBack.y = 480 / 2 - l_background->h / 2;
	posBack.w = l_background->w;
	posBack.h = l_background->h;

	SDL_RenderCopy(p_interface->renderer, l_backTexture, NULL, &posBack);

	createFont(&l_play, p_interface->renderer, "PLAY");

	SDL_RenderPresent(p_interface->renderer); // Affichage


	while (continuer)
	{
		SDL_WaitEvent(&(p_interface->event));
		switch (p_interface->event.type)
		{
		case SDL_MOUSEBUTTONDOWN:
			SDL_GetMouseState(&(l_posMouse.x), &(l_posMouse.y));

			if (l_play.posText.x < l_posMouse.x && l_posMouse.x < l_play.posText.x + l_play.posText.w && l_play.posText.y < l_posMouse.y && l_posMouse.y < l_play.posText.y + l_play.posText.h) {
				gameLoop(p_interface, p_map);
				continuer = 0;
			}
			break;

		case SDL_KEYDOWN:
			switch (p_interface->event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				continuer = 0;
				break;

			default:
				break;
			}
		case SDL_QUIT:
			continuer = 0;
			break;

		}
	}

	closeFonts(l_play);
	closeInterface(p_interface);
	SDL_Quit();
	return;
}


void closeFonts(sText p_text) {
	SDL_DestroyTexture(p_text.fontTexture); // Libération de la mémoire associée à la texture
	SDL_FreeSurface(p_text.surfaceText);
	TTF_CloseFont(p_text.font);
	TTF_Quit();
}

void createAnim() {
	int l_i, continuer =1;
	char l_snowPath[158] = "./assets/sprite/frame-001.bmp";

	SDL_Window *window;
	SDL_Surface *l_tmpsprite;
	SDL_Renderer *renderer;
	SDL_Texture *snowTab[158];
	SDL_Event event;

	if (SDL_Init(SDL_INIT_EVERYTHING)) {
		fprintf(stdout, "[SDL] Initialization Error (%s)\n", SDL_GetError());
		return EXIT_FAILURE;
	}
	IMG_Init(IMG_INIT_PNG);

	window = SDL_CreateWindow("-TEST ANIM'-", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	if (!window) {
		fprintf(stderr, "[SDL] Window creation error (%s)\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	for (l_i = 0; l_i < 158; ++l_i) {
		l_snowPath[21] = (int)(l_i / 10) + 48;
		l_snowPath[22] = (l_i - (int)(l_i / 10) * 10) + 48;
		l_tmpsprite = SDL_LoadBMP(l_snowPath);
		snowTab[l_i] = SDL_CreateTextureFromSurface(renderer, l_tmpsprite);
		SDL_FreeSurface(l_tmpsprite);
		}

		/*SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);*/

		SDL_RenderPresent(renderer); // Affichage


		while (continuer)
		{
			SDL_WaitEvent(&(event));
			switch (event.type)
			{
			case SDL_MOUSEBUTTONDOWN:
				break;

			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					continuer = 0;
					break;

				default:
					break;
				}
			case SDL_QUIT:
				continuer = 0;
				break;

			}
		}

		SDL_Quit();
		return;
}