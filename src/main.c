#include <stdio.h>
#include "SDL.h"
#include "tetris.h"

void	exit_sdlerror(void) {
	printf("%s\n", SDL_GetError());
	exit(EXIT_FAILURE);
}

int		init_video(t_cont *cont) {
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		exit_sdlerror();
	cont->win = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, WIN_W, WIN_H, 0);
	if (cont->win == NULL)
		exit_sdlerror();
	cont->ren = SDL_CreateRenderer(cont->win, -1, SDL_RENDERER_ACCELERATED);
	if (cont->ren == NULL)
		exit_sdlerror();
	return (0);
}

void		copy_surface_to_texture(SDL_Texture *tex, SDL_Surface *bmp)
{
	SDL_Rect	r;
	void		*pixels;
	int			pitch;

	SDL_LockTexture(tex, NULL, &pixels, &pitch);
	for (r.y = 0; r.y < bmp->h; r.y++) {
		for (r.x = 0; r.x < bmp->w; r.x++) {
			*(Uint32 *)((char *)pixels + (r.y * pitch + r.x * 4)) =
				*(Uint32 *)((char *)bmp->pixels +
						(r.y * bmp->pitch + r.x * bmp->format->BytesPerPixel));
		}
	}
	SDL_UnlockTexture(tex);
}

SDL_Texture	*load_bmp(t_cont *cont, char *name) {
	SDL_Surface	*bmp;
	SDL_Texture	*tex;

	bmp = SDL_LoadBMP(name);
	if (bmp == NULL)
		exit_sdlerror();
	tex = SDL_CreateTexture(cont->ren, SDL_PIXELFORMAT_ARGB8888,
			SDL_TEXTUREACCESS_STREAMING, bmp->w, bmp->h);
	if (tex == NULL)
		exit_sdlerror();
	copy_surface_to_texture(tex, bmp);
	SDL_FreeSurface(bmp);
	return (tex);
}

void	quit_video(t_cont *cont) {
	SDL_DestroyRenderer(cont->ren);
	SDL_DestroyWindow(cont->win);
	SDL_Quit();
}

void	render_texture(t_cont *cont, SDL_Texture *tex, int x, int y) {
	SDL_Rect dst;

	dst.x = x;
	dst.y = y;
	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
//	SDL_RenderCopy(cont->ren, tex, NULL, &dst);
	SDL_RenderCopy(cont->ren, tex, NULL, NULL);
}

void	load_textures(t_cont *cont) {
	static char *name[N_TEXTURES] = {
		"textures"
	};
	int i;

	for (i = 0; i < N_TEXTURES; i++) {
		cont->tex[i].tex = load_bmp(cont, name[i]);
		SDL_QueryTexture(cont->tex[i].tex, NULL, NULL,
				&cont->tex[i].w, &cont->tex[i].h);
		if (SDL_LockTexture(cont->tex[i].tex, NULL,
					(void **)&cont->tex[i].pixels, &cont->tex[i].pitch) < 0)
			exit_sdlerror();
	}
}

void	init_var(t_cont *cont) {
	cont->ticks = SDL_GetTicks();
	cont->keyb = SDL_GetKeyboardState(NULL);
	cont->img.tex = SDL_CreateTexture(cont->ren, SDL_PIXELFORMAT_ARGB8888,
			SDL_TEXTUREACCESS_STREAMING, WIN_W, WIN_H);
	SDL_QueryTexture(cont->img.tex, NULL, NULL, &cont->img.w, &cont->img.h);
	load_textures(cont);
	cont->pixels = malloc(WIN_H * WIN_W * sizeof(Uint32));
}

void		framewait(t_cont *cont) {
	unsigned	now;

	while (1) {
		now = SDL_GetTicks() - cont->ticks;
		if (now >= FPS_DFLT)
			break ;
		SDL_Delay(3);
	}
	cont->ticks = SDL_GetTicks();
	cont->ticks++;
}

int		update_events(t_cont *cont) {
	SDL_Event ev;

	while (SDL_PollEvent(&ev)) {
		if (ev.type == SDL_QUIT)
			return (1);
	}
	return (0);
}

void	lock_textures(t_cont *cont) {
	if (SDL_LockTexture(cont->img.tex, NULL, (void **)&cont->img.pixels,
				&cont->img.pitch) < 0)
		exit_sdlerror();
}

void	unlock_textures(t_cont *cont) {
	SDL_UnlockTexture(cont->img.tex);
}

void	do_all(t_cont *cont) {
	if (cont->keyb[SDL_SCANCODE_U]) {
		if (cont->fullscreen)
			SDL_SetWindowFullscreen(cont->win, 0);
		else
			SDL_SetWindowFullscreen(cont->win, SDL_WINDOW_FULLSCREEN);
		cont->fullscreen = !cont->fullscreen;
	}
}

int		main_loop(t_cont *cont) {
	while (1) {
		if (update_events(cont) || cont->keyb[SDL_SCANCODE_ESCAPE])
			break ;

		do_all(cont);
		SDL_UpdateTexture(cont->img.tex, NULL, cont->pixels, cont->img.pitch);
		SDL_RenderCopy(cont->ren, cont->img.tex, NULL, NULL);
		SDL_RenderPresent(cont->ren);
		framewait(cont);
	}
	return (0);
}

int		main(void) {
	t_cont	cont;

	bzero(&cont, sizeof(cont));
	if (init_video(&cont) < 0)
		return (EXIT_FAILURE);
	init_var(&cont);
	main_loop(&cont);
	quit_video(&cont);
	return (0);
}
