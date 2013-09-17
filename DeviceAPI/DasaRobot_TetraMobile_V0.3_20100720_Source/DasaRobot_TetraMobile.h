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
	*	Mobile의 양쪽 바퀴를 서보오프시킨다.
	*	@return true - 명령 수행 성공.<br>
	*			false - 명령 수행 실패.<br>	
	*/
	bool ServoOff ();
	/**
	*	Mobile의 양쪽 바퀴를 속도제어한다.
	*	@param leftVelocity 왼쪽 바퀴 속도
	*	@param rightVelocity 오른쪽 바퀴 속도
	*	@return true - 명령 수행 성공.<br>
	*			false - 명령 수행 실패.<br>	
	*/
	bool VelocityControl (int leftVelocity, int rightVelocity);
	/**
	*	Mobile의 양쪽 바퀴 엔코더값을 가져온다.
	*	@param leftEncoder 왼쪽 바퀴 엔코더값
	*	@param rightEncoder 오른쪽 바퀴 엔코더값
	*	@return true - 명령 수행 성공.<br>
	*			false - 명령 수행 실패.<br>	
	*/
	bool ReadEncoder(long *leftEncoder, long *rightEncoder);
	/**
	*	Mobile의 위치를 가져온다.
	*	@param x x축 위치
	*	@param y y축 위치
	*	@param th 회전축 각도
	*	@return true - 명령 수행 성공.<br>
	*			false - 명령 수행 실패.<br>	
	*/
	bool ReadPosition (int *x, int *y, int *th);
	/**
	*	Mobile의 위치를 설정한다.
	*	@param x x축 위치
	*	@param y y축 위치
	*	@param th 회전축 각도
	*	@return true - 명령 수행 성공.<br>
	*			false - 명령 수행 실패.<br>	
	*/
	bool ChangePosition (int x, int y, int th);
	/**
	*	Mobile의 파라미터를 설정한다.
	*	@param index 파리미터 인덱스
	*	@param parameter 파리미터 값
	*	@return true - 명령 수행 성공.<br>
	*			false - 명령 수행 실패.<br>	
	*/
	bool SetParameter (int index, int parameter);
	/**
	*	Mobile의 파라미터를 가져온다.
	*	@param index 파리미터 인덱스
	*	@param parameter 파리미터 값
	*	@return true - 명령 수행 성공.<br>
	*			false - 명령 수행 실패.<br>	
	*/
	bool GetParameter (int index, int *parameter);
	/**
	*	Mobile를 속도 제어 모드로 변경시킨다.
	*	@return true - 명령 수행 성공.<br>
	*			false - 명령 수행 실패.<br>	
	*/
	bool SetVelocityControlMode (void);
	/**
	*	Mobile를 위치 제어 모드로 변경시킨다.
	*	@return true - 명령 수행 성공.<br>
	*			false - 명령 수행 실패.<br>	
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
	*	이전 시간의 Mobility 왼쪽 바퀴의 엔코더 값을 나타내는 변수이다.
	*/
	long leftWheelEncoderPrev;
	/**
	*	이전 시간의 Mobility 왼쪽 바퀴의 엔코더 값을 나타내는 변수이다.
	*/
	long rightWheelEncoderPrev;
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