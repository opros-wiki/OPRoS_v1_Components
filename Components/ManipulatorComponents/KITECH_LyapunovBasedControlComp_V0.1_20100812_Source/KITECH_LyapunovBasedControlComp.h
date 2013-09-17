#ifndef _KITECH_LyapunovBasedControlComp_COMPONENT_H
#define _KITECH_LyapunovBasedControlComp_COMPONENT_H
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

#include "TrackingControlServiceProvided.h"
#include "LyapunovBasedControl.h"

class KITECH_LyapunovBasedControlComp: public Component
	,public ITrackingControlService
{
protected:
	Property parameter;
	int error;

	LyapunovBasedControl *_dynamics;

public:
	KITECH_LyapunovBasedControlComp();
	KITECH_LyapunovBasedControlComp(const std::string &compId);
	virtual ~KITECH_LyapunovBasedControlComp();
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
	virtual bool SetJointAcceleration(vector<double> jointAcceleration);
	virtual vector<double> GetJointAcceleration();
	virtual bool SetJointVelocity(vector<double> jointVelocity);
	virtual vector<double> GetJointVelocity();
	virtual bool SetJointPosition(vector<double> jointPosition);
	virtual vector<double> GetJointPosition();
	virtual bool SetDesiredJointAcceleration(vector<double> desiredJointAcceleration);
	virtual vector<double> GetDesiredJointAcceleration();
	virtual bool SetDesiredJointVelocity(vector<double> desiredJointVelocity);
	virtual vector<double> GetDesiredJointVelocity();
	virtual bool SetDesiredJointPosition(vector<double> desiredJointPosition);
	virtual vector<double> GetDesiredJointPosition();
	virtual vector<double> SloveTrackingControl();
};

#endif

