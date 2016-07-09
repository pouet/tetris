#ifndef GAME_H
#define GAME_H

enum {
	GRID_LG = 10,
	GRID_HT = 22,
	MAX_TET = 7,
	MAX_ROT = 4,
	TET_LG = 4,
	TET_HT = 4,
	CASE_NOTET = MAX_TET,
	DELAY_TO_LOCK = 20
};

enum {
	TET_NEXT_OFFX = 15,
	TET_NEXT_OFFY = 5,
	TET_HOLD_OFFX = 15,
	TET_HOLD_OFFY = 10
};

typedef struct game_s {
	Sint32 tGrid[GRID_HT][GRID_LG];
	Sint32 tLine[GRID_HT];

	Sint32 nPieceCur;
	Sint32 nPieceHold;
	Sint32 nPieceNxt;
	Sint32 nPieceRot;

	Sint32 nRow;
	Sint32 nCol;

	Sint32 nInc;
	Sint32 nDelay; /* Delay avant de poser la piece */

	Uint32 nLevel;
	Uint32 nScore;
	Uint32 nLine;
	Uint32 nTime;
} game_t;

Sint32 gameInit(void *pArgs);
Sint32 gameMain(void *pArgs);
Sint32 gameRelease(void *pArgs);

#endif
