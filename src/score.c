#include <stdio.h>
#include <SDL.h>
#include "tetris.h"
#include "score.h"
#include "game.h"

void scoreEncode(score_t *score) {
	Uint32 i;
	Uint8 *p;

	p = (Uint8 *) score;
	for (i = 0; i < sizeof *score; i++) {
		*p = ((~(*p)) ^ 42) | 0x80;
		p++;
	}
}

void scoreDecode(score_t *score) {
	Uint32 i;
	Uint8 *p;

	p = (Uint8 *) score;
	for (i = 0; i < sizeof *score; i++) {
		*p = ((~(*p)) ^ 42) & 0x7F;
		p++;
	}
}

score_t loadScore(void) {
	FILE *pFile;
	score_t sScore;

	memset(&sScore, 0, sizeof sScore);
	pFile = fopen(SCORE_FILE, "r");
	if (pFile == NULL)
		return sScore;
	if (fread(sScore.pPlayer, sizeof sScore.pPlayer[0], NB_SCORE, pFile) != NB_SCORE) {
		fprintf(stderr, "Failed to open scores... reseting scores\n");
		memset(&sScore, 0, sizeof sScore);
		fclose(pFile);
		return sScore;
	}
	fclose(pFile);
	scoreDecode(&sScore);
	return sScore;
}

Sint32 saveScore(void) {
	FILE *pFile;
	score_t score = gVars.sScore;

	pFile = fopen(SCORE_FILE, "w");
	if (pFile == NULL) {
		fprintf(stderr, "Failed to save scores...\n");
		return -1;
	}
	scoreEncode(&score);
	if (fwrite(score.pPlayer, sizeof score.pPlayer[0], NB_SCORE, pFile) != NB_SCORE) {
		fprintf(stderr, "Failed to save scores ...\n");
		fclose(pFile);
		pFile = fopen(SCORE_FILE, "w");
		fclose(pFile);
		return -1;
	}
	fclose(pFile);
	return 0;
}

Sint32 isHighScore(Uint32 nScore) {
	Sint32 i;
	
	for (i = 0; i < NB_SCORE; i++) {
		if (nScore > gVars.sScore.pPlayer[i].nScore)
			return i;
	}
	return -1;
}

void scoreAdd(Sint32 nPos, Uint32 nScore, char *name) {
	Sint32 i;

	if (nPos < 0 || nPos >= NB_SCORE)
		return;

	for (i = NB_SCORE - 1; i > nPos; i--)
		gVars.sScore.pPlayer[i] = gVars.sScore.pPlayer[i - 1];

	strncpy(gVars.sScore.pPlayer[nPos].pName, name, NAME_LEN);
	gVars.sScore.pPlayer[nPos].pName[NAME_LEN] = '\0';
	gVars.sScore.pPlayer[nPos].nScore = nScore;
}
