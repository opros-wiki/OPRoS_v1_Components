#ifndef	_VOICERECOGNITION_H_
#define	_VOICERECOGNITION_H_

#include "OprosApi.h"

class VoiceRecognition : public OprosApi
{
public:
	VoiceRecognition(void) { };
	virtual ~VoiceRecognition(void) { };

public:
	virtual int GetResult(std::string *result) { return API_NOT_SUPPORTED; };
};

#endif	//	_SPEECH_H_
