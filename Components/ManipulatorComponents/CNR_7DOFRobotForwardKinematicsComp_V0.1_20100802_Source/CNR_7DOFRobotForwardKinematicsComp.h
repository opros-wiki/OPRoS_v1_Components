#ifndef _CNR_7DOFRobotForwardKinematicsComp_COMPONENT_H
#define _CNR_7DOFRobotForwardKinematicsComp_COMPONENT_H
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

#include "InverseKinematicsServiceProvided.h"

class CNR_7DOFRobotForwardKinematicsComp: public Component
	,public IInverseKinematicsService
{
public:
	CNR_7DOFRobotForwardKinematicsComp();
	CNR_7DOFRobotForwardKinematicsComp(const std::string &compId);
	virtual ~CNR_7DOFRobotForwardKinematicsComp();
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
	virtual bool SetJointPosition(vector<double> jointPosition);
	virtual vector<double> GetJointPosition();
	virtual bool SetDesiredPosition(ObjectPosition desiredPosition);
	virtual ObjectPosition GetCurrentPosition();

private:
	vector<double> m_joint;
	Property parameter;
	int error;
};

#endif

