#include <string.h>
#include "SDL.h"
#include "tetris.h"

SDL_Texture	*createFont(char *s, int nSize) {
	SDL_Surface *pSfc;
	SDL_Texture *pTex;
	SDL_Rect r;
	int nLen;
	int i;

	Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	rmask = 0xff000000;
	gmask = 0x00ff0000;
	bmask = 0x0000ff00;
	amask = 0x000000ff;
#else
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = 0xff000000;
#endif

(void)nSize;
	nLen = strlen(s);
	SDL_QueryTexture(gVars.pFont, NULL, NULL, NULL, &r.h);
	r.w = r.h * nLen; 

	pSfc = SDL_CreateRGBSurface(0, r.w, r.h, 32, rmask, gmask, bmask, amask);
	if (pSfc == NULL) {
		fprintf(stderr, "SDL_CreateRGBSurface: %s\n", SDL_GetError());
		return NULL;
	}
	SDL_SetColorKey(pSfc, SDL_TRUE, SURFACE_TRANSPARENT_COLOR);
	pTex = SDL_CreateTextureFromSurface(gVars.pRen, pSfc);
	SDL_FreeSurface(pSfc);

	pTex = SDL_CreateTexture(gVars.pRen, SDL_PIXELFORMAT_ARGB8888,
			SDL_TEXTUREACCESS_TARGET, r.w, r.h);
	if (pTex == NULL) {
		fprintf(stderr, "SDL_CreateTexture: %s\n", SDL_GetError());
		return NULL;
	}
	SDL_SetTextureBlendMode(pTex, SDL_BLENDMODE_BLEND);
	SDL_SetRenderTarget(gVars.pRen, pTex);
	SDL_SetRenderDrawColor(gVars.pRen, 0xff, 0x00, 0xff, 0);
	SDL_RenderFillRect(gVars.pRen, NULL);

	SDL_Rect rSrc, rDst;

	rSrc.x = 0;
	rSrc.y = 0;
	rSrc.h = r.h;
	rSrc.w = r.h;

	rDst.x = 0;
	rDst.y = 0;
	rDst.h = r.h;
	rDst.w = r.h;

	for (i = 0; i < nLen; i++) {
		rSrc.x = (s[i] - ' ') * r.h;
		SDL_RenderCopy(gVars.pRen, gVars.pFont, &rSrc, &rDst);
		rDst.x += r.h;
	}

	SDL_SetRenderTarget(gVars.pRen, NULL);
	return pTex;
}
