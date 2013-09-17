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


// ����
/**
*	KITECH_NavigationComp�� �̵� �κ��� ������ ���� ������Ʈ�̴�.
*	KITECH_NavigationComp�� �̵� �κ��� ������Ʈ�ν� ������ ���� ǥ�� �������̽��� INavigationService�� ��ӹ޾� �����ȴ�.
*	���� ���̺귯���� �����Ǹ� IGlobalMapService�� ��ӹ޾� ������ ������ ������Ʈ, 
*	ILocalizationService�� ��ӹ޾� ������ ��ġ ���� ������Ʈ, IPathPlanningService�� ��ӹ޾� ������ ��ΰ�ȹ ������Ʈ,
*	IObstacleAvoidanceService�� ��ӹ޾� ������ ��ֹ� ȸ�� ������Ʈ, IWheelControllerCompService�� ��ӹ޾� ������ ������ ������Ʈ,
*	ILaserScannerCompService�� ��ӹ޾� ������ ��������ĳ�� ������Ʈ�� �� 6���� ������Ʈ��� ����Ǿ� ���ȴ�.
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
	*	�κ��� ��ġ�� �����ϴ� ǥ�� �Լ��̴�.
	*	@param position �κ��� ��ġ
	*	@return void<br>
	*/
	virtual void SetPosition(ObjectLocation position);

	/**
	*	�κ��� ��ġ�� ��� ǥ�� �Լ��̴�.
	*	@param position �κ��� ��ġ
	*	@return void<br>
	*/
	virtual ObjectLocation GetPosition();

	/**
	*	�̵� �κ��� �������� ������ �����ϴ� ǥ�� �Լ��̴�.
	*	@param targetPosition ������ ��ġ
	*	@return true - ���� ���� ����<br>
	*			false - ���� ���� ����<br>
	*/
	virtual bool NavigationTo(ObjectLocation targetPosition);

	/**
	*	�̵� �κ��� �Է� �Ÿ���ŭ ������Ű�� ǥ�� �Լ��̴�.
	*	@param distance ���� �Ÿ�(����:m)
	*	@return true - �̵� ����<br>
	*			false - �̵� ����<br>
	*/
	virtual bool Move(double distance);

	/**
	*	�̵� �κ��� �Է� ������ŭ ȸ����Ű�� ǥ�� �Լ��̴�.
	*	@param degree ȸ�� ����(����:��)
	*	@return true - �̵� ����<br>
	*			false - �̵� ����<br>
	*/
	virtual bool Rotate(double degree);

	/**
	*	�������� �̵� �κ��� ���ߴ� ǥ�� �Լ��̴�.
	*	@return void<br>
	*/
	virtual void AbortNavigation();

	/**
	*	�̵� �κ��� ���� �������� �Ǵ��ϴ� ǥ�� �Լ��̴�.
	*	@return true - ���� ���� ����<br>
	*	        false -���� ����<br> 
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
	*	�Ķ���͸� �����ϴ� �����̴�.
	*	�Ķ������ �׸��� �̵� �κ��� �ʱ� ��ġ�̴�.
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
	*	������ ��ĳ�� ���� ������Ʈ�� �Ķ���͸� �����ϴ� �����̴�.
	*/
	Property laserScannerParameter;

	/**
	*	������ ��ĳ�� ������ ������ �����͸� �����ϴ� �����̴�.
	*/
	std::vector<double> laserData;

	/**
	*	������ ��ĳ�� ������ ���� ������ ������ ��Ÿ���� �����̴�.
	*/
	int laserScannerCount;

	/**
	*	������ ������Ʈ�� �Ķ���͸� �����ϴ� �����̴�.
	*/
	Property wheelControllerParameter;

	/**
	*	�̵� �κ��� ���� �ݰ��� ��Ÿ���� �����̴�.
	*/
	double mobilitySafeRadius;

	/**
	*	���� ó���� �ߺ� ó���� ���� ���� �����̴�.
	*/
	OprosLock lock;

	/**
	*	���� ó���� �ܰ踦 ��Ÿ���� �����̴�.
	*/
	int navigationStep;

	/**
	*	������ ó���ϴ� �Լ��̴�.
	*/
	void DoTask ();

	/**
	*	�̵� �κ��� ���� ��ġ�� ��Ÿ���� �����̴�.
	*/
	ObjectLocation currentPosition;

	/**
	*	�̵� �κ��� ������ ��ġ�� ��Ÿ���� �����̴�.
	*/
	ObjectLocation targetPosition;

	/**
	*	�̵� �κ��� ������ ��ġ���� �߰� ��� ��ġ�� ��Ÿ���� �����̴�.
	*/
	ObjectLocation subTargetPosition;

	/**
	*	�̵� �κ��� ��� ��ġ�� ��Ÿ���� �����̴�.
	*/
	vector<ObjectLocation> path;
};

#ifdef USE_GUI
extern KITECH_NavigationComp *naviComp;
#endif

#endif

