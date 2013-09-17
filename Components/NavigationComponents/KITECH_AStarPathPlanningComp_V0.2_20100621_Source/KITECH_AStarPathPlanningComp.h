
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

// ����
/**
 *	KITECH_AStarPathPlanningComp�� �̵� �κ��� ������ ���� ���� ��θ� ��ȹ�ϴ� ������Ʈ�̴�.
 *	KITECH_AStarPathPlanningComp�� ���� ��θ� ��ȹ�ϴ� ������Ʈ�ν� ��� ��ȹ�� ���� ǥ�� �������̽��� IPathPlanningCompService�� ��ӹ޾� �����ȴ�.
 *	A-Star �˰����� ����Ͽ� ���� ��ġ���� ������ ��ġ���� ��θ� ��ȹ�Ѵ�.
 *	���� ���̺귯���� �����Ǹ� GridBasedGlobalMapComp�� �����Ͽ� ���ȴ�.
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
	 *	�ĸ����͸� �����ϴ� ǥ�� �Լ��̴�.
	 *	@param parameter �Ķ���� ����.
	 *	@return true - �ĸ����� ���� ����<br>
	 *			false - �Ķ���� ���� ����<br>
	 */
	virtual bool SetParameter(Property parameter);

	/**
	 *	�ĸ����͸� ��� ǥ�� �Լ��̴�.
	 *	@param parameter �Ķ���͸� ��� ���� ������ ����.
	 *	@return true - �ĸ����� ��� ����<br>
	 *			false - �Ķ���� ��� ����<br>
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
	 *	�켱������ ������ ť ����
	 */
	priority_queue	openList;

	/**
	 *	���� ����
	 */
	stack			closeList;

	/**
	 *	A-Star �˰��򿡼� ������ �����͸� ������ �� �������� ũ�⸦ �����ϱ� ���� ����
	 *	������ �����ʹ� ���� �ػ󵵸� ������ �ֱ� ������ A-Star �˰����� ���ӵ��� ������ �ϱ� ����
	 *	������ �������� �ػ󵵸� �ٿ��� ����Ѵ�.
	 */
	int				scalefactor;

	/**
	 *	�ԷµǴ� �� ��ġ�� �Ÿ��� ����Ѵ�.
	 *	@param p1 �� ���� ��ġ
	 *	@param p2 �ٸ� �� ���� ��ġ
	 *	@return �� ���� �Ÿ�
	 */
	double CalcDistance(point p1, point p2);

	/**
	 *	A-Star�� �̿��� ���� ��θ� �����Ͽ� �����Ѵ�.
	 *	@param path A-Star �˰������κ��� ���� ��� ������
	 *	@return void
	 */
	void ExtractPath(stack *path);

	/**
	 *	��� ������ �ԷµǴ� �������� ������ ��ֹ��� ��ĥ �� ��ֹ��� ��ġ�� �ʴ� ���� ����� �� ������ ��ġ�� ����Ѵ�.
	 *	@param point ã���� �ϴ� ��ġ. �Է°� ���ÿ� ����� ��� ��ġ ����
	 *	@return true - ��ġ ��� ����<br>
	 *	        false - ��ġ ��� ����<br>
	 */
	bool FindNearestPoint (ObjectLocation *point);
};

#endif

