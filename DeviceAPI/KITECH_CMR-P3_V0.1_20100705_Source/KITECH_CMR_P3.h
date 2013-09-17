#pragma once

#if defined(WIN32)
#include <Windows.h>
#else
#include <dlfcn.h>
#endif
#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include "WheelController.h"
#include "CAN.h"
#include "ServoActuator.h"

class KITECH_CMR_P3 : public WheelController
{
public:
	KITECH_CMR_P3 (void);
	virtual ~KITECH_CMR_P3 (void);

public:
	int Initialize(Property parameter);
	int Finalize(void);
	int Enable(void);
	int Disable(void);
	int SetParameter(Property parameter);
	int GetParameter(Property &parameter);

	int Move(double distance);
	int Rotate(double degree);
	int Drive(double forwardVelocity, double angularVelocity);
	int Stop(void);
	int EmergencyStop(void);
	int SetPosition(ObjectLocation position);
	int GetPosition(ObjectLocation &position);

private:
	Property parameter;
	WheelControllerProfile _profile;

	/**
	*	���� �ð��� Mobility ���� ������ ���� �������� ��Ÿ���� �����̴�.
	*/
	double leftWheelAnglePrev;
	/**
	*	���� �ð��� Mobility ������ ������ ���� �������� ��Ÿ���� �����̴�.
	*/
	double rightWheelAnglePrev;
	/**
	*	Mobility�� ������� ���� �̵��� �Ÿ��� ��Ÿ���� �����̴�.
	*/
	double currentForward;
	/**
	*	Mobility�� ������� ȸ���� ������ ��Ÿ���� �����̴�.
	*/
	double currentTurn;
	/**
	*	Mobility�� ������ ��ǥ �Ÿ��� ��Ÿ���� �����̴�.
	*/
	double targetForward;
	/**
	*	Mobility�� ȸ���� ��ǥ ������ ��Ÿ���� �����̴�.
	*/
	double targetTurn;

	/**
	*	Mobility�� ���� ��ġ x, y, theta�� ��Ÿ���� �����̴�.
	*/
	ObjectLocation position;
	/**
	*	Mobility�� ��ġ ���� x, y, theta�� ��Ÿ���� �����̴�.
	*/
	ObjectLocation variance;

	/**
	*	Mobility�� �����̰� �ִ����� ��Ÿ���� �����̴�.
	*/
	bool isRunning;
	/**
	*	Mobility�� �����ϱ� ���� ����� ��Ÿ���� �����̴�.
	*/
	int mobileCommand;

	bool UpdatePosition();

	long taskPeriod;
	void StartTask(long period);
	void StopTask();
	void DoTask();

	double _forwardVelocity;
	double _forwardAccel;
	double _centripetalAccel;
	void EstimateAcceleration (double &forwardVelocity, double &angularVelocity, double deltaTime);

	boost::thread *pThread;
	bool threadOn;
	void ThreadFunc();

#if defined(WIN32)
	HMODULE hOprosAPI;
#else
	void *hOprosAPI;
#endif
	ServoActuator *leftWheel, *rightWheel;

	int InitializeServoActuator(Property parameter);
	int FinalizeServoActuator(void);
};

/* Robin Parameter
WheelDiameter     : 0.255
AxleDistance      :  0.395
VarianceDistance  : 0.02
VarianceDirection : 1.0
SafeRadius        : 0.4
MaximumVelocity   : 0.5
Acceleration      : 0.5
 */