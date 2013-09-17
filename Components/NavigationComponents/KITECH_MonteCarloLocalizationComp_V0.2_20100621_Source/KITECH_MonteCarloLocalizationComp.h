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

// ����
/**
*	KITECH_MonteCarloLocalizationComp�� �̵� �κ��� ������ ���� �κ��� ���� ��ġ�� �����ϴ� ������Ʈ�̴�.
*	KITECH_MonteCarloLocalizationComp�� ������ ��ĳ�� ���� ������� �ϴ� �κ��� ���� ��ġ�� �����ϴ� ������Ʈ�ν� 
*	�κ��� ���� ��ġ�� �����ϱ� ���� ǥ�� �������̽��� ILocalizationCompService�� ��ӹ޾� �����ȴ�.
*	MonteCarlo ��� Particle Filter �˰����� ����Ѵ�.
*	���� ���̺귯���� �����Ǹ� NavigationComponent���� KITECH_VFHObstacleAvoidanceComp�� ���� �Լ��� ȣ���Ͽ� ����Ѵ�.
*	KITECH_MonteCarloLocalizationComp�� ������ ��ĳ�� ������ ����ϰ� �̵� �κ��� ��ġ ������ �̿��� �����ϱ� ������
*	�̵� �κ��� ���� ����, ȸ�� ������ ������ ��ĳ�� ������ ���� ��ĵ ����, ���� ��ĵ ����, �ּ� ���� �Ÿ�, �ִ� �����Ÿ�
*	��ĵ ������ ����, ���� ����, �׸��� �̵� �κ��� �����Ǵ� ��ġ ������ �˾ƾ� �Ѵ�.
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
	*	�ĸ����͸� �����ϴ� ǥ�� �Լ��̴�.
	*	@param parameter �Ķ���� ����.
	*	@return true - �ĸ����� ���� ����<br>
	*			false - �Ķ���� ���� ����<br>
	*/
	virtual bool SetParameter(Property parameter);

	/**
	*	�ĸ����͸� ��� ǥ�� �Լ��̴�.
	*	@return �Ķ���� ����<br>
	*/
	virtual Property GetParameter();

	virtual int GetError ();

	/**
	*	�κ��� ��ġ�� �����ϴ� ǥ�� �Լ��̴�.
	*	@param position �κ��� ��ġ
	*	@return void<br>
	*/
	virtual void SetPosition(ObjectLocation position);

	/**
	*	�κ��� ��ġ�� �����ϰ� �� ����� ��� ǥ�� �Լ��̴�.
	*	@return ������ �κ��� ��ġ<br>
	*/
	virtual ObjectLocation Localize();

private:
	/**
	*	�Ķ���͸� �����ϴ� �����̴�.
	*	�Ķ������ �׸��� ��ƼŬ�� ������ �̵� �κ��� ���� ����, ȸ�� ������ ������ ��ĳ�� ������ ���� ��ĵ ����, ���� ��ĵ ����, �ּ� ���� �Ÿ�, �ִ� �����Ÿ�
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
	*	�̵� �κ��� ���� ����
	*/
	double varianceDistance;

	/**
	*	�̵� �κ��� ȸ�� ����
	*/
	double varianceDirection;

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
	*	������ ��ĳ�� ������ ���� ����
	*/
	double sensorVariance;

	/**
	*	������ ��ĳ�� ������ �̵� �κ��� �����Ǵ� ��ġ
	*/
	ObjectLocation sensorPosition;

	/**
	*	�κ��� ���� ��ġ
	*/
	ObjectLocation	currentPosition;

	/**
	*	�κ��� ���� ��ġ
	*/
	ObjectLocation	positionPrev;

	/**
	*	������ �κ��� ��ġ�� ���� ����
	*/
	ObjectLocation	variance;

	/**
	*	��ƼŬ�� �ִ� ����
	*/
	int maxParticles;

	/**
	*	��ƼŬ
	*/
	vector<VirtualRobot> particles;

	bool Predict(ObjectLocation position);
	bool Update(std::vector<double> sensorValue);

	/**
	*	������ ��ĳ�� ������ ������ ��ֹ����� �Ÿ��� �������� ��ֹ��� Particle�� ��ġ���� ��Ī�� �Ǵ� Ȯ���� ����Ѵ�.
	*	@param vr ��ƼŬ
	*	@param laserData[] ������ ��ĳ�� ������ ������ ������
	*	@return ��Ī Ȯ��<br>
	*/
	double GetProbability (VirtualRobot &vr, double laserData[]);

	/**
	*	��ƼŬ���� Ȯ�� ���� �̿��� ��ƼŬ���� ������Ѵ�.
	*	@return void<br>
	*/
	void Resampling ();

	/**
	*	��ƼŬ���� ��ġ�� ����Ͽ� �̵� �κ��� ��ġ�� ����Ѵ�.
	*	@return void<br>
	*/

	void StocasticPosition ();

	/**
	*	�Է� ��ġ���� ��ƼŬ���� �Է� �ݰ� ������ ������ ��ġ�� ������Ѵ�.
	*	@param x ������ ��ġ
	*	@param y ������ ��ġ
	*	@param radius �ݰ�
	*	@return void<br>
	*/
	void RandomizeAt (double x, double y, double radius);
};

#endif

