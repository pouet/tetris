#include <stdio.h>
#include <time.h>
#include "SDL.h"
#include "tetris.h"
#include "frame.h"
#include "menu.h"
#include "game.h"

struct gVars_s gVars;

void	quitVideo(void) {
	SDL_DestroyRenderer(gVars.pRen);
	SDL_DestroyWindow(gVars.pWin);
}

int		initVideo(void) {
	if (SDL_Init(SDL_FLAGS) < 0) {
		fprintf(stderr, "SDL_Init : %s\n", SDL_GetError());
		return -1;
	}
	atexit(SDL_Quit);

	gVars.pWin = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, WIN_W, WIN_H, 0);
	if (gVars.pWin == NULL) {
		fprintf(stderr, "SDL_Init : %s\n", SDL_GetError());
		return -1;
	}

	gVars.pRen = SDL_CreateRenderer(gVars.pWin, -1, SDL_RENDERER_ACCELERATED);
	if (gVars.pRen == NULL) {
		fprintf(stderr, "SDL_Init : %s\n", SDL_GetError());
		return -1;
	}

	SDL_SetRenderDrawBlendMode(gVars.pRen, SDL_BLENDMODE_NONE);
	SDL_SetRenderDrawColor(gVars.pRen, 0xff, 0xff, 0xff, 0x00);

	return 0;
}

