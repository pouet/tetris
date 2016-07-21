#include <SDL.h>
#include "tetris.h"
#include "score.h"
#include "menu.h"
#include "font.h"
#include "sfx.h"

Sint32 menuHelpInit(void *pArgs) {
	menu_t *this = pArgs;

	(void)this;
	eventClear();

	return 0;
}

Sint32 menuHelpRelease(void *pArgs) {
	menu_t *this = pArgs;

	(void)this;
	sfxPlaySound(SFX_PLAY_ROTATE, SFX_REPEAT_OFF);
	return 0;
}

Sint32 menuHelpEvents(void *pArgs) {
	menu_t *this = pArgs;

	(void)this;

	if (gVars.nKeyb[KEY_SPACE]) {
		gVars.nKeyb[KEY_SPACE] = KEY_NONE;
		return 0;
	}

	return -1;
}

Sint32 menuHelpMain(void *pArgs) {
	menu_t *this = pArgs;
	Sint32 i;
	char *pTab[16][2] = {
		{ "escape", "quit"   },
		{ "     p", "pause"  },
		{ "  left", "move l" },
		{ " right", "move r" },
		{ "    up", "rotate" },
		{ "  down", "down"   },
		{ " space", "drop"   },
		{ "     c", "hold"   },
		{ NULL    , NULL     }
	};

	(void)this;

	blitTexture(gVars.pBackground, 0, 0, NULL);

	for (i = 0; pTab[i][0] != NULL; i++) {
		printText(pTab[i][0], MENU_FONT_SIZE,
				FONT_COL_WHITE_RED, MENU_OFFX + 10, MENU_OFFY + 30 * i);
		printText(pTab[i][1], MENU_FONT_SIZE,
				FONT_COL_WHITE_BLUE, MENU_OFFX + 160, MENU_OFFY + 30 * i);
	}

	if (menuHelpEvents(pArgs) >= 0)
		return MENU_MAIN;

	return MENU_NULL;
}
