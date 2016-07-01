#include "SDL.h"
#include "tetris.h"
#include "frame.h"
#include "menu.h"

struct gVars_s gVars;

Sint32 menuIntroInit(void *pArgs) {
	intro_t *this = pArgs;

	bzero(this, sizeof(*this));
	this->nFade = SDL_ALPHA_TRANSPARENT;
	this->state = INTRO_FADEIN;
	this->ticks = 0;

	return 0;
}

Sint32 menuIntroMain(void *pArgs) {
	intro_t *this = pArgs;

	if (gVars.pKeyb[SDL_SCANCODE_SPACE])
		return MENU_MAIN;

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
				return MENU_MAIN;
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

	return MENU_NULL;
}

Sint32 menuIntroRelease(void *pArgs) {
	intro_t *this = pArgs;

	(void)this;

	return 0;
}
