#include <SDL.h>
#include "tetris.h"
#include "game.h"
#include "font.h"
#include "sfx.h"

Uint32 gFrameToDrop[MAX_LEVEL + 1] = {
	0,
	48,
	43,
	38,
	33,
	28,
	23,
	20,
	18,
	15,
	13,
	11,
	9,
	8,
	7,
	6,
	5,
	4,
	3,
	2,
	1
};

Sint32 getNextPiece(void) {
	static Sint32 tPieces[MAX_TET];
	static Uint32 nPcs = MAX_TET;
	int i, n, tmp;

	if (nPcs >= MAX_TET) {
		nPcs = 0;
		for (i = 0; i < MAX_TET; i++)
			tPieces[i] = i;
		for (i = 0; i < MAX_TET; i++) {
			n = (rand() % (MAX_TET - i)) + i;
			tmp = tPieces[n];
			tPieces[n] = tPieces[i];
			tPieces[i] = tmp;
		}
	}
	return tPieces[nPcs++];
}

Sint32 gameInit(void *pArgs) {
	game_t *this = pArgs;
	int i, j;

	eventClear();

	memset(this, 0, sizeof *this);
	for (i = 0; i < GRID_HT; i++)
		for (j = 0; j < GRID_LG; j++)
			this->tGrid[i][j] = CASE_NOTET;

	this->nState = GAME_ANIM_GRID_BEGIN;

	this->nPieceHold = -1;
	this->nPieceCur = getNextPiece();
	this->nPieceNxt = getNextPiece();
	this->nPieceRot = 0;
	this->nDelay = DELAY_TO_LOCK;

	this->nRow = 2;
	this->nCol = (GRID_LG / 2) - (TET_LG / 2);

	this->nLevel = gOpts.nLevelStart;
	this->nInc = gFrameToDrop[this->nLevel];
	this->nScore = 0;
	this->nTime = 0;

	return 0;
}

Sint32 isPosValid(game_t *this, Sint32 nTet, Sint32 nRot, Sint32 nRow, Sint32 nCol) {
	int i;
	int iRow, iCol;

	for (i = 0; i < NB_TET_BLOCK; i++) {
		iRow = nRow + gTetros[nTet][nRot][i].y;
		iCol = nCol + gTetros[nTet][nRot][i].x;
		if (iCol < 0 || iCol >= GRID_LG || iRow < 0 || iRow >= GRID_HT ||
			this->tGrid[iRow][iCol] != CASE_NOTET)
			return 0;
	}
	return 1;
}

Sint32 gameRelease(void *pArgs) {
	game_t *this = pArgs;
	(void)this;
	return 0;
}

void blitOneBlock(Sint32 nTet, int row, int col, int y, int x) {
	SDL_Rect rClip;
	SDL_Rect r;

	SDL_QueryTexture(gVars.pTetsImg, NULL, NULL, NULL, &r.h);
	r.w = r.h;
	rClip.x = r.w * nTet;
	rClip.y = 0;
	rClip.w = r.w;
	rClip.h = r.w;

	r.x = col + x * r.w;
	r.y = row + y * r.w;
	if (r.y < 64)
		return;
	SDL_RenderCopy(gVars.pRen, gVars.pTetsImg, &rClip, &r);
}

void gameDrawTetro(Sint32 nTet, Sint32 nRot, int row, int col) {
	int i;
	int iRow, iCol;

	for (i = 0; i < NB_TET_BLOCK; i++) {
		iRow = gTetros[nTet][nRot][i].y;
		iCol = gTetros[nTet][nRot][i].x;
		blitOneBlock(nTet, row, col, iRow, iCol);
	}
}

void gameDrawGhost(game_t *this) {
	Sint32 nRow = this->nRow + 1;
	int i;
	int iRow, iCol;

	while (isPosValid(this, this->nPieceCur, this->nPieceRot, nRow, this->nCol))
		nRow++;
	nRow--;
	
	for (i = 0; i < NB_TET_BLOCK; i++) {
		iRow = gTetros[this->nPieceCur][this->nPieceRot][i].y;
		iCol = gTetros[this->nPieceCur][this->nPieceRot][i].x;
		blitOneBlock(MAX_TET, PLAYGRID_OFFY + (nRow - LINE_HIDDEN) * 32,
				PLAYGRID_OFFX + this->nCol * 32, iRow, iCol);
	}
}

