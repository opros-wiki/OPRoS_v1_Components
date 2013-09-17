#ifndef _CNR_6DOFAnalyticInverseKinematicsComp_COMPONENT_H
#define _CNR_6DOFAnalyticInverseKinematicsComp_COMPONENT_H
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

class CNR_6DOFAnalyticInverseKinematicsComp: public Component
	,public IInverseKinematicsService
{
public:
	CNR_6DOFAnalyticInverseKinematicsComp();
	CNR_6DOFAnalyticInverseKinematicsComp(const std::string &compId);
	virtual ~CNR_6DOFAnalyticInverseKinematicsComp();
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
	vector<double> m_Joint;
	ObjectPosition m_Position;
	Property parameter;
	int error;
	//회전각도값에서 +- 360도를 해서 절대값이 작은 값을 출력한다. 
	double ASV_DEG(double val);	//Absolute Smallest value

};

#endif

