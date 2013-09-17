#ifndef	_ENCODER_H_
#define	_ENCODER_H_

#include "Sensor.h"

class EncoderProfile : public SensorProfile
{
public:
	EncoderProfile(void)
	{
		linePerRevolution = 0.0;
		reductionRatio = 0.0;
	};
	virtual ~EncoderProfile(void) { };

public:
	double linePerRevolution;
	double reductionRatio;
};

class Encoder : public Sensor
{
public:
	Encoder(void) { };
	virtual ~Encoder(void) { };

public:
	virtual int GetEncoderData(vector<double> &encoderData) { return API_NOT_SUPPORTED; };
};


#endif	//	_ENCODER_H_
