#ifndef	_SOUND_PLAYER_H_
#define	_SOUND_PLAYER_H_

#include "OprosApi.h"

#define	SOUND_PLAYER_TEXT_STREAM	0
#define	SOUND_PLAYER_TEXT_FILE		1
#define	SOUND_PLAYER_WAVE_STREAM	2
#define	SOUND_PLAYER_WAVE_FILE		3

class SoundPlayer : public OprosApi
{
public:
	SoundPlayer(void) { };
	virtual ~SoundPlayer(void) { };

public:
	virtual int Play(string soundData, int mode) { return API_NOT_SUPPORTED; };
	virtual int Stop(void) { return API_NOT_SUPPORTED; };
};

#endif	//	_SOUND_PLAYER_H_
