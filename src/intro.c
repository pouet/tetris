#include "SDL.h"
#include "tetris.h"
#include "frame.h"
#include "menu.h"

Sint32 menuIntroInit(void *pArgs) {
	intro_t *this = pArgs;

	eventClear();

	bzero(this, sizeof(*this));
	this->nFade = SDL_ALPHA_TRANSPARENT;
	this->state = INTRO_FADEIN;
	this->ticks = 0;

	SDL_SetRenderDrawColor(gVars.pRen, 0xff, 0xff, 0xff, 0x00);

	return 0;
}

Sint32 menuIntroMain(void *pArgs) {
	intro_t *this = pArgs;

	if (gVars.nKeyb[KEY_SPACE])
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

	SDL_SetTextureAlphaMod(gVars.pIntroImg, this->nFade);
	SDL_RenderCopy(gVars.pRen, gVars.pIntroImg, NULL, NULL);

	return MENU_NULL;
}

Sint32 menuIntroRelease(void *pArgs) {
	intro_t *this = pArgs;

	(void)this;

	return 0;
}
