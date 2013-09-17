#ifndef _DASAROBOT_TETRAMOBILE_H_
#define _DASAROBOT_TETRAMOBILE_H_

#if defined(WIN32)
#include <Windows.h>
#else
#include <dlfcn.h>
#endif
#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "WheelController.h"


class DasaRobot_TetraMobile : public WheelController
{
public:
	DasaRobot_TetraMobile (void);
	virtual ~DasaRobot_TetraMobile (void);

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

	bool ServoOn ();
	/**
	*	Mobile�� ���� ������ ����������Ų��.
	*	@return true - ��� ���� ����.<br>
	*			false - ��� ���� ����.<br>	
	*/
	bool ServoOff ();
	/**
	*	Mobile�� ���� ������ �ӵ������Ѵ�.
	*	@param leftVelocity ���� ���� �ӵ�
	*	@param rightVelocity ������ ���� �ӵ�
	*	@return true - ��� ���� ����.<br>
	*			false - ��� ���� ����.<br>	
	*/
	bool VelocityControl (int leftVelocity, int rightVelocity);
	/**
	*	Mobile�� ���� ���� ���ڴ����� �����´�.
	*	@param leftEncoder ���� ���� ���ڴ���
	*	@param rightEncoder ������ ���� ���ڴ���
	*	@return true - ��� ���� ����.<br>
	*			false - ��� ���� ����.<br>	
	*/
	bool ReadEncoder(long *leftEncoder, long *rightEncoder);
	/**
	*	Mobile�� ��ġ�� �����´�.
	*	@param x x�� ��ġ
	*	@param y y�� ��ġ
	*	@param th ȸ���� ����
	*	@return true - ��� ���� ����.<br>
	*			false - ��� ���� ����.<br>	
	*/
	bool ReadPosition (int *x, int *y, int *th);
	/**
	*	Mobile�� ��ġ�� �����Ѵ�.
	*	@param x x�� ��ġ
	*	@param y y�� ��ġ
	*	@param th ȸ���� ����
	*	@return true - ��� ���� ����.<br>
	*			false - ��� ���� ����.<br>	
	*/
	bool ChangePosition (int x, int y, int th);
	/**
	*	Mobile�� �Ķ���͸� �����Ѵ�.
	*	@param index �ĸ����� �ε���
	*	@param parameter �ĸ����� ��
	*	@return true - ��� ���� ����.<br>
	*			false - ��� ���� ����.<br>	
	*/
	bool SetParameter (int index, int parameter);
	/**
	*	Mobile�� �Ķ���͸� �����´�.
	*	@param index �ĸ����� �ε���
	*	@param parameter �ĸ����� ��
	*	@return true - ��� ���� ����.<br>
	*			false - ��� ���� ����.<br>	
	*/
	bool GetParameter (int index, int *parameter);
	/**
	*	Mobile�� �ӵ� ���� ���� �����Ų��.
	*	@return true - ��� ���� ����.<br>
	*			false - ��� ���� ����.<br>	
	*/
	bool SetVelocityControlMode (void);
	/**
	*	Mobile�� ��ġ ���� ���� �����Ų��.
	*	@return true - ��� ���� ����.<br>
	*			false - ��� ���� ����.<br>	
	*/
	bool SetPositionControlMode (void);

	Property parameter;
	WheelControllerProfile profile;

	//double wheelDiameter;
	//double axleDistance;
	//double varianceDistance;
	//double varianceDirection;
	//double safeRadius;
	//double maximumVelocity;
	//double acceleration;

	std::string robotIP;
	int robotPort;

	/**
	*	���� �ð��� Mobility ���� ������ ���ڴ� ���� ��Ÿ���� �����̴�.
	*/
	long leftWheelEncoderPrev;
	/**
	*	���� �ð��� Mobility ���� ������ ���ڴ� ���� ��Ÿ���� �����̴�.
	*/
	long rightWheelEncoderPrev;
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


#if defined(WIN32)
	HMODULE hOprosAPI;
#endif

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
};

#endif