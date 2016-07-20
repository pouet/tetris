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
	SFX_PLAY_DROP,
	SFX_PLAY_GAMEOVER,
	SFX_PLAY_LEVELUP,
	SFX_PLAY_LINE,
	SFX_PLAY_MOVE,
	SFX_PLAY_ROTATE,
	SFX_PLAY_TETRIS,
	SFX_PLAY_TYPEA,
	SFX_PLAY_TYPEB,
	SFX_PLAY_TYPEC,
	SFX_PLAY_MARIO,
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
void sfxStopSounds(void);
void sfxStopMusic(void);

#endif
