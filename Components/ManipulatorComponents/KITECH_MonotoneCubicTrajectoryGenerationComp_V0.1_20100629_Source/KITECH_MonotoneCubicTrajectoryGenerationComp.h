#ifndef _KITECH_MonotoneCubicTrajectoryGenerationComp_COMPONENT_H
#define _KITECH_MonotoneCubicTrajectoryGenerationComp_COMPONENT_H
/*
 *  Generated sources by OPRoS Component Generator (OCG V2)
 *   
 */
#include <Component.h>
#include <InputDataPort.h>
#include <OutputDataPort.h>
#include <InputEventPort.h>
#include <OutputEventPort.h>
#include <Event.h>
#include <OPRoSTypes.h>

#include "TrajectoryGenerationServiceProvided.h"

class KITECH_MonotoneCubicTrajectoryGenerationComp: public Component
	,public ITrajectoryGenerationService
{
protected:
	Property parameter;
	int error;
	double samplingTime;
	double monotonicity;

	vector< valarray<double> > acceleration;
	vector< valarray<double> > velocity;
	vector< valarray<double> > position;

public:
	KITECH_MonotoneCubicTrajectoryGenerationComp();
	KITECH_MonotoneCubicTrajectoryGenerationComp(const std::string &compId);
	virtual ~KITECH_MonotoneCubicTrajectoryGenerationComp();
	virtual void portSetup();

protected:
	virtual ReturnType onInitialize();
	virtual ReturnType onStart();
	virtual ReturnType onStop();
	virtual ReturnType onReset();
	virtual ReturnType onError();
	virtual ReturnType onRecover();
	virtual ReturnType onDestroy();

public:
	virtual ReturnType onEvent(Event *evt);
	virtual ReturnType onExecute();
	virtual ReturnType onUpdated();
	virtual ReturnType onPeriodChanged();

	virtual bool SetParameter(Property parameter);
	virtual Property GetParameter();
	virtual int GetError();
	virtual bool GenerateTrajectory(vector < valarray<double> > pathData);
	virtual vector< valarray<double> > GetAcceleration();
	virtual vector< valarray<double> > GetVelocity();
	virtual vector< valarray<double> > GetPosition();
};

#endif

