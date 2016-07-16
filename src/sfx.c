#include <stdlib.h>
#include <string.h>
#include "SDL.h"
#include "tetris.h"
#include "sfx.h"

SDL_AudioCVT gpSound[SFX_PLAY_MAX];

SDL_AudioSpec gObtained;
struct gSfxBuf_s gSfxBuf[SFX_SAMPLES];

void sfxPlaySound(Uint8 nSndNum, int nRepeat) {
	int i;

	if (gOpts.nSfxSound == 0 && nSndNum <= SFX_PLAY_TETRIS)
		return;
	else if (gOpts.nSfxMusic == 0 && nSndNum >= SFX_PLAY_TYPEA)
		return;

	for (i = 0; i < SFX_SAMPLES; i++) {
		if (gSfxBuf[i].nSfx == SFX_PLAY_NONE) {
			SDL_LockAudio();
			gSfxBuf[i].nPos = 0;
			gSfxBuf[i].nSfx = nSndNum;
			gSfxBuf[i].nLen = gpSound[gSfxBuf[i].nSfx].len_cvt;
			gSfxBuf[i].pData = gpSound[gSfxBuf[i].nSfx].buf;
			gSfxBuf[i].nRepeat = nRepeat;
			SDL_UnlockAudio();
			return;
		}
	}
}

void sfxMixAudio(void *data, Uint8 *stream, int len) {
	int nLenToCopy;
	int nLen;
	int i, j;

	(void)data;

	bzero(stream, len);

	for (i = 0; i < SFX_SAMPLES; i++) {
		if (gSfxBuf[i].nSfx != SFX_PLAY_NONE) {
			nLen = gSfxBuf[i].nLen;
			nLenToCopy = nLen - gSfxBuf[i].nPos > len ? len : nLen - gSfxBuf[i].nPos;
			for (j = 0; j < nLenToCopy; j++)
				stream[j] += *(gSfxBuf[i].pData + gSfxBuf[i].nPos + j);
			gSfxBuf[i].nPos += nLenToCopy;
			if (gSfxBuf[i].nPos >= gSfxBuf[i].nLen) {
				if (gSfxBuf[i].nRepeat == SFX_REPEAT_ON)
					gSfxBuf[i].nPos = 0;
				else
					gSfxBuf[i].nSfx = SFX_PLAY_NONE;
			}
		}
	}
}

SDL_AudioCVT loadWAV(char *file) {
	SDL_AudioSpec sndFile;
	SDL_AudioCVT cvt;
	Uint8 *pSndData;
	Uint32 nSndLen;

	if (SDL_LoadWAV(file, &sndFile, &pSndData, &nSndLen) == NULL) {
		fprintf(stderr, "SDL_LoadWAV: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	if (SDL_BuildAudioCVT(&cvt, sndFile.format, sndFile.channels, sndFile.freq,
				gObtained.format, gObtained.channels, gObtained.freq) < 0) {
		fprintf(stderr, "SDL_BuildAudioCVT: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	cvt.buf = malloc(nSndLen * cvt.len_mult);
	if (cvt.buf == NULL)
		exit(EXIT_FAILURE);
	cvt.len = nSndLen;
	memcpy(cvt.buf, pSndData, nSndLen);
	if (SDL_ConvertAudio(&cvt) < 0) {
		fprintf(stderr, "SDL_ConvertAudio: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	SDL_FreeWAV(pSndData);
	return cvt;
}

Sint32 sfxInit(void) {
	SDL_AudioSpec desired;
	char *pFiles[SFX_PLAY_MAX] = {
		"",
		"sfx/drop.wav",
		"sfx/gameover.wav",
		"sfx/levelup.wav",
		"sfx/line.wav",
		"sfx/move.wav",
		"sfx/rotate.wav",
		"sfx/tetris.wav",
		"sfx/typea.wav",
		"sfx/typeb.wav",
		"sfx/typec.wav",
		"sfx/typeawesome.wav",
	};
	int i;

	memset(&desired, 0, sizeof desired);
	desired.freq = SFX_FREQ;
	desired.format = SFX_FORMAT;
	desired.channels = SFX_CHANNELS;
	desired.samples = SFX_SAMPLES;
	desired.callback = sfxMixAudio;
	desired.userdata = NULL;

	if (SDL_OpenAudio(&desired, &gObtained) != 0) {
		fprintf(stderr, "SDL_OpenAudio: %s\n", SDL_GetError());
		return -1;
	}

	for (i = 1; i < SFX_PLAY_MAX; i++)
		gpSound[i] = loadWAV(pFiles[i]);

	/* Let's do it !!! */
	SDL_PauseAudio(0);
//	SDL_PauseAudio(1);

	return 0;
}

void sfxStopAllAudio(void) {
	int i;

	SDL_LockAudio();
	for (i = 0; i < SFX_SAMPLES; i++) {
		gSfxBuf[i].nSfx = SFX_PLAY_NONE;
		gSfxBuf[i].nLen = 0;
		gSfxBuf[i].nPos = 0;
	}
	SDL_UnlockAudio();
}

void sfxPauseAudio(void) {
	SDL_PauseAudio(1);
}

void sfxPlayAudio(void) {
	SDL_PauseAudio(0);
}
