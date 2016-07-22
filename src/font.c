#include <SDL.h>
#include "tetris.h"
#include "font.h"

void printText(char *s, int nSize, int nFont, int x, int y) {
	static char *pLetters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.:!'-*>< ";
	SDL_Rect rSrc, rDst;
	SDL_Rect r;
	int nLen;
	int i;

	if (nSize <= 0 || nSize > 256)
		nSize = FONT_DEFAULT_SIZE;
	if (nFont < 0 || nFont >= FONT_COL_MAX)
		nFont = FONT_COL_WHITE_BLACK;

	nLen = strlen(s);
	r.h = FONT_HEIGHT;

	rSrc.x = 0;
	rSrc.y = r.h * nFont;
	rSrc.h = r.h;
	rSrc.w = r.h;

	rDst.x = x;
	rDst.y = y;
	rDst.h = nSize;
	rDst.w = nSize;

	for (i = 0; i < nLen; i++) {
		char *p = strchr(pLetters, toupper(s[i]));
		if (p == NULL)
			p = strchr(pLetters, ' ');
		rSrc.x = (p - pLetters) * r.h;
		SDL_RenderCopy(gVars.pRen, gVars.pFont, &rSrc, &rDst);
		rDst.x += nSize;
	}
}
