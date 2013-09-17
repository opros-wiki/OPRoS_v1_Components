#ifndef	_ACTUATOR_H_
#define	_ACTUATOR_H_

#include "Device.h"

namespace OPRoS
{

// ����
/**
 *	�κ��� �����̱� ���ؼ��� ���߿����͸� �����ؾ��Ѵ�.
 *	���߿����Ϳ��� ���� ���� ������ �ְ� �������� ���� ������ �ִ�. ���������� ���߿����͸� �����ϱ� ����
 *	����� �����ϴ� �������̽��� ����Ѵ�. �Ķ���ͷδ� ���߿������� �ִ� ��°� ��� ���� ������ �ʿ��ϴ�.
 *	<center><table border=0><tr><td colspan=3><center><b>GlobalMap API���� ����ϴ� Parameter</b></center></td></tr>
 *	<tr><td bgcolor=#dddddd><center><b>Index</b></center></td><td bgcolor=#dddddd><center><b>Type of Value</b></center></td><td bgcolor=#dddddd><center><b>Description</b></center></td></tr>
 *	<tr><td><b>maximumPower</b></td><td>double</td><td>���߿������� �ִ����</td></tr>
 *	<tr><td><b>powerUnit</b></td><td>int</td><td>���߿����� ����� ������ �����Ѵ�. 0�� ��ũ(Nm), 1�� �Ŀ�(W), 2�� ����(A), 3�� ����(%) �� ��Ÿ����.</td></tr>
 *	</table></center>
 */
#define	POWER_UNIT_TORQUE	0
#define	POWER_UNIT_POWER	1
#define	POWER_UNIT_CURRENT	2
#define	POWER_UNIT_RATE		3

class Actuator : public Device
{
public:
	Actuator(void) { };
	virtual ~Actuator(void) { };

public:
	/**
	 *	���߿������� ����� �����Ѵ�.
	 *	@param power ���������� ��°�
	 *	@param time ms ������ ��� �ð�, time�� 0�� ��� �ٸ� ����� �Էµ��� ������ ������ ���� ���� �Ѵ�.
	 *	@return true - ���������� ���������� ����� ������ ��� true ���� ��ȯ�Ѵ�.<br>
	 *			false - ���������� ����� �����ϴ� ���� ������ �߻��� ��� false ���� ��ȯ�Ѵ�.<br>
	 */
	virtual bool setPower(double power, unsigned long time = 0) = 0;

	/**
	 *	���߿������� ����� �о�´�.
	 *	@param power ���������� ��°��� ����� ����
	 *	@return true - ���������� ���������� ����� �о�� ��� true ���� ��ȯ�Ѵ�.<br>
	 *			false - ���������� ����� �д� ���� ������ �߻��� ��� false ���� ��ȯ�Ѵ�.<br>
	 */
	virtual bool getPower(double *power) = 0;
};

};

#endif	//	_ACTUATOR_H_