#ifndef _TRAJECTORY_GENERATION_H_
#define _TRAJECTORY_GENERATION_H_

#include "Application.h"
#include "OprosApiTypes.h"

#include <vector>
#include <valarray>

using namespace std;

namespace OPRoS
{

// ����
/**
 *	���� ���� (Trajectory Generation) API�� �Ŵ�ǽ�����Ͱ� �������� ���������� �߰��Ͽ� ������ �����Ѵ�.
 *	���� ���� API���� �������� �߰��ϴ� addViaPoint �������̽��� �߰��� �������� �����ϴ� clearViaPoint
 *	�������̽�, �׸��� �߰��� ���������� �������ִ� interpolation �������̽��� �����Ǿ� �ִ�.
 */
class TrajectoryGeneration : public Application
{
public:
	TrajectoryGeneration(void) { };
	virtual ~TrajectoryGeneration(void) { };

public:
	/**
	 *	TrajectoryGeneration API�� �ʱ�ȭ �ϴ� ǥ�� �Լ��̴�.
	 *  ������Ʈ�κ��� �Ķ���͸� �޾� TrajectoryGeneration API�� ���� �� �޸𸮸� �ʱ�ȭ �Ѵ�. 
	 *	@param parameter �ʱ�ȭ�� �ʿ��� �Ķ����.
	 *	@return true - �ʱ�ȭ ����<br>
	 *			false - �ʱ�ȭ ����<br>
	 */
	virtual bool initialize(Property parameter) = 0;

	/**
	 *	TrajectoryGeneration API�� ���� �ϴ� ǥ�� �Լ��̴�.
	 *  TrajectoryGeneration API���� ����ϴ� �޸𸮳� �ٸ� ���̺귯���� �����Ѵ�.
	 *	@return true - ���� ����<br>
	 *			false - ���� ����<br>
	 */
	virtual bool finalize(void) = 0;

	/**
	 *	TrajectoryGeneration API�� Ȱ��ȭ �ϴ� ǥ�� �Լ��̴�.
	 *	@return true - Ȱ��ȭ ����<br>
	 *			false - Ȱ��ȭ ����<br>
	 */
	virtual bool enable(void) = 0;

	/**
	 *	TrajectoryGeneration API�� ��Ȱ��ȭ �ϴ� ǥ�� �Լ��̴�.
	 *	@return true - ��Ȱ��ȭ ����<br>
	 *			false - ��Ȱ��ȭ ����<br>
	 */
	virtual bool disable(void) = 0;

	/**
	 *	TrajectoryGeneration API�� �ĸ����͸� �����ϴ� ǥ�� �Լ��̴�.
	 *	@param parameter TrajectoryGeneration API�� �ʿ��� �Ķ����.
	 *	@return true - �ĸ����� ���� ����<br>
	 *			false - �Ķ���� ���� ����<br>
	 */
	virtual bool setParameter(Property parameter) = 0;

	/**
	 *	TrajectoryGeneration API�� �ĸ����͸� ��� ǥ�� �Լ��̴�.
	 *	@return parameter - TrajectoryGeneration API�� �Ķ����<br>
	 */
	virtual Property getParameter(void) = 0;

public:
	/**
	 *	���������� �����Ѵ�. (Joint space�󿡼��� ����)
	 *	@param deltatime ���������� ����(Interpolation)�� �����ð�
	 *	@return �ð��� ���� ���� �������� ������ ������<br>
	 */
	virtual std::vector<std::valarray<double>> interpolation(double deltatime) = 0;

	/**
	 *	���ؽð����κ����� �ð�(time)�� ��ġ(point)�� �������� �߰��Ѵ�.
	 *	@param time ���ؽð����κ����� �ð�
	 *	@param point ���ؽð����κ����� ��ġ
	 *	@return true - ��� ������ �������� �� true ���� ��ȯ�Ѵ�.<br>
	 *			false - ��� ������ �������� �� false ���� ��ȯ�Ѵ�.<br>
	 */
	virtual bool addViaPoint(double time, valarray<double> point) = 0;

	/**
	 *	�Էµ� ��������� ��� �����Ѵ�.
	 */
	virtual void clearViaPoint(void) = 0;
};


};


#endif
