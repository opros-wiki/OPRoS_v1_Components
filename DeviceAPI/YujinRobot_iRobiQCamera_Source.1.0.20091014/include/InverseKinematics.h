#ifndef _INVERSE_KINEMATICS_H_
#define _INVERSE_KINEMATICS_H_

#include "Application.h"
#include "OprosApiTypes.h"

#include <valarray>

using namespace std;

namespace OPRoS
{

// ����
/**
 *	���ⱸ���� ������ġ(End Effector)�� � ��ġ�� ��ġ��Ű�� �� ��, ������ġ(End Effector)��
 *	�ش� ��ġ�� �������� �Ŵ�ǽ�����Ͱ� � �ڼ��� ���ؾ� �ϴ°��� ����ϴ� ���̴�.
 *	�� ���������� �Ŵ�ǽ�������� ��� ��� ���� ���ⱸ���� ����ϴ� �������̽��� �ٷ��.
 */
class InverseKinematics : public Application
{
public:
	InverseKinematics(void) { };
	virtual ~InverseKinematics(void) { };

public:
	/**
	 *	InverseKinematics API�� �ʱ�ȭ �ϴ� ǥ�� �Լ��̴�.
	 *  ������Ʈ�κ��� �Ķ���͸� �޾� InverseKinematics API�� ���� �� �޸𸮸� �ʱ�ȭ �Ѵ�. 
	 *	@param parameter �ʱ�ȭ�� �ʿ��� �Ķ����.
	 *	@return true - �ʱ�ȭ ����<br>
	 *			false - �ʱ�ȭ ����<br>
	 */
	virtual bool initialize(Property parameter) = 0;

	/**
	 *	InverseKinematics API�� ���� �ϴ� ǥ�� �Լ��̴�.
	 *  InverseKinematics API���� ����ϴ� �޸𸮳� �ٸ� ���̺귯���� �����Ѵ�.
	 *	@return true - ���� ����<br>
	 *			false - ���� ����<br>
	 */
	virtual bool finalize(void) = 0;

	/**
	 *	InverseKinematics API�� Ȱ��ȭ �ϴ� ǥ�� �Լ��̴�.
	 *	@return true - Ȱ��ȭ ����<br>
	 *			false - Ȱ��ȭ ����<br>
	 */
	virtual bool enable(void) = 0;

	/**
	 *	InverseKinematics API�� ��Ȱ��ȭ �ϴ� ǥ�� �Լ��̴�.
	 *	@return true - ��Ȱ��ȭ ����<br>
	 *			false - ��Ȱ��ȭ ����<br>
	 */
	virtual bool disable(void) = 0;

	/**
	 *	InverseKinematics API�� �ĸ����͸� �����ϴ� ǥ�� �Լ��̴�.
	 *	@param parameter InverseKinematics API�� �ʿ��� �Ķ����.
	 *	@return true - �ĸ����� ���� ����<br>
	 *			false - �Ķ���� ���� ����<br>
	 */
	virtual bool setParameter(Property parameter) = 0;

	/**
	 *	InverseKinematics API�� �ĸ����͸� ��� ǥ�� �Լ��̴�.
	 *	@return parameter - InverseKinematics API�� �Ķ����<br>
	 */
	virtual Property getParameter(void) = 0;

public:
	/**
	 *	�Ŵ�ǽ�������� ���ⱸ��(Inverse Kinematics)�� ����Ѵ�.
	 *	@param endEffectorPosition ������ġ�� ��ǥ��ġ(x,y,z,roll,pitch,yaw)������
	 *	@param currentJointPoisiton ���� ������ ����(����: degree)
	 *	@param jointPosition ��ǥ��ġ���� �����ϱ����� ����
	 *	@return true - ��� ������ �������� �� true ���� ��ȯ�Ѵ�.<br>
	 *			false - ��� ������ �������� �� false ���� ��ȯ�Ѵ�.<br>
	 */
	virtual bool solveInverseKinematics(valarray<double> endEffectorPosition, valarray<double> currentJointPoisiton, valarray<double> *jointPosition) = 0;
};


};


#endif
