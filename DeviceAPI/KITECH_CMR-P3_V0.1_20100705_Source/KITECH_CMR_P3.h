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
	*	이전 시간의 Mobility 왼쪽 바퀴의 누적 각도값을 나타내는 변수이다.
	*/
	double leftWheelAnglePrev;
	/**
	*	이전 시간의 Mobility 오른쪽 바퀴의 누적 각도값을 나타내는 변수이다.
	*/
	double rightWheelAnglePrev;
	/**
	*	Mobility가 현재까지 직진 이동한 거리를 나타내는 변수이다.
	*/
	double currentForward;
	/**
	*	Mobility가 현재까지 회전한 각도를 나타내는 변수이다.
	*/
	double currentTurn;
	/**
	*	Mobility가 직진할 목표 거리를 나타내는 변수이다.
	*/
	double targetForward;
	/**
	*	Mobility가 회전할 목표 각도를 나타내는 변수이다.
	*/
	double targetTurn;

	/**
	*	Mobility의 현재 위치 x, y, theta를 나타내는 변수이다.
	*/
	ObjectLocation position;
	/**
	*	Mobility의 위치 에러 x, y, theta를 나타내는 변수이다.
	*/
	ObjectLocation variance;

	/**
	*	Mobility가 움직이고 있는지를 나타내는 변수이다.
	*/
	bool isRunning;
	/**
	*	Mobility를 제어하기 위한 명령을 나타내는 변수이다.
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