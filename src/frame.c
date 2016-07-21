#include <SDL.h>
#include "tetris.h"

static Uint32 gnTimer;

void franeInit(void) {
	gnTimer = SDL_GetTicks();
}

void frameWait(void) {
	Uint32 nTimer;

	while (1) {
		nTimer = SDL_GetTicks() - gnTimer;
		if (nTimer >= FPS_DFLT)
			break;
		SDL_Delay(3);
	}
	gnTimer = SDL_GetTicks();
}
