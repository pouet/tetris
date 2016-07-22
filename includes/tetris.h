#ifndef TETRIS_H
#define TETRIS_H

#include <SDL.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "score.h"

/* ********************************* */
/* *          Constantes           * */
/* ********************************* */

#define TITLE "Tetris"

#define SURFACE_TRANSPARENT_COLOR 0x00FFFFFF

enum {
	SDL_FLAGS = SDL_INIT_VIDEO,
	FPS = 60,
	FPS_DFLT = 1000 / FPS,
	FPS_1S = 1000
};

enum {
	WIN_W = 1024,
	WIN_H = 768
};

typedef enum {
	MENU_NULL,
	MENU_INTRO,
	MENU_MAIN,
	MENU_OPTS,
	MENU_HISCORES,
	MENU_GAMEOVER,
	MENU_GAME,
	MENU_HELP,
	MENU_CREDITS,
	MENU_QUIT,
	MENU_MAX
} menu_e;

enum {
	KEY_UP,
	KEY_DOWN,
	KEY_LEFT,
	KEY_RIGHT,
	KEY_SPACE,
	KEY_P,
	KEY_C,
	KEY_LAST
};

enum {
	KEY_NONE = 0,
	KEY_PRESSED = 1,
	KEY_DELAY = 2,
	KEY_MAX_DELAY = 10
};

typedef Sint32 (*pFct)(void *);

/* ********************************* */
/* *          Structures           * */
/* ********************************* */

struct gVars_s {
	SDL_Window		*pWin;
	SDL_Renderer	*pRen;
	Uint32			nScrW;
	Uint32			nScrH;
	Sint32			nKeyb[KEY_LAST];
	const Uint8		*pKeyb;

	SDL_Texture		*pTetsImg;
	SDL_Texture		*pFont;
	SDL_Texture		*pIntroImg;
	SDL_Texture		*pBackground;

	score_t			sScore;
};

struct gOpts_s {
	Uint32 nSfxSound;
	Uint32 nSfxMusic;
	Uint32 nLevelStart;
	Uint32 nGhost;
};

extern struct gOpts_s gOpts;

/* ********************************* */
/* *           Globales            * */
/* ********************************* */

extern struct gVars_s gVars;

/* ********************************* */
/* *          Prototypes           * */
/* ********************************* */

int	init(void);
int initVideo(void);
int	initGVars(void);
void quit(void);
void quitVideo(void);

int	eventHandler(void);
void eventClear(void);

/* fonction generique qui gere tous les etats du jeu */
menu_e menuLoop(pFct pInit, pFct pMain, pFct pRelease, void *pArgs);
int mainLoop(void);

SDL_Texture *loadBMP(char *s);

void renderFlip(void);
void blitTexture(SDL_Texture *pTex, int x, int y, SDL_Rect *rClip);
void eventClear(void);

#endif
