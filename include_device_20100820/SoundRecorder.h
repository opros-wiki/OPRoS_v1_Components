#ifndef	_SOUND_RECORDER_H_
#define	_SOUND_RECORDER_H_

#include "OprosApi.h"

#define	SOUND_RECORDER_BUFFER	0
#define	SOUND_RECORDER_FILE		1

class SoundRecorder : public SoundRecorder
{
public:
	SoundRecorder(void) { };
	virtual ~SoundRecorder(void) { };

public:
	virtual int StartRecording(string soundData, int mode) { return API_NOT_SUPPORTED; };
	virtual int StopRecording(void) { return API_NOT_SUPPORTED; };
	virtual int GetRecordedData(vector<unsigned char> &recordedData) { return API_NOT_SUPPORTED; };
}; 

#endif	//	_SOUND_RECODER_H_
