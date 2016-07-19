#include "SDL.h"
#include "tetris.h"
#include "score.h"
#include "menu.h"
#include "game.h"
#include "font.h"

struct gOpts_s gOpts;

void menuOptsDefault(void) {
	gOpts.nSfxSound = 1;
	gOpts.nSfxMusic = 1;
	gOpts.nLevelStart = 1;
	gOpts.nGhost = 1;
}

Sint32 menuOptsInit(void *pArgs) {
	menu_t *this = pArgs;

	eventClear();

	SDL_SetRenderDrawColor(gVars.pRen, 0xAB, 0xCD, 0xEF, 0x00);
	bzero(this, sizeof(*this));
	bzero(gVars.nKeyb, sizeof gVars.nKeyb);

	this->nSizeMenu = 5;
//	menuOptsDefault();

	return 0;
}

Sint32 menuOptsRelease(void *pArgs) {
	menu_t *this = pArgs;

	(void)this;
	return 0;
}

void menuOptsDraw(void *pArgs) {
	menu_t *this = pArgs;
	int i;

	SDL_RenderCopy(gVars.pRen, gVars.pTetrisLogo, NULL, NULL);

	for (i = 0; i < this->nSizeMenu; i++) {
	}
}

void changeValue(menu_t *this) {
	Sint32 nInc = 1;
	Sint32 *pVal;
	Sint32 min, max;

	if (gVars.nKeyb[KEY_LEFT] != KEY_NONE)
		nInc = -1;

	switch (this->nSelect) {
		case 0:
			pVal = (Sint32*) &gOpts.nSfxSound;
			min = 0;
			max = 1;
			break;
		case 1:
			pVal = (Sint32*) &gOpts.nSfxMusic;
			min = 0;
			max = 3;
			break;
		case 2:
			pVal = (Sint32*) &gOpts.nLevelStart;
			min = 1;
			max = MAX_LEVEL;
			break;
		case 3:
			pVal = (Sint32*) &gOpts.nGhost;
			min = 0;
			max = 1;
			break;
		default:
			return;
			break;
	}
	*pVal += nInc;
	if (*pVal < min)
		*pVal = max;
	else if (*pVal > max)
		*pVal = min;
}

Sint32 menuOptsEvents(void *pArgs) {
	menu_t *this = pArgs;
	int i;

	(void)this;

	/* Delay de repetition sur les touches */
	for (i = 0; i < KEY_LAST; i++) {
		if (gVars.nKeyb[i] > KEY_DELAY)
			gVars.nKeyb[i]--;
	}

	if (gVars.nKeyb[KEY_UP] >= KEY_DELAY && gVars.nKeyb[KEY_DOWN] >= KEY_DELAY)
		return -1;
	if (gVars.nKeyb[KEY_LEFT] >= KEY_DELAY && gVars.nKeyb[KEY_RIGHT] >= KEY_DELAY)
		return -1;

	if (gVars.nKeyb[KEY_UP] == KEY_PRESSED || gVars.nKeyb[KEY_UP] == KEY_DELAY) {
		this->nSelect--;
		gVars.nKeyb[KEY_UP] = KEY_MAX_DELAY;
	}
	if (gVars.nKeyb[KEY_DOWN] == KEY_PRESSED || gVars.nKeyb[KEY_DOWN] == KEY_DELAY) {
		this->nSelect++;
		gVars.nKeyb[KEY_DOWN] = KEY_MAX_DELAY;
	}

	if (gVars.nKeyb[KEY_LEFT] == KEY_PRESSED || gVars.nKeyb[KEY_LEFT] == KEY_DELAY) {
		changeValue(this);
		gVars.nKeyb[KEY_LEFT] = KEY_MAX_DELAY;
	}
	if (gVars.nKeyb[KEY_RIGHT] == KEY_PRESSED || gVars.nKeyb[KEY_RIGHT] == KEY_DELAY) {
		changeValue(this);
		gVars.nKeyb[KEY_RIGHT] = KEY_MAX_DELAY;
	}

	if (this->nSelect < 0)
		this->nSelect = this->nSizeMenu - 1;
	else if (this->nSelect >= this->nSizeMenu)
		this->nSelect = 0;

	if (gVars.nKeyb[KEY_SPACE] && this->nSelect == this->nSizeMenu - 1)
		return 0;

	return -1;
}

Sint32 menuOptsMain(void *pArgs) {
	menu_t *this = pArgs;
	char s[128] = "";
	Sint32 i;

	char *pNameOpts[] = {
		"Sound FX",
		"Music",
		"Level start",
		"Ghost piece",
		"Quit"
	};
	char *pValOptsMusic[64] = {
		"off",
		"typea",
		"typeb",
		"typec"
	};

	// on / off
	// off - typea - typeb - typec
	// 1 - MAX_LEVEL
	// on / off

	(void)this;

	SDL_RenderFillRect(gVars.pRen, NULL);

	printText("->", 30, FONT_COL_BLUE_BLUE, 40, 100 + 50 * this->nSelect);
	for (i = 0; i < this->nSizeMenu; i++) {
		sprintf(s, "%-15s", pNameOpts[i]);
		printText(s, 30, FONT_COL_WHITE_RED, 100, 100 + 50 * i);
		switch (i) {
			case 0:
				strcpy(s, gOpts.nSfxSound ? "on" : "off");
				break;
			case 1:
				strcpy(s, pValOptsMusic[gOpts.nSfxMusic]);
				break;
			case 2:
				sprintf(s, "%u", gOpts.nLevelStart);
				break;
			case 3:
				strcpy(s, gOpts.nGhost ? "on" : "off");
				break;
			default:
				s[0] = '\0';
				break;
		}
		printText(s, 30, FONT_COL_WHITE_BLUE, 650, 100 + 50 * i);
	}

	if (menuOptsEvents(pArgs) >= 0)
		return MENU_MAIN;

	return MENU_NULL;
}
