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

	eventClear();

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
	int i;

	/* Delay de repetition sur les touches */
	for (i = 0; i < KEY_LAST; i++) {
		if (gVars.nKeyb[i] > KEY_DELAY)
			gVars.nKeyb[i]--;
	}

	if (gVars.nKeyb[KEY_UP] >= KEY_DELAY && gVars.nKeyb[KEY_DOWN] >= KEY_DELAY)
		return -1;

	if (gVars.nKeyb[KEY_UP] == KEY_PRESSED || gVars.nKeyb[KEY_UP] == KEY_DELAY) {
		this->nSelect--;
		gVars.nKeyb[KEY_UP] = KEY_MAX_DELAY;
	}
	if (gVars.nKeyb[KEY_DOWN] == KEY_PRESSED || gVars.nKeyb[KEY_DOWN] == KEY_DELAY) {
		this->nSelect++;
		gVars.nKeyb[KEY_DOWN] = KEY_MAX_DELAY;
	}
	if (this->nSelect < 0)
		this->nSelect = this->nSizeMenu - 1;
	else if (this->nSelect >= this->nSizeMenu)
		this->nSelect = 0;

	if (gVars.nKeyb[KEY_SPACE])
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
