#ifndef GAME_H
#define GAME_H

/* ********************************* */
/* *          Constantes           * */
/* ********************************* */

enum {
	GRID_LG = 10,
	GRID_HT = 22,
	LINE_HIDDEN = 2,
	MAX_TET = 7,
	NB_TET_BLOCK = 4,
	MAX_ROT = 4,
	MAX_LINE = 4,
	MAX_LEVEL = 20,
	LEVEL_START = 1,
	TET_LG = 4,
	TET_HT = 4,
	CASE_NOTET = MAX_TET,
	DELAY_TO_LOCK = 20,
	INC_TO_NEXT_LINE = 20,
	LINE_PER_LEVEL = 10
};

enum {
	SCORE_1_LINE = 100,
	SCORE_2_LINE = 300,
	SCORE_3_LINE = 500,
	SCORE_4_LINE = 800,
	SCORE_SOFT_DROP = 1,
	SCORE_HARD_DROP = 2
};

enum {
	TET_NEXT_OFFX = 350,
	TET_NEXT_OFFY = 150,
	TET_HOLD_OFFX = 350,
	TET_HOLD_OFFY = 320
};

enum {
	GAME_NORMAL,
	GAME_ANIM_GRID_BEGIN,
	GAME_ANIM_GRID_FINISH,
	GAME_PAUSE,
	GAME_GAMEOVER
};

/* ********************************* */
/* *          Structures           * */
/* ********************************* */

typedef struct game_s {
	Sint32 tGrid[GRID_HT][GRID_LG];
	Sint32 tLine[GRID_HT];

	Uint32 nState;
	Uint32 nLastState;

	/* for animation */
	Uint32 nStart;
	Uint32 nEnd;
// ???
	Sint32 nSleep;

	Uint32 nHold;

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

	char pName[256];
	Uint32 nPos;
} game_t;

extern SDL_Point gTetros[MAX_TET][MAX_ROT][NB_TET_BLOCK];

/* ********************************* */
/* *          Prototypes           * */
/* ********************************* */

Sint32 gameInit(void *pArgs);
Sint32 gameMain(void *pArgs);
Sint32 gameRelease(void *pArgs);

#endif
