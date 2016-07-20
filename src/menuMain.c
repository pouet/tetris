#include "SDL.h"
#include "tetris.h"
#include "frame.h"
#include "menu.h"
#include "font.h"
#include "sfx.h"

Sint32 menuMainInit(void *pArgs) {
	menu_t *this = pArgs;
	struct {
		char *pName;
		Uint32 nVal;
	} pTab[] = {
		{ "Play", MENU_OPTS },
		{ "High scores", MENU_HISCORES },
	};
	int nSize = sizeof pTab / sizeof *pTab;
	int i;

	eventClear();

	bzero(this, sizeof(*this));

	this->nSizeMenu = nSize;
	this->pnVal = malloc(nSize * sizeof *this->pnVal);
	for (i = 0; i < nSize; i++)
		this->pnVal[i] = pTab[i].nVal;

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
		sfxPlaySound(SFX_PLAY_MOVE, SFX_REPEAT_OFF);
	}
	if (gVars.nKeyb[KEY_DOWN] == KEY_PRESSED || gVars.nKeyb[KEY_DOWN] == KEY_DELAY) {
		this->nSelect++;
		gVars.nKeyb[KEY_DOWN] = KEY_MAX_DELAY;
		sfxPlaySound(SFX_PLAY_MOVE, SFX_REPEAT_OFF);
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
	char *pName[] = {
		"Play",
		"High scores",
		NULL
	};
	int i;
	Uint32 nColor;

	blitTexture(gVars.pBackground, 0, 0, NULL);

	printText(">", MENU_FONT_SIZE, FONT_COL_BLUE_BLUE, MENU_OFFX, MENU_OFFY + this->nSelect * 30);
	for (i = 0; i < this->nSizeMenu; i++) {
		if (i == this->nSelect)
			nColor = FONT_COL_WHITE_RED;
		else
			nColor = FONT_COL_WHITE_BLUE;
		printText(pName[i], MENU_FONT_SIZE, nColor,
				MENU_OFFX + 30, MENU_OFFY + i * 30);
	}
}

Sint32 menuMainMain(void *pArgs) {
	menu_t *this = pArgs;
	Sint32 nRet = MENU_NULL;

	if (menuMainEvents(pArgs) >= 0)
		nRet = this->pnVal[this->nSelect];
	menuMainDraw(pArgs);

	return nRet;
}

Sint32 menuMainRelease(void *pArgs) {
	menu_t *this = pArgs;

	free(this->pnVal);
	sfxPlaySound(SFX_PLAY_ROTATE, SFX_REPEAT_OFF);
	return 0;
}
