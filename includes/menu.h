#ifndef MENU_H
#define MENU_H

#include "SDL.h"
#include "frame.h"

/* ********************************* */
/* *          Constantes           * */
/* ********************************* */

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
	Uint32 select;
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

#endif
