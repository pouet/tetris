#include <SDL.h>
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

	memset(this, 0, sizeof *this);
	sfxPlaySound(SFX_PLAY_TYPEA + gOpts.nSfxMusic - 1, SFX_REPEAT_ON);

	this->nSizeMenu = 4;

	return 0;
}

Sint32 menuOptsRelease(void *pArgs) {
	menu_t *this = pArgs;

	(void)this;
	sfxPlaySound(SFX_PLAY_ROTATE, SFX_REPEAT_OFF);
	return 0;
}

static void changeValue(menu_t *this) {
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
	if ((Uint32 *)pVal == &gOpts.nSfxMusic) {
		sfxStopAllAudio();
		if (gOpts.nSfxMusic)
			sfxPlaySound(SFX_PLAY_TYPEA + gOpts.nSfxMusic - 1, SFX_REPEAT_ON);
	}
}

static Sint32 menuOptsEvents(void *pArgs) {
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
	else if (gVars.nKeyb[KEY_C])
		return 1;

	return -1;
}

Sint32 menuOptsMain(void *pArgs) {
	menu_t *this = pArgs;
	char s[128] = "";
	Sint32 i, nEv;
	Sint32 nRet = MENU_NULL;

	char *pNameOpts[] = {
		"Sound",
		"Music",
		"Level",
		"Ghost",
		""
	};
	char *pValOptsMusic[] = {
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

	nEv = menuOptsEvents(pArgs);
	if (nEv == 0)
		nRet = MENU_GAME;
	else if (nEv == 1)
		nRet = MENU_MAIN;

	blitTexture(gVars.pBackground, 0, 0, NULL);

	printText(">", MENU_FONT_SIZE, FONT_COL_BLUE_BLUE,
			MENU_OFFX, MENU_OFFY + 50 * this->nSelect);
	printText("<", MENU_FONT_SIZE, FONT_COL_GREEN_GREEN,
			MENU_OFFX + 150, MENU_OFFY + 50 * this->nSelect);
	printText(">", MENU_FONT_SIZE, FONT_COL_GREEN_GREEN,
			MENU_OFFX + 280, MENU_OFFY + 50 * this->nSelect);

	for (i = 0; i < this->nSizeMenu; i++) {
		sprintf(s, "%-15s", pNameOpts[i]);
		printText(s, MENU_FONT_SIZE, FONT_COL_WHITE_RED, MENU_OFFX + 30, MENU_OFFY + 50 * i);
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
		printText(s, MENU_FONT_SIZE, FONT_COL_WHITE_BLUE,
				MENU_OFFX + 148 + 25, MENU_OFFY + 50 * i);
	}
	printText("Press SPACE", MENU_FONT_SIZE, FONT_COL_WHITE_RED, MENU_OFFX + 25, 600);
	printText("to start", MENU_FONT_SIZE, FONT_COL_WHITE_RED, MENU_OFFX + 60, 630);

	if (nRet != MENU_NULL && nRet != MENU_GAME)
		sfxStopAllAudio();
	return nRet;
}
