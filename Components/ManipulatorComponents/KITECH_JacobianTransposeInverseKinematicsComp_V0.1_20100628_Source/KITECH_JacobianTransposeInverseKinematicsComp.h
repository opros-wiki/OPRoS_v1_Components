#ifndef _KITECH_JacobianTransposeInverseKinematicsComp_COMPONENT_H
#define _KITECH_JacobianTransposeInverseKinematicsComp_COMPONENT_H
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
#include "JacobianTranspose.h"

class KITECH_JacobianTransposeInverseKinematicsComp : public Component, public IInverseKinematicsService
{
protected:
	Property parameter;
	int error;

	JacobianTranspose *jacobianTranspose;

public:
	KITECH_JacobianTransposeInverseKinematicsComp();
	KITECH_JacobianTransposeInverseKinematicsComp(const std::string &compId);
	virtual ~KITECH_JacobianTransposeInverseKinematicsComp();
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
};

#endif

