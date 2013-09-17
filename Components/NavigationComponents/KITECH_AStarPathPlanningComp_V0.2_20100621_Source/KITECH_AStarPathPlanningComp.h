
#ifndef _KITECH_AStarPathPlanningComp_COMPONENT_H
#define _KITECH_AStarPathPlanningComp_COMPONENT_H
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
#include "priority_queue.h"
#include "stack.h"

// 개요
/**
 *	KITECH_AStarPathPlanningComp는 이동 로봇의 주행을 위한 전역 경로를 게획하는 컴포넌트이다.
 *	KITECH_AStarPathPlanningComp는 전역 경로를 계획하는 컴포넌트로써 경로 계획을 위한 표준 인터페이스인 IPathPlanningCompService를 상속받아 구현된다.
 *	A-Star 알고리즘을 사용하여 시작 위치에서 목적지 위치까지 경로를 계획한다.
 *	동적 라이브러리로 생성되며 GridBasedGlobalMapComp와 연동하여 사용된다.
 */
class KITECH_AStarPathPlanningComp: public Component, public IPathPlanningService
{
protected:
// method for required
	GlobalMapServiceRequired *ptrGlobalMapService;

public:
	KITECH_AStarPathPlanningComp();
	KITECH_AStarPathPlanningComp(const std::string &compId);
	virtual ~KITECH_AStarPathPlanningComp();
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
	 *	우선순위를 가지는 큐 변수
	 */
	priority_queue	openList;

	/**
	 *	스택 변수
	 */
	stack			closeList;

	/**
	 *	A-Star 알고리즘에서 전역맵 데이터를 가져올 때 전역맵의 크기를 변경하기 위한 변수
	 *	전역맵 데이터는 높은 해상도를 가지고 있기 때문에 A-Star 알고리즘의 계산속도를 빠르게 하기 위해
	 *	전역맵 데이터의 해상도를 줄여서 사용한다.
	 */
	int				scalefactor;

	/**
	 *	입력되는 두 위치의 거리를 계산한다.
	 *	@param p1 한 점의 위치
	 *	@param p2 다른 한 점의 위치
	 *	@return 두 점의 거리
	 */
	double CalcDistance(point p1, point p2);

	/**
	 *	A-Star를 이용해 계산된 경로를 정렬하여 추출한다.
	 *	@param path A-Star 알고리즘으로부터 계산된 경로 데이터
	 *	@return void
	 */
	void ExtractPath(stack *path);

	/**
	 *	경로 생성시 입력되는 시작점과 끝점이 장애물과 겹칠 때 장애물을 겹치지 않는 재일 가까운 빈 공간의 위치를 계산한다.
	 *	@param point 찾고자 하는 위치. 입력과 동시에 결과를 얻는 위치 변수
	 *	@return true - 위치 계산 성공<br>
	 *	        false - 위치 계산 실패<br>
	 */
	bool FindNearestPoint (ObjectLocation *point);
};

#endif

