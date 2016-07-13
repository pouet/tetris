#ifndef SCORE_H
#define SCORE_H

#include "SDL.h"

#define SCORE_FILE "score.sc"
#define NAME_LEN 15
#define MAX_SCORE 10

#pragma pack(1)

struct player_s {
	char pName[NAME_LEN + 1];
	Uint32 nScore;
};

typedef struct score_s {
	struct player_s pPlayer[MAX_SCORE];
} score_t;

score_t loadScore(void);
Sint32 saveScore(score_t *pScore);

#endif
