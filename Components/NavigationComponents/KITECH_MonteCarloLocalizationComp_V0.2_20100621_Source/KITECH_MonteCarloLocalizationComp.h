#ifndef _KITECH_MonteCarloLocalizationComp_COMPONENT_H
#define _KITECH_MonteCarloLocalizationComp_COMPONENT_H
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

#include "LocalizationServiceProvided.h"
#include "GlobalMapServiceRequired.h"

#include "../LaserScannerComp/LaserScannerServiceRequired.h"
#include "../WheelControllerComp/WheelControllerServiceRequired.h"

struct VirtualRobot {
	double			prob;
	ObjectLocation	pos;
};

// 개요
/**
*	KITECH_MonteCarloLocalizationComp는 이동 로봇의 주행을 위해 로봇의 현재 위치를 추정하는 컴포넌트이다.
*	KITECH_MonteCarloLocalizationComp는 레이저 스캐너 센서 기반으로 하는 로봇의 현재 위치를 추정하는 컴포넌트로써 
*	로봇의 현재 위치를 추정하기 위한 표준 인터페이스인 ILocalizationCompService를 상속받아 구현된다.
*	MonteCarlo 기반 Particle Filter 알고리즘을 사용한다.
*	동적 라이브러리로 생성되며 NavigationComponent에서 KITECH_VFHObstacleAvoidanceComp의 서비스 함수를 호출하여 사용한다.
*	KITECH_MonteCarloLocalizationComp는 레이저 스캐너 센서를 사용하고 이동 로봇의 위치 정보를 이용해 추정하기 때문에
*	이동 로봇의 전진 오차, 회전 오차와 레이저 스캐너 센서의 시작 스캔 각도, 종료 스캔 각도, 최소 측정 거리, 최대 측정거리
*	스캔 포인터 개수, 측정 오차, 그리고 이동 로봇에 장착되는 위치 정보를 알아야 한다.
*/
class KITECH_MonteCarloLocalizationComp: public Component, public ILocalizationService
{
protected:
// method for required
	GlobalMapServiceRequired		*ptrGlobalMapService;

	LaserScannerServiceRequired		*ptrLaserScannerService;
	WheelControllerServiceRequired	*ptrWheelControllerService;

public:
	KITECH_MonteCarloLocalizationComp();
	KITECH_MonteCarloLocalizationComp(const std::string &compId);
	virtual ~KITECH_MonteCarloLocalizationComp();
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
	*	@return 파라미터 변수<br>
	*/
	virtual Property GetParameter();

	virtual int GetError ();

	/**
	*	로봇의 위치를 설정하는 표준 함수이다.
	*	@param position 로봇의 위치
	*	@return void<br>
	*/
	virtual void SetPosition(ObjectLocation position);

	/**
	*	로봇의 위치를 추정하고 그 결과를 얻는 표준 함수이다.
	*	@return 추정된 로봇의 위치<br>
	*/
	virtual ObjectLocation Localize();

private:
	/**
	*	파라미터를 저장하는 변수이다.
	*	파라미터의 항목은 파티클의 개수와 이동 로봇의 전진 오차, 회전 오차와 레이저 스캐너 센서의 시작 스캔 각도, 종료 스캔 각도, 최소 측정 거리, 최대 측정거리
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
	*	이동 로봇의 전진 오차
	*/
	double varianceDistance;

	/**
	*	이동 로봇의 회전 오차
	*/
	double varianceDirection;

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
	*	레이저 스캐너 센서의 측정 오차
	*/
	double sensorVariance;

	/**
	*	레이저 스캐너 센서가 이동 로봇에 장착되는 위치
	*/
	ObjectLocation sensorPosition;

	/**
	*	로봇의 현재 위치
	*/
	ObjectLocation	currentPosition;

	/**
	*	로봇의 과거 위치
	*/
	ObjectLocation	positionPrev;

	/**
	*	추정된 로봇의 위치에 대한 오차
	*/
	ObjectLocation	variance;

	/**
	*	파티클의 최대 개수
	*/
	int maxParticles;

	/**
	*	파티클
	*/
	vector<VirtualRobot> particles;

	bool Predict(ObjectLocation position);
	bool Update(std::vector<double> sensorValue);

	/**
	*	레이저 스캐너 센서로 측정된 장애물과의 거리가 전역맵의 장애물과 Particle의 위치에서 매칭이 되는 확률을 계산한다.
	*	@param vr 파티클
	*	@param laserData[] 레이저 스캐너 센서의 측정된 데이터
	*	@return 매칭 확률<br>
	*/
	double GetProbability (VirtualRobot &vr, double laserData[]);

	/**
	*	파티클들의 확률 값을 이용해 파티클들을 재생성한다.
	*	@return void<br>
	*/
	void Resampling ();

	/**
	*	파티클들의 위치를 평균하여 이동 로봇의 위치를 계산한다.
	*	@return void<br>
	*/

	void StocasticPosition ();

	/**
	*	입력 위치에서 파티클들을 입력 반경 내에서 임의의 위치에 재생성한다.
	*	@param x 가로축 위치
	*	@param y 세로축 위치
	*	@param radius 반경
	*	@return void<br>
	*/
	void RandomizeAt (double x, double y, double radius);
};

#endif

