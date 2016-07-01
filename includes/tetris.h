#ifndef TETRIS_H
#define TETRIS_H

#include "SDL.h"
 
/* ********************************* */
/* *          Constantes           * */
/* ********************************* */

#define TITLE "Tetris"

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

enum {
	NGRIDX = 10,
	NGRIDY = 22,
	NBLOCKS = 4,
	SZBLOCK = 32
};

enum {
	TET_I,
	TET_O,
	TET_T,
	TET_S,
	TET_Z,
	TET_J,
	TET_L,
	NTETS
};

typedef enum {
	MENU_NULL,
	MENU_INTRO,
	MENU_MAIN,
	MENU_OPTS,
	MENU_HISCORES,
	MENU_GAME,
	MENU_QUIT
} menu_e;

typedef Sint32 (*pFct)(void *);
 
/* ********************************* */
/* *          Structures           * */
/* ********************************* */

struct gVars_s {
	SDL_Window		*pWin;
	SDL_Renderer	*pRen;
	Uint32			nScrW;
	Uint32			nScrH;
	const Uint8		*pKeyb;

	SDL_Texture		*pTetsImg;
	SDL_Texture		*pIntroImg;
	SDL_Texture		*pTetrisLogo;
};

typedef struct point_s {
	Uint32 x;
	Uint32 y;
} point_t;

typedef struct game_s {
} game_t;

/* ********************************* */
/* *           Globales            * */
/* ********************************* */
 
extern struct gVars_s gVars;

/* ********************************* */
/* *          Prototypes           * */
/* ********************************* */

void renderFlip(void);

#endif
