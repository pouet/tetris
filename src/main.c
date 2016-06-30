#include <stdio.h>
#include <time.h>
#include "SDL.h"
#include "tetris.h"
#include "frame.h"

struct gVars_s gVars;

point_t gTetros[NTETS][NBLOCKS] = {
	{ { 0, -2 }, { 0, -1 }, { 0, 0 }, { 0, 1 } },
	{ { -1, -1 }, { 0, -1 }, { -1, 0 }, { 0, 0 } },
	{ { -1, 0 }, { 0, 0 }, { 1, 0 }, { 0, -1 } },
	{ { -1, 0 }, { 0, 0 }, { 0, -1 }, { 1, -1 } },
	{ { 1, 0 }, { 0, 0 }, { 0, -1 }, { -1, -1 } },
	{ { -1, 1 }, { 0, 1 }, { 0, 0 }, { 0, -1 } },
	{ { 1, 1 }, { 0, 1 }, { 0, 0 }, { 0, -1 } }
};

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
	SDL_SetRenderDrawColor(gVars.pRen, 0, 255, 0, 255);

	return 0;
}
#include <unistd.h>
SDL_Texture *loadBMP(char *s) {
	SDL_Surface *pSfc;
	SDL_Texture *pTex;

	pSfc = SDL_LoadBMP(s);
	if (pSfc == NULL) {
		fprintf(stderr, "LoadBMP failed: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	pTex = SDL_CreateTextureFromSurface(gVars.pRen, pSfc);
	if (pTex == NULL) {
		fprintf(stderr, "CreateTextureFromSurface failed: %s\n", SDL_GetError());
		exit(1);
	}
	SDL_FreeSurface(pSfc);
	return pTex;
}

int		initGVars(void) {
	gVars.nScrW = WIN_W;
	gVars.nScrH = WIN_H;
	gVars.pKeyb = SDL_GetKeyboardState(NULL);
	gVars.pTetsImg = loadBMP("gfx/tets.bmp");
	gVars.pIntroImg = loadBMP("gfx/intro.bmp");
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

void	renderRexture(SDL_Texture *pTex, int x, int y) {
	SDL_Rect rDst;
	SDL_Rect rSrc;

	rSrc.x = 64;
	rSrc.y = 0;
	rSrc.w = 32;
	rSrc.h = 32;

	rDst.x = x;
	rDst.y = y;
	rDst.w = 32;
	rDst.h = 32;
	//SDL_QueryTexture(pTex, NULL, NULL, &rDst.w, &rDst.h);
	SDL_RenderCopy(gVars.pRen, pTex, &rSrc, &rDst);
//	SDL_RenderCopy(gVars.pRen, pTex, NULL, NULL);
}

void drawTetros(game_t *game) {
	int i;
int j = 6;
	for (i = 0; i < NBLOCKS; i++) {
		int x = 500 + (SZBLOCK * gTetros[j][i].x);
		int y = 500 + (SZBLOCK * gTetros[j][i].y);
		renderRexture(gVars.pTetsImg, x, y);
	}
}

void renderFlip(void) {
	// draw on the screen
	frameWait();
}


// intro

Sint32 menuIntroInit(void *pArgs) {
	SDL_SetRenderDrawBlendMode(gVars.pRen, SDL_BLENDMODE_NONE);
	SDL_SetTextureBlendMode(gVars.pIntroImg, SDL_BLENDMODE_BLEND);
	(void)pArgs;
	return 0;
}

Sint32 menuIntroMain(void *pArgs) {
	static int i = SDL_ALPHA_TRANSPARENT;
	
	SDL_SetRenderDrawColor(gVars.pRen, 0xff, 0xff, 0xff, 0xff);
	SDL_RenderClear(gVars.pRen);

	if (SDL_SetTextureAlphaMod(gVars.pIntroImg, i) < 0)
		puts("marche pas..");
	SDL_RenderCopy(gVars.pRen, gVars.pIntroImg, NULL, NULL);
	SDL_RenderPresent(gVars.pRen);
	frameWait();
	i += 3;
	if (i > SDL_ALPHA_OPAQUE)
		i = SDL_ALPHA_OPAQUE;
	(void)pArgs;
	return 0;
}

Sint32 menuIntroRelease(void *pArgs) {
	(void)pArgs;
	return 0;
}










int		eventHandler(void) {
	SDL_Event ev;

	while (SDL_PollEvent(&ev)) {
		if (ev.type == SDL_QUIT)
			return 1;
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
	menu_e nState;
	int nLoop;

	nState = MENU_INTRO;
	nLoop = 1;
	while (nLoop) {
		switch (nState) {
			case MENU_INTRO:
				nState = menuLoop(menuIntroInit, menuIntroMain, menuIntroRelease, NULL);
				break;

			case MENU_MAIN:
				break;

			case MENU_OPTS:
				break;

			case MENU_HISCORES:
				break;

			case MENU_GAME:
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
