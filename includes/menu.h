#ifndef MENU_H
#define MENU_H

#include "SDL.h"
#include "frame.h"

/* ********************************* */
/* *          Constantes           * */
/* ********************************* */

enum {
	MENU_OFFX = 365,
	MENU_OFFY = 100,
	MENU_FONT_SIZE = 21
};

enum {
	FADE_INC = 3,
	WAIT_1S = FPS
};

enum {
	INTRO_FADEIN,
	INTRO_FADEOUT,
	INTRO_WAIT
};

/* ********************************* */
/* *          Structures           * */
/* ********************************* */

typedef struct intro_s {
	Uint32 state;
	Sint32 nFade;
	Uint32 ticks;
} intro_t;

typedef struct menu_s {
	Uint32 state;
	Sint32 nSelect;
	Sint32 nDelay;

	/* anim gauche droite */
	Sint32 nOffSelect;
	Sint32 nOffIncr;

	SDL_Texture **pTex;
	Sint32 *pnVal;
	Sint32 nSizeMenu;
} menu_t;

/* ********************************* */
/* *          Prototypes           * */
/* ********************************* */

Sint32 menuIntroInit(void *pArgs);
Sint32 menuIntroMain(void *pArgs);
Sint32 menuIntroRelease(void *pArgs);

Sint32 menuMainInit(void *pArgs);
Sint32 menuMainMain(void *pArgs);
Sint32 menuMainRelease(void *pArgs);

Sint32 menuHighScoreInit(void *pArgs);
Sint32 menuHighScoreMain(void *pArgs);
Sint32 menuHighScoreRelease(void *pArgs);

Sint32 menuOptsInit(void *pArgs);
Sint32 menuOptsMain(void *pArgs);
Sint32 menuOptsRelease(void *pArgs);

Sint32 menuHelpInit(void *pArgs);
Sint32 menuHelpMain(void *pArgs);
Sint32 menuHelpRelease(void *pArgs);

void menuOptsDefault(void);

#endif
