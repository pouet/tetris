#include <SDL.h>
#include "tetris.h"
#include "game.h"
#include "score.h"
#include "menu.h"
#include "font.h"
#include "sfx.h"

#define NAME_LETTERS " ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-"

Sint32 gameOverInit(void *pArgs) {
	game_t *this = pArgs;

	eventClear();
	this->nHigh = isHighScore(this->nScore);

	return 0;
}

Sint32 gameOverRelease(void *pArgs) {
	game_t *this = pArgs;
	int i;

	sfxPlaySound(SFX_PLAY_ROTATE, SFX_REPEAT_OFF);
	if (this->nHigh >= 0) {
		for (i = 0; i < NAME_LEN; i++)
			this->pName[i] = NAME_LETTERS[(Uint8)this->pName[i]];
		scoreAdd(this->nHigh, this->nScore, this->pName);
	}
	return 0;
}

static Sint32 gameOverEvents(void *pArgs) {
	Sint32 nLenLetters = strlen(NAME_LETTERS);
	game_t *this = pArgs;
	int i;

	(void)this;

	/* Pas de high score */
	if (this->nHigh < 0) {
		if (gVars.nKeyb[KEY_SPACE] == KEY_PRESSED)
			return 0;
		return -1;
	}

	/* Delay de repetition sur les touches */
	for (i = 0; i < KEY_LAST; i++) {
		if (gVars.nKeyb[i] > KEY_DELAY)
			gVars.nKeyb[i]--;
	}

	if (gVars.nKeyb[KEY_UP] == KEY_PRESSED || gVars.nKeyb[KEY_UP] == KEY_DELAY) {
		this->pName[this->nPos]++;
		if (this->pName[this->nPos] >= nLenLetters)
			this->pName[this->nPos] = 0;
		gVars.nKeyb[KEY_UP] = KEY_MAX_DELAY;
	}
	if (gVars.nKeyb[KEY_DOWN] == KEY_PRESSED || gVars.nKeyb[KEY_DOWN] == KEY_DELAY) {
		this->pName[this->nPos]--;
		if (this->pName[this->nPos] < 0)
			this->pName[this->nPos] = nLenLetters - 1;
		gVars.nKeyb[KEY_DOWN] = KEY_MAX_DELAY;
	}
	if (gVars.nKeyb[KEY_SPACE]) {
		this->nPos++;
		gVars.nKeyb[KEY_SPACE] = KEY_NONE;
	}
	if (gVars.nKeyb[KEY_LEFT]) {
		if (this->nPos > 0)
			this->nPos--;
		gVars.nKeyb[KEY_LEFT] = KEY_NONE;
	}
	if (gVars.nKeyb[KEY_RIGHT]) {
		if (this->nPos < NAME_LEN - 1)
			this->nPos++;
		gVars.nKeyb[KEY_RIGHT] = KEY_NONE;
	}

	if (this->nPos >= NAME_LEN)
		return 0;

	return -1;
}

static void gameOverDraw(game_t *this) {
	char s[NAME_LEN + 1] = "";
	int i;

	blitTexture(gVars.pBackground, 0, 0, NULL);

	if (this->nHigh >= 0) {
		printText("new high score", MENU_FONT_SIZE, FONT_COL_WHITE_RED, MENU_OFFX, MENU_OFFY);
		for (i = 0; i < NAME_LEN; i++)
			s[i] = NAME_LETTERS[(Uint8)this->pName[i]];
		printText("name:", MENU_FONT_SIZE, FONT_COL_BLUE_BLUE, MENU_OFFX, MENU_OFFY + 60);
		printText(s, MENU_FONT_SIZE, FONT_COL_CYAN_BLUE, MENU_OFFX + 110, MENU_OFFY + 60);
		printText("-", MENU_FONT_SIZE, FONT_COL_CYAN_BLUE, MENU_OFFX + 110 + this->nPos * MENU_FONT_SIZE, MENU_OFFY + 80);
	}
	else {
		printText("! game over !", 24, FONT_COL_BLUE_BLUE, PLAYGRID_OFFX, (32 * GRID_HT) / 2);
	}
}

Sint32 gameOverMain(void *pArgs) {
	game_t *this = pArgs;
	Sint32 nRet = MENU_NULL;

	if (gameOverEvents(pArgs) >= 0)
		nRet = MENU_MAIN;

	gameOverDraw(this);

	return nRet;
}
