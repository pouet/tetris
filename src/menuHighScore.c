#include <SDL.h>
#include "tetris.h"
#include "score.h"
#include "menu.h"
#include "font.h"
#include "sfx.h"

Sint32 menuHighScoreInit(void *pArgs) {
	menu_t *this = pArgs;

	eventClear();

	bzero(this, sizeof(*this));

	return 0;
}

Sint32 menuHighScoreRelease(void *pArgs) {
	menu_t *this = pArgs;

	(void)this;
	sfxPlaySound(SFX_PLAY_ROTATE, SFX_REPEAT_OFF);
	return 0;
}

Sint32 menuHighScoreEvents(void *pArgs) {
	menu_t *this = pArgs;

	(void)this;

	if (gVars.nKeyb[KEY_SPACE]) {
		gVars.nKeyb[KEY_SPACE] = KEY_NONE;
		return 0;
	}

	return -1;
}

Sint32 menuHighScoreMain(void *pArgs) {
	menu_t *this = pArgs;
	char s[64] = "";
	Sint32 i;

	(void)this;

	blitTexture(gVars.pBackground, 0, 0, NULL);

	for (i = 0; i < NB_SCORE; i++) {
		if (gVars.sScore.pPlayer[i].nScore == 0)
			break;

		sprintf(s, "%-6.6s %u",
				gVars.sScore.pPlayer[i].pName, gVars.sScore.pPlayer[i].nScore);

		strncpy(s, gVars.sScore.pPlayer[i].pName, NAME_LEN);
		s[NAME_LEN] = '\0';
		printText(s, MENU_FONT_SIZE, FONT_COL_BLUE_BLUE, MENU_OFFX + 10, MENU_OFFY + 30 * i);

		sprintf(s, "%.6u", gVars.sScore.pPlayer[i].nScore);
		printText(s, MENU_FONT_SIZE, FONT_COL_CYAN_BLUE, MENU_OFFX + 160, MENU_OFFY + 30 * i);
	}
	if (i == 0)
		printText("no high score", MENU_FONT_SIZE, FONT_COL_CYAN_BLUE, MENU_OFFX + 10, MENU_OFFY);

	if (menuHighScoreEvents(pArgs) >= 0)
		return MENU_MAIN;

	return MENU_NULL;
}
