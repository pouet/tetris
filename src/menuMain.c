#include "SDL.h"
#include "tetris.h"
#include "frame.h"
#include "menu.h"
#include "font.h"

Sint32 menuMainInit(void *pArgs) {
	menu_t *this = pArgs;
	struct {
		char *pName;
		Uint32 nVal;
	} pTab[] = {
		{ "Play", MENU_GAME },
		{ "High scores", MENU_HISCORES },
		{ "Options", MENU_OPTS },
		{ "Quit", MENU_QUIT },
	};
	int nSize = sizeof pTab / sizeof *pTab;
	int i;

	SDL_SetRenderDrawColor(gVars.pRen, 0x00, 0x00, 0xFF, 0x00);
	bzero(this, sizeof(*this));

	this->nSizeMenu = nSize;
	this->pTex = malloc(nSize * sizeof *this->pTex);
	this->pnVal = malloc(nSize * sizeof *this->pnVal);
	for (i = 0; i < nSize; i++) {
		this->pTex[i] = createFont(pTab[i].pName, 0);
		this->pnVal[i] = pTab[i].nVal;
	}
	this->nOffIncr = 2;

	return 0;
}

Sint32 menuMainEvents(void *pArgs) {
	menu_t *this = pArgs;

	if (this->nDelay <= 0) {
		if (gVars.pKeyb[SDL_SCANCODE_UP]) {
			this->nSelect--;
			this->nDelay = 10;
		}
		else if (gVars.pKeyb[SDL_SCANCODE_DOWN]) {
			this->nSelect++;
			this->nDelay = 10;
		}
		if (this->nSelect < 0)
			this->nSelect = this->nSizeMenu - 1;
		else if (this->nSelect >= this->nSizeMenu)
			this->nSelect = 0;
	}
	else if (this->nDelay > 0)
		this->nDelay--;
	if (gVars.pKeyb[SDL_SCANCODE_RETURN])
		return 0;

	return -1;
}

void menuMainDraw(void *pArgs) {
	menu_t *this = pArgs;
	int i;

	SDL_RenderCopy(gVars.pRen, gVars.pTetrisLogo, NULL, NULL);

	for (i = 0; i < this->nSizeMenu; i++) {
		if (i == this->nSelect) {
			blitTexture(this->pTex[i], 10 + this->nOffSelect, 10 + i * 42, NULL);
			this->nOffSelect = this->nOffSelect + this->nOffIncr;
			if (this->nOffSelect < -64 || this->nOffSelect > 64)
				this->nOffIncr *= -1;
		}
		else
			blitTexture(this->pTex[i], 10, 10 + i * 42, NULL);
	}
}

Sint32 menuMainMain(void *pArgs) {
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
*/

	if (menuMainEvents(pArgs) >= 0)
		return this->pnVal[this->nSelect];
	menuMainDraw(pArgs);

	return MENU_NULL;
}

Sint32 menuMainRelease(void *pArgs) {
	menu_t *this = pArgs;
	int i;

	for (i = 0; i < this->nSizeMenu; i++)
		SDL_DestroyTexture(this->pTex[i]);
	free(this->pTex);
	free(this->pnVal);
	return 0;
}
