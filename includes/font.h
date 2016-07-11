#ifndef FONT_H
#define FONT_H

#include "SDL.h"

/* ********************************* */
/* *          Prototypes           * */
/* ********************************* */

SDL_Texture	*createFont(char *s, int nSize);
void printText(char *s, int nSize, int x, int y);

#endif
