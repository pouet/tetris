#include "SDL.h"
#include "tetris.h"
#include "score.h"
#include "menu.h"
#include "game.h"
#include "font.h"
#include "sfx.h"

struct gOpts_s gOpts;

void menuOptsDefault(void) {
	gOpts.nSfxSound = 1;
	gOpts.nSfxMusic = 1;
	gOpts.nLevelStart = 1;
	gOpts.nGhost = 1;
}

Sint32 menuOptsInit(void *pArgs) {
	menu_t *this = pArgs;

	menuOptsDefault();
	eventClear();

	bzero(this, sizeof(*this));

	this->nSizeMenu = 4;

	return 0;
}

Sint32 menuOptsRelease(void *pArgs) {
	menu_t *this = pArgs;

	(void)this;
	return 0;
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
		sfxPlaySound(SFX_PLAY_MOVE, SFX_REPEAT_OFF);
	}
	if (gVars.nKeyb[KEY_DOWN] == KEY_PRESSED || gVars.nKeyb[KEY_DOWN] == KEY_DELAY) {
		this->nSelect++;
		gVars.nKeyb[KEY_DOWN] = KEY_MAX_DELAY;
		sfxPlaySound(SFX_PLAY_MOVE, SFX_REPEAT_OFF);
	}

	if (gVars.nKeyb[KEY_LEFT] == KEY_PRESSED || gVars.nKeyb[KEY_LEFT] == KEY_DELAY) {
		changeValue(this);
		gVars.nKeyb[KEY_LEFT] = KEY_MAX_DELAY;
		sfxPlaySound(SFX_PLAY_MOVE, SFX_REPEAT_OFF);
	}
	if (gVars.nKeyb[KEY_RIGHT] == KEY_PRESSED || gVars.nKeyb[KEY_RIGHT] == KEY_DELAY) {
		changeValue(this);
		gVars.nKeyb[KEY_RIGHT] = KEY_MAX_DELAY;
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

#define MENU_OFFX 360
#define MENU_OFFY 100

Sint32 menuOptsMain(void *pArgs) {
	menu_t *this = pArgs;
	char s[128] = "";
	Sint32 i;
	Sint32 nRet = MENU_NULL;

	char *pNameOpts[] = {
		"Sound",
		"Music",
		"Level",
		"Ghost"
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

	if (menuOptsEvents(pArgs) >= 0)
		nRet = MENU_GAME;

	blitTexture(gVars.pBackground, 0, 0, NULL);

	printText("->", 20, FONT_COL_BLUE_BLUE, MENU_OFFX, MENU_OFFY + 50 * this->nSelect);
	for (i = 0; i < this->nSizeMenu; i++) {
		sprintf(s, "%-15s", pNameOpts[i]);
		printText(s, 20, FONT_COL_WHITE_RED, MENU_OFFX + 50, MENU_OFFY + 50 * i);
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
		printText(s, 20, FONT_COL_WHITE_BLUE, MENU_OFFX + 180, MENU_OFFY + 50 * i);
	}
	printText("Press SPACE", 20, FONT_COL_WHITE_RED, MENU_OFFX + 45, 600);
	printText("to start", 20, FONT_COL_WHITE_RED, MENU_OFFX + 80, 630);

	return nRet;
}
