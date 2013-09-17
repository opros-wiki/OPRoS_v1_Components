#ifndef _KITECH_VFHObstacleAvoidanceComp_COMPONENT_H
#define _KITECH_VFHObstacleAvoidanceComp_COMPONENT_H
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

#include "LocalMap.h"

#include "ObstacleAvoidanceServiceProvided.h"
#include "../LaserScannerComp/LaserScannerServiceRequired.h"


// 개요
/**
*	KITECH_VFHObstacleAvoidanceComp는 이동 로봇의 주행을 위해 동적 장애물을 회피하는 컴포넌트이다.
*	KITECH_VFHObstacleAvoidanceComp는 장애물 회피를 위한 컴포넌트로써 장애물 회피를 위한 표준 인터페이스인 IObstacleAvoidanceService를 상속받아 구현된다.
*	Vector field histogram 알고리즘과 레이저 스캐너 센서를 사용하여 동적 장애물 회피를 수행한다.
*	동적 라이브러리로 생성되며 NavigationComponent에서 KITECH_VFHObstacleAvoidanceComp의 서비스 함수를 사용한다.
*	KITECH_VFHObstacleAvoidanceComp는 레이저 스캐너 센서를 사용하고 이동 로봇의 주행 데이터인 전진속도, 회전속도를 계산하기 때문에
*	이동 로봇의 최대 속도, 가속도, 안전 반경 크기와 레이저 스캐너 센서의 시작 스캔 각도, 종료 스캔 각도, 최소 측정 거리, 최대 측정거리
*	스캔 포인터 개수, 그리고 이동 로봇에 장착되는 위치 정보를 알아야 한다.
*/
class KITECH_VFHObstacleAvoidanceComp: public Component, public IObstacleAvoidanceService
{
protected:
// method for required
	LaserScannerServiceRequired *ptrLaserScannerService;

public:
	KITECH_VFHObstacleAvoidanceComp();
	KITECH_VFHObstacleAvoidanceComp(const std::string &compId);
	virtual ~KITECH_VFHObstacleAvoidanceComp();
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

	/**
	*	파리미터를 설정하는 표준 함수이다.
	*	@param parameter 파라미터 변수.
	*	@return true - 파리미터 설정 성공<br>
	*			false - 파라미터 설정 실패<br>
	*/
	virtual bool SetParameter(Property parameter);

	/**
	*	파리미터를 얻는 표준 함수이다.
	*	@return 파리미터 데이터<br>
	*/
	virtual Property GetParameter();

	virtual int GetError();

	/**
	*	로봇의 위치를 설정한다.
	*	@param position 로봇의 위치
	*	@return void<br>
	*/
	virtual void SetPosition(ObjectLocation position);

	/**
	*	현재 위치에서 목적지 위치까지 레이저 스캐너 센서 데이터를 이용해 동적 장애물을 회피하며 이동하는 로봇의 전진 속도와 회전 속도를 계산하는 표준 함수이다.
	*	@param currentPosition 로봇의 현재 위치
	*	@param targetPosition 로봇의 목적지 위치
	*	@return 계산된 이동 로봇의 속도값<br>
	*/
	virtual WheelControlVelocity Avoid(ObjectLocation currentPosition, ObjectLocation targetPosition);

private:
	/**
	*	파라미터를 저장하는 변수이다.
	*	파라미터의 항목은 이동 로봇의 최대 속도, 가속도, 안전 반경 크기와 레이저 스캐너 센서의 시작 스캔 각도, 종료 스캔 각도, 최소 측정 거리, 최대 측정거리
	*	스캔 포인터 개수, 측정 오차, 그리고 이동 로봇에 장착되는 위치이다.
	*/
	Property parameter;

	int error;

	/**
	*	파라미터 변수로 부터 각 항목별로 데이터를 얻는다.
	*	@return true - 파리미터 얻기 성공<br>
	*			false - 파라미터 얻기 실패<br>
	*/
	bool LoadProperty ();

	/**
	*	이동 로봇의 최대 속도
	*/
	double maximumVelocity;

	/**
	*	이동 로봇의 가속도
	*/
	double acceleration;

	/**
	*	이동 로봇의 외형 크기로써 안전 반경에 대한 반지름
	*/
	double safeRadius;

	/**
	*	레이저 스캐너 센서의 스캔 시작 각도
	*/
	double startAngle;

	/**
	*	레이저 스캐너 센서의 스캔 끝 각도
	*/
	double endAngle;

	/**
	*	레이저 스캐너 센서의 최소 측정 거리
	*/
	double minRange;

	/**
	*	레이저 스캐너 센서의 최대 측정 거리
	*/
	double maxRange;

	/**
	*	레이저 스캐너 센서의 측정 포인터 개수
	*/
	int sensorCount;

	/**
	*	레이저 스캐너 센서가 이동 로봇에 장착되는 위치
	*/
	ObjectLocation sensorPosition;

	/**
	*	VFH 알고리즘에서 사용하는 로봇의 위치를 중심에서의 국부맵 클래스
	*/
	CLocalMap *localMap;

	/**
	*	VFH 알고리즘에서 사용하는 목적지 방향
	*/
	double targetDirection;

	/**
	*	VFH 알고리즘에서 사용하는 현재 위치에서 목적지까지의 거리
	*/
	double targetDistance;

	/**
	*	VFH 알고리즘에서 사용하는 로봇의 회전 각도
	*/
	double steerDirection;

	/**
	*	VFH 알고리즘에서 사용하는 로봇의 전진 속도
	*/
	double steerForwardVel;

	/**
	*	VFH 알고리즘에서 사용하는 로봇의 회전 속도
	*/
	double steerAngularVel;

	/**
	*	VFH 알고리즘에서 사용하는 폴라히스토그램 데이터
	*/
	double polarHistogram[360];

	/**
	*	로봇의 현재 위치
	*/
	ObjectLocation currentPosition;

	/**
	*	로봇의 목적지 위치
	*/
	ObjectLocation targetPosition;

	/**
	*	국부 맵에 저장된 장애물에 대해 폴라히스토그램을 생성한다.
	*	@return void<br>
	*/
	void MakeDirectionHistogram ();

	/**
	*	생성된 폴라히스토그램을 이용해 목적지를 향하면서 장애물을 회피하는 이동 로봇의 전진속도와 회전 속도를 계산한다.
	*	@param forwardVel 계산된 이동 로봇의 전진속도
	*	@param angularVel 계산된 이동 로봇의 회전속도
	*	@return void<br>
	*/
	void CalcDrivingVelocity (double *forwardVel, double *angularVel);
};

#endif

