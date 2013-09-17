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


// ����
/**
*	KITECH_VFHObstacleAvoidanceComp�� �̵� �κ��� ������ ���� ���� ��ֹ��� ȸ���ϴ� ������Ʈ�̴�.
*	KITECH_VFHObstacleAvoidanceComp�� ��ֹ� ȸ�Ǹ� ���� ������Ʈ�ν� ��ֹ� ȸ�Ǹ� ���� ǥ�� �������̽��� IObstacleAvoidanceService�� ��ӹ޾� �����ȴ�.
*	Vector field histogram �˰���� ������ ��ĳ�� ������ ����Ͽ� ���� ��ֹ� ȸ�Ǹ� �����Ѵ�.
*	���� ���̺귯���� �����Ǹ� NavigationComponent���� KITECH_VFHObstacleAvoidanceComp�� ���� �Լ��� ����Ѵ�.
*	KITECH_VFHObstacleAvoidanceComp�� ������ ��ĳ�� ������ ����ϰ� �̵� �κ��� ���� �������� �����ӵ�, ȸ���ӵ��� ����ϱ� ������
*	�̵� �κ��� �ִ� �ӵ�, ���ӵ�, ���� �ݰ� ũ��� ������ ��ĳ�� ������ ���� ��ĵ ����, ���� ��ĵ ����, �ּ� ���� �Ÿ�, �ִ� �����Ÿ�
*	��ĵ ������ ����, �׸��� �̵� �κ��� �����Ǵ� ��ġ ������ �˾ƾ� �Ѵ�.
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
	*	�ĸ����͸� �����ϴ� ǥ�� �Լ��̴�.
	*	@param parameter �Ķ���� ����.
	*	@return true - �ĸ����� ���� ����<br>
	*			false - �Ķ���� ���� ����<br>
	*/
	virtual bool SetParameter(Property parameter);

	/**
	*	�ĸ����͸� ��� ǥ�� �Լ��̴�.
	*	@return �ĸ����� ������<br>
	*/
	virtual Property GetParameter();

	virtual int GetError();

	/**
	*	�κ��� ��ġ�� �����Ѵ�.
	*	@param position �κ��� ��ġ
	*	@return void<br>
	*/
	virtual void SetPosition(ObjectLocation position);

	/**
	*	���� ��ġ���� ������ ��ġ���� ������ ��ĳ�� ���� �����͸� �̿��� ���� ��ֹ��� ȸ���ϸ� �̵��ϴ� �κ��� ���� �ӵ��� ȸ�� �ӵ��� ����ϴ� ǥ�� �Լ��̴�.
	*	@param currentPosition �κ��� ���� ��ġ
	*	@param targetPosition �κ��� ������ ��ġ
	*	@return ���� �̵� �κ��� �ӵ���<br>
	*/
	virtual WheelControlVelocity Avoid(ObjectLocation currentPosition, ObjectLocation targetPosition);

private:
	/**
	*	�Ķ���͸� �����ϴ� �����̴�.
	*	�Ķ������ �׸��� �̵� �κ��� �ִ� �ӵ�, ���ӵ�, ���� �ݰ� ũ��� ������ ��ĳ�� ������ ���� ��ĵ ����, ���� ��ĵ ����, �ּ� ���� �Ÿ�, �ִ� �����Ÿ�
	*	��ĵ ������ ����, ���� ����, �׸��� �̵� �κ��� �����Ǵ� ��ġ�̴�.
	*/
	Property parameter;

	int error;

	/**
	*	�Ķ���� ������ ���� �� �׸񺰷� �����͸� ��´�.
	*	@return true - �ĸ����� ��� ����<br>
	*			false - �Ķ���� ��� ����<br>
	*/
	bool LoadProperty ();

	/**
	*	�̵� �κ��� �ִ� �ӵ�
	*/
	double maximumVelocity;

	/**
	*	�̵� �κ��� ���ӵ�
	*/
	double acceleration;

	/**
	*	�̵� �κ��� ���� ũ��ν� ���� �ݰ濡 ���� ������
	*/
	double safeRadius;

	/**
	*	������ ��ĳ�� ������ ��ĵ ���� ����
	*/
	double startAngle;

	/**
	*	������ ��ĳ�� ������ ��ĵ �� ����
	*/
	double endAngle;

	/**
	*	������ ��ĳ�� ������ �ּ� ���� �Ÿ�
	*/
	double minRange;

	/**
	*	������ ��ĳ�� ������ �ִ� ���� �Ÿ�
	*/
	double maxRange;

	/**
	*	������ ��ĳ�� ������ ���� ������ ����
	*/
	int sensorCount;

	/**
	*	������ ��ĳ�� ������ �̵� �κ��� �����Ǵ� ��ġ
	*/
	ObjectLocation sensorPosition;

	/**
	*	VFH �˰��򿡼� ����ϴ� �κ��� ��ġ�� �߽ɿ����� ���θ� Ŭ����
	*/
	CLocalMap *localMap;

	/**
	*	VFH �˰��򿡼� ����ϴ� ������ ����
	*/
	double targetDirection;

	/**
	*	VFH �˰��򿡼� ����ϴ� ���� ��ġ���� ������������ �Ÿ�
	*/
	double targetDistance;

	/**
	*	VFH �˰��򿡼� ����ϴ� �κ��� ȸ�� ����
	*/
	double steerDirection;

	/**
	*	VFH �˰��򿡼� ����ϴ� �κ��� ���� �ӵ�
	*/
	double steerForwardVel;

	/**
	*	VFH �˰��򿡼� ����ϴ� �κ��� ȸ�� �ӵ�
	*/
	double steerAngularVel;

	/**
	*	VFH �˰��򿡼� ����ϴ� ����������׷� ������
	*/
	double polarHistogram[360];

	/**
	*	�κ��� ���� ��ġ
	*/
	ObjectLocation currentPosition;

	/**
	*	�κ��� ������ ��ġ
	*/
	ObjectLocation targetPosition;

	/**
	*	���� �ʿ� ����� ��ֹ��� ���� ����������׷��� �����Ѵ�.
	*	@return void<br>
	*/
	void MakeDirectionHistogram ();

	/**
	*	������ ����������׷��� �̿��� �������� ���ϸ鼭 ��ֹ��� ȸ���ϴ� �̵� �κ��� �����ӵ��� ȸ�� �ӵ��� ����Ѵ�.
	*	@param forwardVel ���� �̵� �κ��� �����ӵ�
	*	@param angularVel ���� �̵� �κ��� ȸ���ӵ�
	*	@return void<br>
	*/
	void CalcDrivingVelocity (double *forwardVel, double *angularVel);
};

#endif

