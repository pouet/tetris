#include <stdio.h>
#include "SDL.h"
#include "tetris.h"
#include "score.h"
#include "game.h"

score_t loadScore(void) {
	FILE *pFile;
	score_t sScore;

	bzero(&sScore, sizeof sScore);
	pFile = fopen(SCORE_FILE, "r");
	if (pFile == NULL)
		return sScore;
	if (fread(sScore.pPlayer, sizeof sScore.pPlayer[0], MAX_SCORE, pFile) != MAX_SCORE) {
		bzero(&sScore, sizeof sScore);
		fclose(pFile);
		return sScore;
	}
	fclose(pFile);
	return sScore;
}

Sint32 saveScore(void) {
	FILE *pFile;

	pFile = fopen(SCORE_FILE, "w");
	if (pFile == NULL) {
		fprintf(stderr, "Failed to save scores...\n");
		return -1;
	}
	if (fwrite(gVars.sScore.pPlayer, sizeof gVars.sScore.pPlayer[0], MAX_SCORE, pFile) != MAX_SCORE) {
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
	
	for (i = 0; i < MAX_SCORE; i++) {
		if (nScore > gVars.sScore.pPlayer[i].nScore)
			return i;
	}
	return -1;
}

void scoreAdd(Sint32 nPos, Uint32 nScore, char *name) {
	Sint32 i;

	if (nPos < 0 || nPos >= MAX_SCORE)
		return;

	for (i = MAX_SCORE - 1; i > nPos; i--)
		gVars.sScore.pPlayer[i] = gVars.sScore.pPlayer[i - 1];

	strncpy(gVars.sScore.pPlayer[nPos].pName, name, NAME_LEN);
	gVars.sScore.pPlayer[nPos].pName[NAME_LEN] = '\0';
	gVars.sScore.pPlayer[nPos].nScore = nScore;
}