void gameDrawText(game_t *this) {
	char s[50] = "";

	if (this->nState == GAME_PAUSE)
		printText("* paused *", 32, FONT_COL_GREEN_GREEN, PLAYGRID_OFFX, (32 * GRID_HT) / 2);

	printText("Level", 20, FONT_COL_WHITE_BLUE, 150, 500);
	sprintf(s, "%5d", this->nLevel);
	printText(s, 20, FONT_COL_WHITE_RED, 150, 530);

	printText("Score", 20, FONT_COL_WHITE_BLUE, 150, 570);
	sprintf(s, "%5d", this->nScore);
	printText(s, 20, FONT_COL_WHITE_RED, 150, 600);

	printText("Line", 20, FONT_COL_WHITE_BLUE, 150, 640);
	sprintf(s, "%5d", this->nLine);
	printText(s, 20, FONT_COL_WHITE_RED, 150, 670);

	printText("Time", 20, FONT_COL_WHITE_BLUE, 800, 530);
	sprintf(s, "%02d:%02d", (this->nTime / FPS) / 60, (this->nTime / FPS) % 60);
	printText(s, 20, FONT_COL_WHITE_GREY, 800, 560);
}

void gameDraw(game_t *this) {
	int i, j;

	blitTexture(gVars.pBackground, 0, 0, NULL);

	if (this->nState != GAME_PAUSE) {
		if (gOpts.nGhost && this->nState == GAME_NORMAL)
			gameDrawGhost(this);
		for (i = LINE_HIDDEN; i < GRID_HT; i++) {
			for (j = 0; j < GRID_LG; j++) {
				if (this->tGrid[i][j] != CASE_NOTET) {
					blitOneBlock(this->tGrid[i][j], PLAYGRID_OFFY, PLAYGRID_OFFX, i - LINE_HIDDEN, j);
				}
			}
		}
	}

	if (this->nState == GAME_NORMAL) {
		gameDrawTetro(this->nPieceCur, this->nPieceRot,
				PLAYGRID_OFFY + (this->nRow - LINE_HIDDEN) * 32,
				PLAYGRID_OFFX + this->nCol * 32);
		gameDrawTetro(this->nPieceNxt, 0, TET_NEXT_OFFY, TET_NEXT_OFFX);
		if (this->nPieceHold >= 0)
			gameDrawTetro(this->nPieceHold, 0, TET_HOLD_OFFY, TET_HOLD_OFFX);
	}
	gameDrawText(this);
}

void gameAnchorPiece(game_t *this) {
	int i;
	int iRow, iCol;

	for (i = 0; i < NB_TET_BLOCK; i++) {
		iRow = this->nRow + gTetros[this->nPieceCur][this->nPieceRot][i].y;
		iCol = this->nCol + gTetros[this->nPieceCur][this->nPieceRot][i].x;
		this->tGrid[iRow][iCol] = this->nPieceCur;
		this->tLine[iRow]++;
	}
}

void movePiece(game_t *this, Uint32 nKey, Sint32 nInc) {
	if (isPosValid(this, this->nPieceCur, this->nPieceRot, this->nRow, this->nCol + nInc)) {
		this->nCol += nInc;
		this->nDelay = DELAY_TO_LOCK;
		sfxPlaySound(SFX_PLAY_MOVE, SFX_REPEAT_OFF);
	}
	if (gVars.nKeyb[nKey] == KEY_PRESSED)
		gVars.nKeyb[nKey] = KEY_MAX_DELAY;
}

void rotatePiece(game_t *this) {
	Sint32 nRot = (this->nPieceRot + 1) % MAX_ROT;
	Sint32 nCol = this->nCol;
	Sint32 nRow = this->nRow;

	/* Test de rotation normal */
	if (isPosValid(this, this->nPieceCur, nRot, this->nRow, this->nCol))
		this->nPieceRot = nRot;
	/* Test une case a droite */
	else if (isPosValid(this, this->nPieceCur, nRot, this->nRow, this->nCol + 1))
		this->nCol++;
	/* Test une case a gauche */
	else if (isPosValid(this, this->nPieceCur, nRot, this->nRow, this->nCol - 1))
		this->nCol--;
	/* Test juste pour la barre... wall kick droit */
	else if (this->nCol + gTetros[this->nPieceCur][nRot][3].x >= GRID_LG &&
			isPosValid(this, this->nPieceCur, nRot, this->nRow, GRID_LG - 4))
		this->nCol = GRID_LG - 4;
	/* wall kick gauche */
	else if (this->nCol < 0 &&
			isPosValid(this, this->nPieceCur, nRot, this->nRow, 0))
		this->nCol = 0;
	/* floor kick */
	else if (isPosValid(this, this->nPieceCur, nRot, this->nRow - 1, this->nCol))
		this->nRow--;
	/* Test juste pour la barre... floor kick */
	else if (this->nPieceCur == 0 &&
			isPosValid(this, this->nPieceCur, nRot, this->nRow - 2, this->nCol))
		this->nRow -= 2;

	if (nCol != this->nCol || nRow != this->nRow)
		this->nPieceRot = nRot;

	/* Pas de repetition pour la rotation */
	gVars.nKeyb[KEY_UP] = KEY_NONE;
	if (this->nPieceRot == nRot) {
		this->nDelay = DELAY_TO_LOCK;
		sfxPlaySound(SFX_PLAY_ROTATE, SFX_REPEAT_OFF);
	}
}

