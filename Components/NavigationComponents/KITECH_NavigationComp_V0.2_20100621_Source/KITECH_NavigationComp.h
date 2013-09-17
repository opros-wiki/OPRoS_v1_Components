#ifndef _KITECH_NavigationComp_COMPONENT_H
#define _KITECH_NavigationComp_COMPONENT_H
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

#include "OprosLock.h"
#include "NavigationServiceProvided.h"
#include "GlobalMapServiceRequired.h"
#include "PathPlanningServiceRequired.h"
#include "LocalizationServiceRequired.h"
#include "ObstacleAvoidanceServiceRequired.h"

#include "../LaserScannerComp/LaserScannerServiceRequired.h"
#include "../WheelControllerComp/WheelControllerServiceRequired.h"

#ifdef	WIN32
#include "Dialog/NavigationDlg.h"
#endif


// 개요
/**
*	KITECH_NavigationComp는 이동 로봇의 주행을 위한 컴포넌트이다.
*	KITECH_NavigationComp는 이동 로봇의 컴포넌트로써 주행을 위한 표준 인터페이스인 INavigationService를 상속받아 구현된다.
*	동적 라이브러리로 생성되며 IGlobalMapService를 상속받아 구현된 전역맵 컴포넌트, 
*	ILocalizationService를 상속받아 구현된 위치 추정 컴포넌트, IPathPlanningService를 상속받아 구현된 경로계획 컴폰넌트,
*	IObstacleAvoidanceService를 상속받아 구현된 장애물 회피 컴포넌트, IWheelControllerCompService를 상속받아 구현된 휠제어 컴포넌트,
*	ILaserScannerCompService를 상속받아 구현된 레이저스캐너 컴포넌트등 총 6개의 컴포넌트들과 연결되어 사용된다.
*/
class KITECH_NavigationComp: public Component, public INavigationService
{
protected:
// method for required
	GlobalMapServiceRequired			*ptrGlobalMapService;
	PathPlanningServiceRequired			*ptrPathPlanningService;
	LocalizationServiceRequired			*ptrLocalizationService;
	ObstacleAvoidanceServiceRequired	*ptrObstacleAvoidanceService;

	LaserScannerServiceRequired			*ptrLaserScannerService;
	WheelControllerServiceRequired		*ptrWheelControllerService;

public:
	KITECH_NavigationComp();
	KITECH_NavigationComp(const std::string &compId);
	virtual ~KITECH_NavigationComp();
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
	*	@param parameter 파라미터를 얻기 위한 포인터 변수.
	*	@return true - 파리미터 얻기 성공<br>
	*			false - 파라미터 얻기 실패<br>
	*/
	virtual Property GetParameter();

	virtual int GetError();

	/**
	*	로봇의 위치를 설정하는 표준 함수이다.
	*	@param position 로봇의 위치
	*	@return void<br>
	*/
	virtual void SetPosition(ObjectLocation position);

	/**
	*	로봇의 위치를 얻는 표준 함수이다.
	*	@param position 로봇의 위치
	*	@return void<br>
	*/
	virtual ObjectLocation GetPosition();

	/**
	*	이동 로봇을 목적지로 주행을 시작하는 표준 함수이다.
	*	@param targetPosition 목적지 위치
	*	@return true - 주행 시작 성공<br>
	*			false - 주행 시작 실패<br>
	*/
	virtual bool NavigationTo(ObjectLocation targetPosition);

	/**
	*	이동 로봇을 입력 거리만큼 직진시키는 표준 함수이다.
	*	@param distance 직진 거리(단위:m)
	*	@return true - 이동 성공<br>
	*			false - 이동 실패<br>
	*/
	virtual bool Move(double distance);

	/**
	*	이동 로봇을 입력 각도만큼 회전시키는 표준 함수이다.
	*	@param degree 회전 각도(단위:도)
	*	@return true - 이동 성공<br>
	*			false - 이동 실패<br>
	*/
	virtual bool Rotate(double degree);

	/**
	*	동작중인 이동 로봇을 멈추는 표준 함수이다.
	*	@return void<br>
	*/
	virtual void AbortNavigation();

	/**
	*	이동 로봇이 주행 중인지를 판단하는 표준 함수이다.
	*	@return true - 주행 중인 상태<br>
	*	        false -멈춘 상태<br> 
	*/
	virtual bool IsNavigationOngoing();

#ifdef	WIN32
	CNavigationDlg *navigationDlg;
#endif

#ifdef USE_GUI
public:
	Property gridBasedGlobalMapParameter;
	std::string mapFile;

	ObjectLocation laserScannerPos;
	double laserScannerStartAngle;
	double laserScannerEndAngle;

	vector<ObjectLocation> FindPath(ObjectLocation startPos, ObjectLocation endPos);
#else
private:
#endif
	/**
	*	파라미터를 저장하는 변수이다.
	*	파라미터의 항목은 이동 로봇의 초기 위치이다.
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
	*	레이저 스캐너 센서 컴포넌트의 파라미터를 저장하는 변수이다.
	*/
	Property laserScannerParameter;

	/**
	*	레이저 스캐너 센서의 측정된 데이터를 저장하는 변수이다.
	*/
	std::vector<double> laserData;

	/**
	*	레이저 스캐너 센서의 측정 포인터 개수를 나타내는 변수이다.
	*/
	int laserScannerCount;

	/**
	*	휠제어 컴포넌트의 파라미터를 저장하는 변수이다.
	*/
	Property wheelControllerParameter;

	/**
	*	이동 로봇의 안전 반경을 나타내는 변수이다.
	*/
	double mobilitySafeRadius;

	/**
	*	주행 처리중 중복 처리를 막기 위한 변수이다.
	*/
	OprosLock lock;

	/**
	*	주행 처리의 단계를 나타내는 변수이다.
	*/
	int navigationStep;

	/**
	*	주행을 처리하는 함수이다.
	*/
	void DoTask ();

	/**
	*	이동 로봇의 현재 위치를 나타내는 변수이다.
	*/
	ObjectLocation currentPosition;

	/**
	*	이동 로봇의 목적지 위치를 나타내는 변수이다.
	*/
	ObjectLocation targetPosition;

	/**
	*	이동 로봇의 목적지 위치까지 중간 경로 위치를 나타내는 변수이다.
	*/
	ObjectLocation subTargetPosition;

	/**
	*	이동 로봇의 경로 위치를 나타내는 변수이다.
	*/
	vector<ObjectLocation> path;
};

#ifdef USE_GUI
extern KITECH_NavigationComp *naviComp;
#endif

#endif

