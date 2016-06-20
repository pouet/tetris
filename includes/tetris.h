#ifndef TETRIS_H
# define TETRIS_H

# include "SDL.h"

# define TITLE "Tetris"

enum {
	FPS = 60,
	FPS_DFLT = 1000 / FPS
};

enum {
	WIN_W = 1024,
	WIN_H = 768,
	N_TEXTURES
};

typedef struct {
	int			x;
	int			y;
}				t_point;

typedef struct {
	SDL_Texture		*tex;
	Uint32			*pixels;
	int				pitch;
	int				w;
	int				h;
}				t_texture;

typedef struct {
	SDL_Window		*win;
	SDL_Renderer	*ren;
	int				fullscreen;
	Uint32			*pixels;

	t_texture		tex[N_TEXTURES];
	t_texture		img;
	const Uint8		*keyb;

	int				ticks;
}				t_cont;

void	put_pixel(Uint32 *pix32, int x, int y, unsigned col);

#endif
