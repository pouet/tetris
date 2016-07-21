#ifndef SCORE_H
#define SCORE_H

#include <SDL.h>

/* packer la structure pour lecture/ecriture du score */
#pragma pack(1)

/* ********************************* */
/* *          Constantes           * */
/* ********************************* */

#define SCORE_FILE "score.sc"
#define NAME_LEN 6
#define NB_SCORE 20

/* ********************************* */
/* *          Structures           * */
/* ********************************* */

struct player_s {
	char pName[NAME_LEN + 1];
	Uint32 nScore;
};

typedef struct score_s {
	struct player_s pPlayer[NB_SCORE];
} score_t;

/* ********************************* */
/* *          Prototypes           * */
/* ********************************* */

score_t loadScore(void);
Sint32 saveScore(void);

Sint32 isHighScore(Uint32 nScore);
void scoreAdd(Sint32 nPos, Uint32 nScore, char *name);

void scoreEncode(score_t *score);
void scoreDecode(score_t *score);

#endif
