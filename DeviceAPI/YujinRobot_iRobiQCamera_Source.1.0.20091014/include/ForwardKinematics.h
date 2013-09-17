#ifndef _FORWARD_KINEMATICS_H_
#define _FORWARD_KINEMATICS_H_

#include "Application.h"
#include "OprosApiTypes.h"

#include <valarray>

using namespace std;

namespace OPRoS
{

// ����
/**
 *	���ⱸ���� �Ŵ�ǽ�����Ͱ� � �ڼ��� ���� ��, �� ������ġ(End Effector)�� �ش��ϴ� ��ġ��
 *	� ��ġ�� �ְ� �Ǵ����� ���� ����ϴ� ���̴�. �� ���������� �Ŵ�ǽ�������� ��� ��� ����
 *	���ⱸ���� ����ϴ� �������̽��� �ٷ��.
 */
class ForwardKinematics : public Application
{
public:
	ForwardKinematics(void) { };
	virtual ~ForwardKinematics(void) { };

public:
	/**
	 *	ForwardKinematics API�� �ʱ�ȭ �ϴ� ǥ�� �Լ��̴�.
	 *  ������Ʈ�κ��� �Ķ���͸� �޾� ForwardKinematics API�� ���� �� �޸𸮸� �ʱ�ȭ �Ѵ�. 
	 *	@param parameter �ʱ�ȭ�� �ʿ��� �Ķ����.
	 *	@return true - �ʱ�ȭ ����<br>
	 *			false - �ʱ�ȭ ����<br>
	 */
	virtual bool initialize(Property parameter) = 0;

	/**
	 *	ForwardKinematics API�� ���� �ϴ� ǥ�� �Լ��̴�.
	 *  ForwardKinematics API���� ����ϴ� �޸𸮳� �ٸ� ���̺귯���� �����Ѵ�.
	 *	@return true - ���� ����<br>
	 *			false - ���� ����<br>
	 */
	virtual bool finalize(void) = 0;

	/**
	 *	ForwardKinematics API�� Ȱ��ȭ �ϴ� ǥ�� �Լ��̴�.
	 *	@return true - Ȱ��ȭ ����<br>
	 *			false - Ȱ��ȭ ����<br>
	 */
	virtual bool enable(void) = 0;

	/**
	 *	ForwardKinematics API�� ��Ȱ��ȭ �ϴ� ǥ�� �Լ��̴�.
	 *	@return true - ��Ȱ��ȭ ����<br>
	 *			false - ��Ȱ��ȭ ����<br>
	 */
	virtual bool disable(void) = 0;

	/**
	 *	ForwardKinematics API�� �ĸ����͸� �����ϴ� ǥ�� �Լ��̴�.
	 *	@param parameter ForwardKinematics API�� �ʿ��� �Ķ����.
	 *	@return true - �ĸ����� ���� ����<br>
	 *			false - �Ķ���� ���� ����<br>
	 */
	virtual bool setParameter(Property parameter) = 0;

	/**
	 *	ForwardKinematics API�� �ĸ����͸� ��� ǥ�� �Լ��̴�.
	 *	@return parameter - ForwardKinematics API�� �Ķ����<br>
	 */
	virtual Property getParameter(void) = 0;

public:
	/**
	 *	�Ŵ�ǽ�������� ���ⱸ��(Forward Kinematics)�� ����Ѵ�.
	 *	@param jointPosition ���� ������ ����(����: degree)
	 *	@param endEffectorPosition ������ġ�� ���� ��ġ(x,y,z,roll,pitch,yaw)������
	 *	@return true - ��� ������ �������� �� true ���� ��ȯ�Ѵ�.<br>
	 *			false - ��� ������ �������� �� false ���� ��ȯ�Ѵ�.<br>
	 */
	virtual bool solveForwardKinematics(valarray<double> jointPosition, ObjectPosition *endEffectorPosition) = 0;
	
};


};


#endif
