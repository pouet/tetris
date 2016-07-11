#ifndef GAME_H
#define GAME_H

enum {
	GRID_LG = 10,
	GRID_HT = 22,
	MAX_TET = 7,
	MAX_ROT = 4,
	MAX_LINE = 4,
	MAX_LEVEL = 9,
	LEVEL_START = 1,
	TET_LG = 4,
	TET_HT = 4,
	CASE_NOTET = MAX_TET,
	DELAY_TO_LOCK = 20,
	INC_TO_NEXT_LINE = 20
};

enum {
	SCORE_1_LINE = 1,
	SCORE_2_LINE = 3,
	SCORE_3_LINE = 7,
	SCORE_4_LINE = 15,
};

enum {
	TET_NEXT_OFFX = 350,
	TET_NEXT_OFFY = 150,
	TET_HOLD_OFFX = 350,
	TET_HOLD_OFFY = 320
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
