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
 *	KITECH_VisibilityGraphPathPlanningComp�� �̵� �κ��� ������ ���� ���� ��θ� ��ȹ�ϴ� ������Ʈ�̴�.
 *	KITECH_VisibilityGraphPathPlanningComp�� ���� ��θ� ��ȹ�ϴ� ������Ʈ�ν� ��� ��ȹ�� ���� ǥ�� �������̽��� IPathPlanningCompService�� ��ӹ޾� �����ȴ�.
 *	Visibility Graph �˰����� ����Ͽ� ���� ��ġ���� ������ ��ġ���� ��θ� ��ȹ�Ѵ�.
 *	���� ���̺귯���� �����Ǹ� GridBasedGlobalMapComp�� �����Ͽ� ���ȴ�.
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
	 *	�ĸ����͸� �����ϴ� ǥ�� �Լ��̴�.
	 *	@param parameter �Ķ���� ����.
	 *	@return true - �ĸ����� ���� ����<br>
	 *			false - �Ķ���� ���� ����<br>
	 */
	virtual bool SetParameter(Property parameter);

	/**
	 *	�ĸ����͸� ��� ǥ�� �Լ��̴�.
	 *	@return parameter �Ķ���͸� ��� ���� ������ ����<br>
	 */
	virtual Property GetParameter();

	virtual int GetError();

	/**
	 *	�κ��� ���� ��ġ���� ������ ��ġ���� �ִ� �Ÿ��� ��θ� �����ϴ� ǥ�� �Լ��̴�.
	 *	@param startPosition ��� ��ġ.
	 *	@param endPoaition ���� ��ġ.
	 *	@param path ������ ��� ������.
	 *	@return true - ��� ��ȹ ����<br>
	 *	        false - ��� ��ȹ ����<br>
	 */
	virtual vector<ObjectLocation> FindPath(ObjectLocation startPosition,ObjectLocation endPosition);

private:
	/**
	 *	�Ķ���͸� �����ϴ� �����̴�.
	 *	�� ������Ʈ������ ������� �ʴ´�.
	 */
	Property parameter;

	int error;

	/**
	 *	��� ������ �ԷµǴ� �������� ������ ��ֹ��� ��ĥ �� ��ֹ��� ��ġ�� �ʴ� ���� ����� �� ������ ��ġ�� ����Ѵ�.
	 *	@param point ã���� �ϴ� ��ġ. �Է°� ���ÿ� ����� ��� ��ġ ����
	 *	@return true - ��ġ ��� ����<br>
	 *	        false - ��ġ ��� ����<br>
	 */
	bool FindNearestPoint (ObjectLocation *point);

	/**
	 *	�ԷµǴ� ���� ��ġ�� �� ��ġ�� �Բ� ������ �����Ϳ��� ��� �ڳʿ� ���� ��ġ�� ã�� �����Ѵ�.
	 *	@param sp ���� ��ġ
	 *	@param ep �� ��ġ
	 *	@return void<br>
	 */
	void FindAllCorner (const ObjectLocation &sp, const ObjectLocation &ep);

	/**
	 *	���� ��ġ�� �� ��ġ�� ã�� ��� �ڳ� ��ġ�� ���� ���� ������ ��� ���� ������ �����Ѵ�.
	 *	@return void<br>
	 */
	int FindAllPossibleLink ();

	/**
	 *	��� ���� ������ �̿��� ������ġ���� �� ��ġ���� �ִ� �Ÿ��� �����ϴ� ��ε��� ����Ѵ�.
	 *	@param ep �� ��ġ
	 *	@return true - �ִ� ��� ��� ����<br>
	 *	        false - �ִ� ��� ����<br>
	 */
	bool SpreadToGoal (const ObjectLocation &ep);

	/**
	 *	���� �ִ� ��� ��ġ�� �����Ѵ�.
	 *	@param path ���ĵ� �ִ� ��� ������
	 *	@return void<br>
	 */
	void TraceShortestPath (deque<ObjectLocation> *path);
};

#endif

