#ifndef	_SPEECH_H_
#define	_SPEECH_H_

#include "Device.h"

/*
enum SPEECH_MODE {
	SPEECH_TEXT_STREAM,
	SPEECH_TEXT_FILE,
	SPEECH_WAVE_STREAM,
	SPEECH_WAVE_FILE,
};
*/

#define	SPEECH_TEXT_STREAM	(0)
#define	SPEECH_TEXT_FILE	(1)
#define	SPEECH_WAVE_STREAM	(2)
#define	SPEECH_WAVE_FILE	(3)

namespace OPRoS
{

class Speech : public Device
{
public:
	Speech(void) { };
	virtual ~Speech(void) { };

public:
	virtual bool playSpeech(std::string speechData, int mode) = 0;
	virtual bool stopSpeech(void) = 0;
};

};


#endif	//	_SPEECH_H_