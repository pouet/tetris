#include "SDL.h"
#include "tetris.h"
#include "frame.h"
#include "menu.h"

struct gVars_s gVars;

Sint32 menuMainInit(void *pArgs) {
	menu_t *this = pArgs;

	bzero(this, sizeof(*this));
//	this->nFade = SDL_ALPHA_TRANSPARENT;
//	this->state = INTRO_FADEIN;
//	this->ticks = 0;

	return 0;
}

Sint32 menuMainMain(void *pArgs) {
	static char tMenuName[] = {
		"Play",
		"High scores",
		"Options",
		"Quit"
	};
	menu_t *this = pArgs;

	/*
	switch (this->state) {
		case INTRO_FADEIN:
			this->nFade += FADE_INC;
			if (this->nFade > SDL_ALPHA_OPAQUE) {
				this->nFade = SDL_ALPHA_OPAQUE;
				this->state = INTRO_WAIT;
			}
			break;
		case INTRO_FADEOUT:
			this->nFade -= FADE_INC;
			if (this->nFade < SDL_ALPHA_TRANSPARENT)
				return MENU_QUIT;
			break;
		case INTRO_WAIT:
			this->ticks++;
			if (this->ticks > WAIT_1S)
				this->state = INTRO_FADEOUT;
			break;
		default:
			return MENU_QUIT;
	}

	SDL_RenderClear(gVars.pRen);
	SDL_SetTextureAlphaMod(gVars.pIntroImg, this->nFade);
	SDL_RenderCopy(gVars.pRen, gVars.pIntroImg, NULL, NULL);
*/

	SDL_RenderClear(gVars.pRen);
	SDL_RenderCopy(gVars.pRen, gVars.pTetrisLogo, NULL, NULL);

	return MENU_NULL;
}

Sint32 menuMainRelease(void *pArgs) {
	menu_t *this = pArgs;

	(void)this;

	return 0;
}
