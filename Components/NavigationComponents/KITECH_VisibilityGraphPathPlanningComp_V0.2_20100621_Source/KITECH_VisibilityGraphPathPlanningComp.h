#ifndef _KITECH_VisibilityGraphPathPlanningComp_COMPONENT_H
#define _KITECH_VisibilityGraphPathPlanningComp_COMPONENT_H
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


#include "PathPlanningServiceProvided.h"
#include "GlobalMapServiceRequired.h"

/**
 *	KITECH_VisibilityGraphPathPlanningComp는 이동 로봇의 주행을 위한 전역 경로를 게획하는 컴포넌트이다.
 *	KITECH_VisibilityGraphPathPlanningComp는 전역 경로를 계획하는 컴포넌트로써 경로 계획을 위한 표준 인터페이스인 IPathPlanningCompService를 상속받아 구현된다.
 *	Visibility Graph 알고리즘을 사용하여 시작 위치에서 목적지 위치까지 경로를 계획한다.
 *	동적 라이브러리로 생성되며 GridBasedGlobalMapComp와 연동하여 사용된다.
 */
class KITECH_VisibilityGraphPathPlanningComp: public Component, public IPathPlanningService
{
protected:
// method for required
	GlobalMapServiceRequired *ptrGlobalMapService;

public:
	KITECH_VisibilityGraphPathPlanningComp();
	KITECH_VisibilityGraphPathPlanningComp(const std::string &compId);
	virtual ~KITECH_VisibilityGraphPathPlanningComp();
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
	 *	@return parameter 파라미터를 얻기 위한 포인터 변수<br>
	 */
	virtual Property GetParameter();

	virtual int GetError();

	/**
	 *	로봇의 현재 위치에서 목적지 위치까지 최단 거리의 경로를 생성하는 표준 함수이다.
	 *	@param startPosition 출발 위치.
	 *	@param endPoaition 도착 위치.
	 *	@param path 생성된 경로 데이터.
	 *	@return true - 경로 계획 성공<br>
	 *	        false - 경로 계획 실패<br>
	 */
	virtual vector<ObjectLocation> FindPath(ObjectLocation startPosition,ObjectLocation endPosition);

private:
	/**
	 *	파라미터를 저장하는 변수이다.
	 *	본 컴포넌트에서는 사용하지 않는다.
	 */
	Property parameter;

	int error;

	/**
	 *	경로 생성시 입력되는 시작점과 끝점이 장애물과 겹칠 때 장애물을 겹치지 않는 재일 가까운 빈 공간의 위치를 계산한다.
	 *	@param point 찾고자 하는 위치. 입력과 동시에 결과를 얻는 위치 변수
	 *	@return true - 위치 계산 성공<br>
	 *	        false - 위치 계산 실패<br>
	 */
	bool FindNearestPoint (ObjectLocation *point);

	/**
	 *	입력되는 시작 위치와 끝 위치와 함께 전역맵 데이터에서 모든 코너에 대한 위치를 찾아 저장한다.
	 *	@param sp 시작 위치
	 *	@param ep 끝 위치
	 *	@return void<br>
	 */
	void FindAllCorner (const ObjectLocation &sp, const ObjectLocation &ep);

	/**
	 *	시작 위치와 끝 위치와 찾은 모든 코너 위치에 대해 연결 가능한 모든 연결 정보를 추출한다.
	 *	@return void<br>
	 */
	int FindAllPossibleLink ();

	/**
	 *	모든 연결 정보를 이용해 시작위치에서 끝 위치까지 최단 거리를 연결하는 경로들을 계산한다.
	 *	@param ep 끝 위치
	 *	@return true - 최단 경로 계산 성공<br>
	 *	        false - 최단 계산 실패<br>
	 */
	bool SpreadToGoal (const ObjectLocation &ep);

	/**
	 *	계산된 최단 경로 위치를 정렬한다.
	 *	@param path 정렬된 최단 경로 데이터
	 *	@return void<br>
	 */
	void TraceShortestPath (deque<ObjectLocation> *path);
};

#endif

