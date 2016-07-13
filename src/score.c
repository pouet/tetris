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

Sint32 saveScore(score_t *pScore) {
	FILE *pFile;

	pFile = fopen(SCORE_FILE, "w");
	if (pFile == NULL) {
		fprintf(stderr, "Failed to save scores...\n");
		return -1;
	}
	if (fwrite(pScore->pPlayer, sizeof pScore->pPlayer[0], MAX_SCORE, pFile) != MAX_SCORE) {
		fprintf(stderr, "Failed to save scores ...\n");
		fclose(pFile);
		pFile = fopen(SCORE_FILE, "w");
		fclose(pFile);
		return -1;
	}
	fclose(pFile);
	return 0;
}

Sint32 isHighScore(score_t *pScore) {
	(void)pScore;
}
