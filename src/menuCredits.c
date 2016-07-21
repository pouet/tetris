#include <SDL.h>
#include "tetris.h"
#include "score.h"
#include "menu.h"
#include "font.h"
#include "sfx.h"

Sint32 menuCreditsInit(void *pArgs) {
	menu_t *this = pArgs;

	(void)this;
	eventClear();

	return 0;
}

Sint32 menuCreditsRelease(void *pArgs) {
	menu_t *this = pArgs;

	(void)this;
	sfxPlaySound(SFX_PLAY_ROTATE, SFX_REPEAT_OFF);
	return 0;
}

Sint32 menuCreditsEvents(void *pArgs) {
	menu_t *this = pArgs;

	(void)this;

	if (gVars.nKeyb[KEY_SPACE]) {
		gVars.nKeyb[KEY_SPACE] = KEY_NONE;
		return 0;
	}

	return -1;
}

Sint32 menuCreditsMain(void *pArgs) {
	menu_t *this = pArgs;
	Uint32 i;
	struct {
		char *s;
		Uint32 nCol;
	} pTab[] = {
		{ "programer", FONT_COL_WHITE_RED },
		{ "pouet", FONT_COL_BLUE_BLUE },
		{ "", FONT_COL_WHITE_RED },
		{ "", FONT_COL_WHITE_RED },
		{ "sprites", FONT_COL_WHITE_RED },
		{ "pouet", FONT_COL_BLUE_BLUE },
		{ "jdaster64", FONT_COL_BLUE_BLUE },
		{ "viiper", FONT_COL_BLUE_BLUE },
		{ "beam luinsir", FONT_COL_BLUE_BLUE },
		{ "and other...", FONT_COL_BLUE_BLUE },
		{ "", FONT_COL_WHITE_RED },
		{ "", FONT_COL_WHITE_RED },
		{ "", FONT_COL_WHITE_RED },
		{ "thanks to", FONT_COL_WHITE_RED },
		{ "joe78", FONT_COL_BLUE_BLUE },
		{ "GurneyH", FONT_COL_BLUE_BLUE },
	};

	(void)this;

	blitTexture(gVars.pBackground, 0, 0, NULL);

	for (i = 0; i < sizeof pTab / sizeof pTab[0]; i++) {
		printText(pTab[i].s, MENU_FONT_SIZE,
				pTab[i].nCol, MENU_OFFX + 10, MENU_OFFY + 30 * i);
	}

	if (menuCreditsEvents(pArgs) >= 0)
		return MENU_MAIN;

	return MENU_NULL;
}
