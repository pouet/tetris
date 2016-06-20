#include "tetris.h"

void	put_pixel(Uint32 *pix32, int x, int y, unsigned col)
{
	if (x < 0 || x >= WIN_W || y < 0 || y >= WIN_H)
		return;
	pix32[y * WIN_W + x] = col;
}