void hardDrop(game_t *this) {
	Sint32 nRow = this->nRow + 1;

	while (isPosValid(this, this->nPieceCur, this->nPieceRot, nRow, this->nCol)) {
		nRow++;
		this->nScore += SCORE_HARD_DROP;
	}
	this->nRow = nRow - 1;
	/* Pas de repetition pour un hard drop */
	gVars.nKeyb[KEY_SPACE] = KEY_NONE;
	this->nDelay = 0;
	this->nInc = 0;
	sfxPlaySound(SFX_PLAY_DROP, SFX_REPEAT_OFF);
}

void softDrop(game_t *this) {
	if (isPosValid(this, this->nPieceCur, this->nPieceRot, this->nRow + 1, this->nCol)) {
		this->nRow++;
		this->nScore += SCORE_SOFT_DROP;
	}
	gVars.nKeyb[KEY_SPACE] = KEY_MAX_DELAY;
}

Sint32 eventsGamePaused(game_t *this) {
	if (gVars.nKeyb[KEY_P] == KEY_PRESSED) {
		if (this->nState == GAME_PAUSE) {
			sfxPlayAudio();
			this->nState = this->nLastState;
			this->nLastState = GAME_PAUSE;
		}
		else {
			sfxPauseAudio();
			this->nLastState = this->nState;
			this->nState = GAME_PAUSE;
		}
		gVars.nKeyb[KEY_P] = KEY_NONE;
	}

	if (this->nState == GAME_PAUSE || this->nState != GAME_NORMAL)
		return 1;
	else
		return 0;
}

void holdPiece(game_t *this) {
	Sint32 nPieceTmp;

	gVars.nKeyb[KEY_C] = KEY_NONE;

	if (this->nHold)
		return;

	if (this->nPieceHold < 0) {
		this->nPieceHold = this->nPieceCur;
		this->nPieceCur = this->nPieceNxt;
		this->nPieceNxt = getNextPiece();
	}
	else {
		nPieceTmp = this->nPieceHold;
		this->nPieceHold = this->nPieceCur;
		this->nPieceCur = nPieceTmp;
	}

	this->nPieceRot = 0;
	this->nDelay = DELAY_TO_LOCK;
	this->nInc = gFrameToDrop[this->nLevel];
	this->nRow = 2;
	this->nCol = (GRID_LG / 2) - (TET_LG / 2);

	if (!isPosValid(this, this->nPieceCur, this->nPieceRot, this->nRow, this->nCol)) {
		this->nRow--;
		if (!isPosValid(this, this->nPieceCur, this->nPieceRot, this->nRow, this->nCol))
			this->nRow--;
	}

	this->nHold = 1;
}

void processEvents(game_t *this) {
	int i;

	if (eventsGamePaused(this))
		return;

	/* Delay de repetition sur les touches */
	/* valable que sur 2 touches en fait... */
	for (i = 0; i < KEY_LAST; i++) {
		if (gVars.nKeyb[i] > KEY_DELAY)
			gVars.nKeyb[i]--;
	}

	if (gVars.nKeyb[KEY_LEFT] == KEY_PRESSED || gVars.nKeyb[KEY_LEFT] == KEY_DELAY)
		movePiece(this, KEY_LEFT, -1);
	if (gVars.nKeyb[KEY_RIGHT] == KEY_PRESSED || gVars.nKeyb[KEY_RIGHT] == KEY_DELAY)
		movePiece(this, KEY_RIGHT, 1);

	if (gVars.nKeyb[KEY_UP] == KEY_PRESSED)
		rotatePiece(this);

	if (gVars.nKeyb[KEY_SPACE] == KEY_PRESSED)
		hardDrop(this);

	if (gVars.nKeyb[KEY_DOWN] == KEY_PRESSED)
		softDrop(this);

	if (gVars.nKeyb[KEY_C] == KEY_PRESSED)
		holdPiece(this);
}

Uint32 delFullLine(game_t *this) {
	Uint32 nLine = 0;
	int i, j, k;

	for (i = GRID_HT - 1; i > 0; i--) {
		if (this->tLine[i] >= GRID_LG) {
			for (k = i; k > 0; k--) {
				for (j = 0; j < GRID_LG; j++) {
					this->tGrid[k][j] = this->tGrid[k - 1][j];
				}
				this->tLine[k] = this->tLine[k - 1];
			}
			nLine++;
			i++;
		}
	}
	return nLine;
}

