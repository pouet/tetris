#ifndef FONT_H
#define FONT_H

#include "SDL.h"

enum {
	FONT_DEFAULT_SIZE = 8,
	FONT_HEIGHT = 8
};

enum {
	FONT_COL_WHITE_BLACK,
	FONT_COL_WHITE_BLUE,
	FONT_COL_WHITE_RED,
	FONT_COL_WHITE_GREY,
	FONT_COL_BLUE_BLUE,
	FONT_COL_ORANGE_GREY,
	FONT_COL_GREEN_GREEN,
	FONT_COL_CYAN_BLUE,
	FONT_COL_MAX
};

/* ********************************* */
/* *          Prototypes           * */
/* ********************************* */

void printText(char *s, int nSize, int nFont, int x, int y);

#endif
