#include "SDL.h"
#include "tetris.h"
#include "score.h"
#include "menu.h"
#include "font.h"

Sint32 menuHighScoreInit(void *pArgs) {
	menu_t *this = pArgs;

	eventClear();

	SDL_SetRenderDrawColor(gVars.pRen, 0xAB, 0xCD, 0xEF, 0x00);
	bzero(this, sizeof(*this));
	bzero(gVars.nKeyb, sizeof gVars.nKeyb);

	return 0;
}

Sint32 menuHighScoreRelease(void *pArgs) {
	menu_t *this = pArgs;

	(void)this;
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

	SDL_RenderFillRect(gVars.pRen, NULL);

	for (i = 0; i < MAX_SCORE; i++) {
		if (gVars.sScore.pPlayer[i].nScore == 0)
			sprintf(s, "%-15s   :   %s", "----", "----");
		else
			sprintf(s, "%-15s   :   %u",
				gVars.sScore.pPlayer[i].pName, gVars.sScore.pPlayer[i].nScore);
		printText(s, 30, FONT_COL_BLUE_BLUE, 100, 100 + 50 * i);
	}

	if (menuHighScoreEvents(pArgs) >= 0)
		return MENU_MAIN;

	return MENU_NULL;
}
