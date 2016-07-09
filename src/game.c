#include "SDL.h"
#include "tetris.h"
#include "game.h"

Sint32 gtTetros[MAX_TET][MAX_ROT][TET_HT][TET_LG] = {
	{
		{	{ 0, 0, 0, 0 },
			{ 1, 1, 1, 1 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{	{ 0, 1, 0, 0 },
			{ 0, 1, 0, 0 },
			{ 0, 1, 0, 0 },
			{ 0, 1, 0, 0 }
		},
		{	{ 0, 0, 0, 0 },
			{ 1, 1, 1, 1 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{	{ 0, 1, 0, 0 },
			{ 0, 1, 0, 0 },
			{ 0, 1, 0, 0 },
			{ 0, 1, 0, 0 }
		}
	},
	{
		{	{ 1, 0, 0, 0 },
			{ 1, 1, 1, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{	{ 0, 1, 1, 0 },
			{ 0, 1, 0, 0 },
			{ 0, 1, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{	{ 0, 0, 0, 0 },
			{ 1, 1, 1, 0 },
			{ 0, 0, 1, 0 },
			{ 0, 0, 0, 0 }
		},
		{	{ 0, 1, 0, 0 },
			{ 0, 1, 0, 0 },
			{ 1, 1, 0, 0 },
			{ 0, 0, 0, 0 }
		}
	},
	{
		{	{ 0, 0, 1, 0 },
			{ 1, 1, 1, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{	{ 0, 1, 0, 0 },
			{ 0, 1, 0, 0 },
			{ 0, 1, 1, 0 },
			{ 0, 0, 0, 0 }
		},
		{	{ 0, 0, 0, 0 },
			{ 1, 1, 1, 0 },
			{ 1, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{	{ 1, 1, 0, 0 },
			{ 0, 1, 0, 0 },
			{ 0, 1, 0, 0 },
			{ 0, 0, 0, 0 }
		}
	},
	{
		{	{ 0, 1, 1, 0 },
			{ 0, 1, 1, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{	{ 0, 1, 1, 0 },
			{ 0, 1, 1, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{	{ 0, 1, 1, 0 },
			{ 0, 1, 1, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{	{ 0, 1, 1, 0 },
			{ 0, 1, 1, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		}
	},
	{
		{	{ 0, 1, 1, 0 },
			{ 1, 1, 0, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{	{ 0, 1, 0, 0 },
			{ 0, 1, 1, 0 },
			{ 0, 0, 1, 0 },
			{ 0, 0, 0, 0 }
		},
		{	{ 0, 0, 0, 0 },
			{ 0, 1, 1, 0 },
			{ 1, 1, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{	{ 1, 0, 0, 0 },
			{ 1, 1, 0, 0 },
			{ 0, 1, 0, 0 },
			{ 0, 0, 0, 0 }
		}
	},
	{
		{	{ 0, 1, 0, 0 },
			{ 1, 1, 1, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{	{ 0, 1, 0, 0 },
			{ 0, 1, 1, 0 },
			{ 0, 1, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{	{ 0, 0, 0, 0 },
			{ 1, 1, 1, 0 },
			{ 0, 1, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{	{ 0, 1, 0, 0 },
			{ 1, 1, 0, 0 },
			{ 0, 1, 0, 0 },
			{ 0, 0, 0, 0 }
		}
	},
	{
		{	{ 1, 1, 0, 0 },
			{ 0, 1, 1, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{	{ 0, 0, 1, 0 },
			{ 0, 1, 1, 0 },
			{ 0, 1, 0, 0 },
			{ 0, 0, 0, 0 }
		},
		{	{ 0, 0, 0, 0 },
			{ 1, 1, 0, 0 },
			{ 0, 1, 1, 0 },
			{ 0, 0, 0, 0 }
		},
		{	{ 0, 1, 0, 0 },
			{ 1, 1, 0, 0 },
			{ 1, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		}
	}
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

Sint32 isPosValid(game_t *this, Sint32 nTet, Sint32 nRot, Sint32 nRow, Sint32 nCol) {
	int i, j;
	int iRow, iCol;

	for (i = 0; i < TET_HT; i++) {
		iRow = nRow + i;
		for (j = 0; j < TET_LG; j++) {
			iCol = nCol + j;
			if (gtTetros[nTet][nRot][i][j] &&
					(iCol < 0 || iCol >= GRID_LG || iRow < 0 || iRow >= GRID_HT))
				return 0;
			if (gtTetros[nTet][nRot][i][j] && this->tGrid[iRow][iCol] != CASE_NOTET)
				return 0;
		}
	}
	return 1;
}

Sint32 gameInit(void *pArgs) {
	game_t *this = pArgs;
	int i, j;

	bzero(this, sizeof *this);
	for (i = 0; i < GRID_HT; i++)
		for (j = 0; j < GRID_LG; j++)
			this->tGrid[i][j] = CASE_NOTET;

	this->nPieceHold = -1;
	this->nPieceCur = getNextPiece();
	this->nPieceNxt = getNextPiece();
	this->nPieceRot = 0;
	this->nDelay = DELAY_TO_LOCK;

	this->nRow = 0;
	this->nCol = (GRID_LG / 2) - (TET_LG / 2);

	this->nLevel = 1;
	this->nScore = 0;
	this->nTime = 0;

	return 0;
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

//	r.x = (x + col) * r.w;
//	r.y = (y + row) * r.w;
	r.x = col + x * r.w;
	r.y = row + y * r.w;
	SDL_RenderCopy(gVars.pRen, gVars.pTetsImg, &rClip, &r);
}

void gameDrawTetro(Sint32 nTet, Sint32 nRot, int row, int col) {
	int i, j;

	for (i = 0; i < TET_HT; i++) {
		for (j = 0; j < TET_LG; j++) {
			if (gtTetros[nTet][nRot][i][j])
				blitOneBlock(nTet, row, col, i, j);
		}
	}
}

void gameDraw(game_t *this) {
	SDL_Rect r;
	int i, j;

	SDL_SetRenderDrawColor(gVars.pRen, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gVars.pRen);

	SDL_SetRenderDrawColor(gVars.pRen, 0x7F, 0x7F, 0x7F, 0x7F);
	r.x = 0;
	r.y = 0;
	r.w = GRID_LG * 32;
	r.h = GRID_HT * 32;
	SDL_RenderFillRect(gVars.pRen, &r);
	r.x = TET_NEXT_OFFX - 16;
	r.y = TET_NEXT_OFFY - 16;
	r.w = TET_LG * 32 + 32;
	r.h = TET_HT * 32;
	SDL_RenderFillRect(gVars.pRen, &r);

	for (i = 0; i < GRID_HT; i++) {
		for (j = 0; j < GRID_LG; j++) {
			if (this->tGrid[i][j] != CASE_NOTET) {
				blitOneBlock(this->tGrid[i][j], 0, 0, i, j);
			}
		}
	}
	gameDrawTetro(this->nPieceCur, this->nPieceRot, this->nRow * 32, this->nCol * 32);
	/* peut mieux faire... */
	if (this->nPieceNxt == 0)
		gameDrawTetro(this->nPieceNxt, 0, TET_NEXT_OFFY, TET_NEXT_OFFX);
	else if (this->nPieceNxt == 3)
		gameDrawTetro(this->nPieceNxt, 0, TET_NEXT_OFFY + 16, TET_NEXT_OFFX);
	else
		gameDrawTetro(this->nPieceNxt, 0, TET_NEXT_OFFY + 16, TET_NEXT_OFFX + 16);

	if (this->nPieceHold >= 0)
		gameDrawTetro(this->nPieceHold, 0, TET_HOLD_OFFY, TET_HOLD_OFFX);
}

void anchorPiece(game_t *this) {
	int i, j;
	int iRow, iCol;

	for (i = 0; i < TET_HT; i++) {
		iRow = this->nRow + i;
		for (j = 0; j < TET_LG; j++) {
			iCol = this->nCol + j;
			if (gtTetros[this->nPieceCur][this->nPieceRot][i][j]) {
				this->tGrid[iRow][iCol] = this->nPieceCur;
				this->tLine[iRow]++;
			}
		}
	}
}

void processEvents(game_t *this) {
	Sint32 nRot;
	Sint32 nRow;
	int i;

	for (i = 0; i < KEY_LAST; i++) {
		if (gVars.nKeyb[i] > KEY_DELAY)
			gVars.nKeyb[i]--;
	}

	if (gVars.nKeyb[KEY_LEFT] == KEY_PRESSED || gVars.nKeyb[KEY_LEFT] == KEY_DELAY) {
		if (isPosValid(this, this->nPieceCur, this->nPieceRot, this->nRow, this->nCol - 1)) {
			this->nCol--;
			this->nDelay = DELAY_TO_LOCK;
		}
		if (gVars.nKeyb[KEY_LEFT] == KEY_PRESSED)
			gVars.nKeyb[KEY_LEFT] = KEY_MAX_DELAY;
	}
	if (gVars.nKeyb[KEY_RIGHT] == KEY_PRESSED || gVars.nKeyb[KEY_RIGHT] == KEY_DELAY) {
		if (isPosValid(this, this->nPieceCur, this->nPieceRot, this->nRow, this->nCol + 1)) {
			this->nCol++;
			this->nDelay = DELAY_TO_LOCK;
		}
		if (gVars.nKeyb[KEY_RIGHT] == KEY_PRESSED)
			gVars.nKeyb[KEY_RIGHT] = KEY_MAX_DELAY;
	}
	if (gVars.nKeyb[KEY_UP] == KEY_PRESSED) {
		nRot = (this->nPieceRot + 1) % MAX_ROT;
		/* Test de rotation normal, sinon une case a gauche ou a droite */
		if (isPosValid(this, this->nPieceCur, nRot, this->nRow, this->nCol))
			this->nPieceRot = nRot;
		else if (isPosValid(this, this->nPieceCur, nRot, this->nRow, this->nCol - 1)) {
			this->nPieceRot = nRot;
			this->nCol--;
		}
		/* Test juste pour la barre... sinon probleme quand elle set collee a droite */
		else if (this->nPieceCur == 0 &&
				isPosValid(this, this->nPieceCur, nRot, this->nRow, this->nCol - 2)) {
			this->nPieceRot = nRot;
			this->nCol -= 2;
		}
		else if (isPosValid(this, this->nPieceCur, nRot, this->nRow, this->nCol + 1)) {
			this->nPieceRot = nRot;
			this->nCol++;
		}
		/* Pas de repetition pour la rotation */
		gVars.nKeyb[KEY_UP] = KEY_NONE;
		if (this->nPieceRot == nRot)
			this->nDelay = DELAY_TO_LOCK;
	}
	if (gVars.nKeyb[KEY_DOWN] == KEY_PRESSED) {
		nRow = this->nRow;
		while (isPosValid(this, this->nPieceCur, this->nPieceRot, nRow, this->nCol))
			nRow++;
		this->nRow = nRow - 1;
		/* Pas de repetition pour un hard drop */
		gVars.nKeyb[KEY_DOWN] = KEY_NONE;
		this->nDelay = 0;
	}
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

Sint32 gameMain(void *pArgs) {
	game_t *this = pArgs;

	processEvents(this);

	this->nInc += 1;
	if (this->nInc > 10) {
		if (isPosValid(this, this->nPieceCur, this->nPieceRot, this->nRow + 1, this->nCol)) {
			this->nRow++;
			this->nDelay = DELAY_TO_LOCK;
		}
		else {
			/* Game over */
			if (this->nRow <= 0) {
				anchorPiece(this);
				gameDraw(this);
				sleep(2);
				return MENU_MAIN;
			}
			else if (this->nDelay == 0) {
				anchorPiece(this);
				delFullLine(this);
				this->nPieceCur = this->nPieceNxt;
				this->nPieceNxt = getNextPiece();
				this->nPieceRot = 0;
				this->nRow = 0;
				this->nCol = (GRID_LG / 2) - (TET_LG / 2);
			}
		}
		this->nInc = 0;
	}
	if (this->nDelay > 0)
		this->nDelay--;

	gameDraw(this);
	return MENU_NULL;
}