void gamePieceLock(game_t *this) {
	static Uint32 pnScore[MAX_LINE + 1] = {
		0, SCORE_1_LINE, SCORE_2_LINE, SCORE_3_LINE, SCORE_4_LINE
	};
	Uint32 nLine;

	gameAnchorPiece(this);
	nLine = delFullLine(this);
	this->nScore += pnScore[nLine] * this->nLevel;
	if (this->nScore > SCORE_MAX)
		this->nScore = SCORE_MAX;
	this->nLine += nLine;
	if (this->nLevel < MAX_LEVEL && this->nLine > this->nLevel * LINE_PER_LEVEL) {
		this->nLevel++;
		sfxPlaySound(SFX_PLAY_LEVELUP, SFX_REPEAT_OFF);
	}
	else if (nLine > 0) {
		if (nLine == 4)
			sfxPlaySound(SFX_PLAY_TETRIS, SFX_REPEAT_OFF);
		else
			sfxPlaySound(SFX_PLAY_LINE, SFX_REPEAT_OFF);
	}

	this->nPieceCur = this->nPieceNxt;
	this->nPieceNxt = getNextPiece();
	this->nPieceRot = 0;
	this->nDelay = DELAY_TO_LOCK;
	this->nInc = gFrameToDrop[this->nLevel];
	this->nRow = 2;
	this->nCol = (GRID_LG / 2) - (TET_LG / 2);
	this->nHold = 0;


	if (!isPosValid(this, this->nPieceCur, this->nPieceRot, this->nRow, this->nCol)) {
		this->nRow--;
		if (!isPosValid(this, this->nPieceCur, this->nPieceRot, this->nRow, this->nCol))
			this->nRow--;
	}
}

Sint32 gamePieceDown(game_t *this) {
	this->nInc = gFrameToDrop[this->nLevel];

	if (isPosValid(this, this->nPieceCur, this->nPieceRot, this->nRow + 1, this->nCol)) {
		this->nRow++;
		this->nDelay = DELAY_TO_LOCK;
		return MENU_NULL;
	}

	/* Game over */
	if (this->nRow <= 0) {
		sfxStopAllAudio();
		sfxPlaySound(SFX_PLAY_GAMEOVER, SFX_REPEAT_OFF);
		this->nState = GAME_ANIM_GRID_FINISH;
	}
	else if (this->nDelay == 0)
		gamePieceLock(this);

	return MENU_NULL;
}

Sint32 gameNormal(game_t *this) {
	Sint32 nRet = MENU_NULL;

	this->nInc--;
	if (this->nInc <= 0)
		nRet = gamePieceDown(this);
	if (this->nDelay > 0)
		this->nDelay--;

	this->nTime++;

	return nRet;
}

void gameAnimGrid(game_t *this, Uint32 nNextState) {
	static int nDelay;
	Uint32 i, j;

	/* Juste pour que ce soit pas trop rapide */
//	nDelay ^= 1;
	nDelay = (nDelay + 1) & 3;
	if (nDelay)
		return;

	if (this->nStart < GRID_HT)
		this->nStart++;
	if (this->nStart == GRID_HT)
		this->nEnd++;

	for (i = 0; i < GRID_HT; i++) {
		for (j = 0; j < GRID_LG; j++) {
			if (i < this->nEnd)
				this->tGrid[GRID_HT - i - 1][j] = CASE_NOTET;
			else if (i < this->nStart)
				this->tGrid[GRID_HT - i - 1][j] = i % MAX_TET;
		}
	}

	if (this->nEnd == this->nStart) {
		this->nState = nNextState;
		this->nEnd = 0;
		this->nStart = 0;
	}
}

Sint32 gameMain(void *pArgs) {
	game_t *this = pArgs;
	Sint32 nRet = MENU_NULL;

	processEvents(this);

	switch (this->nState) {
		case GAME_NORMAL:
			nRet = gameNormal(this);
			break;

		case GAME_ANIM_GRID_BEGIN:
			gameAnimGrid(this, GAME_NORMAL);
			break;

		case GAME_ANIM_GRID_FINISH:
			gameAnimGrid(this, GAME_GAMEOVER);
			break;

		case GAME_PAUSE:
			/* Nothing to do ! */
			break;

		case GAME_GAMEOVER:
			nRet = MENU_GAMEOVER;
			break;

		default:
			fprintf(stderr, "Ups... something wrong :(\n");
			exit(EXIT_FAILURE);
			break;
	}

	gameDraw(this);
	return nRet;
}
