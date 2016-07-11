#ifndef SFX_H
#define SFX_H

enum {
	SFX_FREQ = 44100,
	SFX_FORMAT = AUDIO_S16SYS,
	SFX_CHANNELS = 2,
	SFX_SAMPLES = 512
};

enum {
	SFX_PLAY_NONE,
	SFX_PLAY_THEME,
	SFX_PLAY_GAMESTART,
	SFX_PLAY_MAX
};

enum {
	SFX_REPEAT_OFF,
	SFX_REPEAT_ON
};

struct gSfxBuf_s {
	Uint8 *pData;
	int nLen;
	int nPos;
	int nRepeat;
	Uint8 nSfx;
};

extern struct gSfxBuf_s gSfxBuf[SFX_SAMPLES];
extern struct SDL_AudioCVT gpSound[SFX_PLAY_MAX];

Sint32 sfxInit(void);
void sfxPlaySound(Uint8 nSndNum, int nRepeat);
void sfxStopAllAudio(void);
void sfxPauseAudio(void);
void sfxPlayAudio(void);

#endif