SDL_Texture *loadBMP(char *s) {
	SDL_Surface *pSfc;
	SDL_Texture *pTex;

	pSfc = SDL_LoadBMP(s);
	if (pSfc == NULL) {
		fprintf(stderr, "LoadBMP failed: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	SDL_SetColorKey(pSfc, SDL_TRUE, SURFACE_TRANSPARENT_COLOR);
	pTex = SDL_CreateTextureFromSurface(gVars.pRen, pSfc);
	if (pTex == NULL) {
		fprintf(stderr, "CreateTextureFromSurface failed: %s\n", SDL_GetError());
		exit(1);
	}
	SDL_FreeSurface(pSfc);
	SDL_SetTextureBlendMode(pTex, SDL_BLENDMODE_BLEND);
	return pTex;
}

int		initGVars(void) {
	gVars.nScrW = WIN_W;
	gVars.nScrH = WIN_H;
	gVars.pKeyb = SDL_GetKeyboardState(NULL);
	gVars.pTetsImg = loadBMP("gfx/tets.bmp");
	gVars.pFont = loadBMP("gfx/font.bmp");
	gVars.pIntroImg = loadBMP("gfx/intro.bmp");
	gVars.pTetrisLogo = loadBMP("gfx/tetris_logo.bmp");
	return 0;
}

int		init(void) {
	if (initVideo() < 0)
		return -1;
	srand(time(NULL));
	if (initGVars())
		return -1;
	return 0;
}


void renderFlip(void) {
	SDL_RenderPresent(gVars.pRen);
	SDL_RenderClear(gVars.pRen);
	frameWait();
}

void blitTexture(SDL_Texture *pTex, int x, int y, SDL_Rect *rClip) {
	SDL_Rect r;

	r.x = x;
	r.y = y;
	SDL_QueryTexture(pTex, NULL, NULL, &r.w, &r.h);
	SDL_RenderCopy(gVars.pRen, pTex, rClip, &r);
}











/* SDLK_LAST no more exists... leave me alone... */
int		eventHandler(void) {
	SDL_Event ev;

	while (SDL_PollEvent(&ev)) {
		if (ev.type == SDL_QUIT)
			return 1;
		else if (ev.key.type == SDL_KEYDOWN && ev.key.repeat == 0) {
			if (ev.key.keysym.sym == SDLK_SPACE)
				gVars.nKeyb[KEY_SPACE] = KEY_PRESSED;
			if (ev.key.keysym.sym == SDLK_UP)
				gVars.nKeyb[KEY_UP] = KEY_PRESSED;
			if (ev.key.keysym.sym == SDLK_DOWN)
				gVars.nKeyb[KEY_DOWN] = KEY_PRESSED;
			if (ev.key.keysym.sym == SDLK_LEFT)
				gVars.nKeyb[KEY_LEFT] = KEY_PRESSED;
			if (ev.key.keysym.sym == SDLK_RIGHT)
				gVars.nKeyb[KEY_RIGHT] = KEY_PRESSED;
			if (ev.key.keysym.sym == SDLK_p)
				gVars.nKeyb[KEY_P] = KEY_PRESSED;
			if (ev.key.keysym.sym == SDLK_c)
				gVars.nKeyb[KEY_C] = KEY_PRESSED;
		}
		else if (ev.type == SDL_KEYUP) {
			if (ev.key.keysym.sym == SDLK_SPACE)
				gVars.nKeyb[KEY_SPACE] = KEY_NONE;
			if (ev.key.keysym.sym == SDLK_UP)
				gVars.nKeyb[KEY_UP] = KEY_NONE;
			if (ev.key.keysym.sym == SDLK_DOWN)
				gVars.nKeyb[KEY_DOWN] = KEY_NONE;
			if (ev.key.keysym.sym == SDLK_LEFT)
				gVars.nKeyb[KEY_LEFT] = KEY_NONE;
			if (ev.key.keysym.sym == SDLK_RIGHT)
				gVars.nKeyb[KEY_RIGHT] = KEY_NONE;
			if (ev.key.keysym.sym == SDLK_p)
				gVars.nKeyb[KEY_P] = KEY_NONE;
			if (ev.key.keysym.sym == SDLK_c)
				gVars.nKeyb[KEY_C] = KEY_NONE;
		}
	}
	if (gVars.pKeyb[SDL_SCANCODE_ESCAPE])
		return 1;
	return 0;
}

menu_e menuLoop(pFct pInit, pFct pMain, pFct pRelease, void *pArgs) {
	menu_e nMenu;

	if (pInit(pArgs) < 0)
		return MENU_QUIT;

	franeInit();
	nMenu = MENU_NULL;
	while (nMenu == MENU_NULL) {
		if (eventHandler() != 0) {
			nMenu = MENU_QUIT;
			break;
		}
		nMenu = pMain(pArgs);
		renderFlip();
	}

	if (pRelease(pArgs) < 0)
		return MENU_QUIT;
	return nMenu;
}

int mainLoop(void) {
	intro_t intro;
	menu_t menu;
	game_t game;
	menu_e nState;
	int nLoop;

//	nState = MENU_INTRO;
	nState = MENU_GAME;
	nLoop = 1;
	while (nLoop) {
		switch (nState) {
			case MENU_INTRO:
				nState = menuLoop(menuIntroInit, menuIntroMain, menuIntroRelease, &intro);
				break;

			case MENU_MAIN:
				nState = menuLoop(menuMainInit, menuMainMain, menuMainRelease, &menu);
				break;

			case MENU_OPTS:
				break;

			case MENU_HISCORES:
				break;

			case MENU_GAME:
				nState = menuLoop(gameInit, gameMain, gameRelease, &game);
				break;

			case MENU_QUIT:
				nLoop = 0;
				break;

			default:
				nState = MENU_QUIT;
				break;
		}
//		if (eventHandler() || gVars.pKeyb[SDL_SCANCODE_ESCAPE])
//			break ;

//		SDL_UpdateTexture(gVars.img.tex, NULL, gVars.pixels, gVars.img.pitch);
//		SDL_RenderCopy(gVars.pRen, gVars.img.tex, NULL, NULL);

//		SDL_RenderClear(gVars.pRen); // Clear the entire screen
//		game_t g;
//		drawTetros(&g);
		//renderRexture(gVars.pTetsImg, 0, 0);
//		SDL_RenderPresent(gVars.pRen);
//		frameWait();
	}
	return 0;
}

int		main(void) {
	if (init() < 0)
		return EXIT_FAILURE;

	mainLoop();
	quitVideo();
	return 0;
}
