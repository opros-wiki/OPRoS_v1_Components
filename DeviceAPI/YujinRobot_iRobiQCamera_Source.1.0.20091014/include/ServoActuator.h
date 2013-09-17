#ifndef	_SERVO_ACTUATOR_H_
#define	_SERVO_ACTUATOR_H_

#include "Actuator.h"

namespace OPRoS
{

// ����
/**
 *	���� ���߿����� API�� ���� ��� ���� �����θ� ���� �������̽��̴�.
 *	��� ���� ���߿����ʹ� ServoActuator �������̽��� �̿��ؾ� �Ѵ�.
 *	Actuator�� power������ �����ϴ� �������� �ݸ鿡, Servo Actuator�� �ӵ����� ��ġ���
 *	������ �������̴�. setParameter �������̽��� ȣ��Ǹ� ���������� ���� ���߿�������
 *	�ִ����, �ִ�ӵ�, ���ӵ�, ��ġ ������ �����ؾ� �Ѵ�.
 *	<center><table border=0><tr><td colspan=3><center><b>GlobalMap API���� ����ϴ� Parameter</b></center></td></tr>
 *	<tr><td bgcolor=#dddddd><center><b>Index</b></center></td><td bgcolor=#dddddd><center><b>Type of Value</b></center></td><td bgcolor=#dddddd><center><b>Description</b></center></td></tr>
 *	<tr><td><b>maximumPower</b></td><td>double</td><td>���� ���߿������� �ִ����</td></tr>
 *	<tr><td><b>powerUnit</b></td><td>int</td><td>���� ���߿����� ����� ������ �����Ѵ�. 0�� ��ũ(Nm), 1�� �Ŀ�(W), 2�� ����(A), 3�� ����(%) �� ��Ÿ����.</td></tr>
 *	<tr><td><b>type</b></td><td>int</td><td>���� ���߿������� Ÿ���� �����Ѵ�. 0�� ȸ��(Revolute) Ÿ���̰�, 1�� ����(Prismatic) Ÿ���̴�.</td></tr>
 *	<tr><td><b>encoderResolution</b></td><td>double</td><td>���� ���߿������� �ӵ� �� ��ġ�� ����ϱ� ���� ���Ǵ� ������ �ػ󵵸� ��Ÿ����. type�� 0�� ���� ���Ӻ� ���ܿ��� �����Ǵ� 360�� �� �����Ǵ� ������ ���̴�.
 *	���� ��� ������ ���ڴ��� �ѹ��� �� �� 2000�޽��� �����Ǹ� encoderResolution�� 2000�� �ȴ�. type�� 1�� ���� 1���ʹ� �����Ǵ� ������ ���� �����Ѵ�.</td></tr>
 *	<tr><td><b>reductionRatio</b></td><td>double</td><td>���� ���߿������� ���Ӻ�(����)�� ��Ÿ����. ���Ϳ� ���Ӻ� 100:1�� ����Ǹ� reduction Ratio�� 100���� �����Ѵ�.</td></tr>
 *	<tr><td><b>maximumVelocity</b></td><td>double</td><td>���� ���߿������� �ִ�ӵ��̴�. type�� 0�� ��� degree/s ������ �����ϰ�, type�� 1�� ��� m/s ������ �����Ѵ�.</td></tr>
 *	<tr><td><b>acceleration</b></td><td>double</td><td>���� ���߿������� ���ӵ��̴�. type�� 0�� ��� degree/s2d�� �����ϰ�, type�� 1�� ��� m/s2d�� �����Ѵ�.</td></tr>
 *	<tr><td><b>minimumPositionLimit</b></td><td>double</td><td>���� ���߿������� �ּ� ��ġ ���� �Ķ�����̴�. ���� ���߿����ʹ� ������ �� ���Ϸ� ��ġ�� ������ �� ����.</td></tr>
 *	<tr><td><b>maximumPositionLimit</b></td><td>double</td><td>���� ���߿������� �ִ� ��ġ ���� �Ķ�����̴�. ���߿����ʹ� ������ �� �̻����� ��ġ�� ������ �� ����.</td></tr>
 *	</table></center>
 */
class ServoActuator : public Actuator
{
public:
	ServoActuator(void) { };
	virtual ~ServoActuator(void) { };

public:
	/**
	 *	���� ���߿������� �ӵ��� �����Ѵ�. type�� 0�� ��� ������ degree/s�̰� 1�� ��� ������ m/s�̴�.
	 *	@param velocity ���� ���߿������� �ӵ�
	 *	@param time ms ������ ��� �ð�, time�� 0�� ��� �ٸ� ����� �Էµ��� ������ ������ ���� ���� �Ѵ�.
	 *	@return true - ���������� ���� ���������� �ӵ��� ������ ��� true ���� ��ȯ�Ѵ�.<br>
	 *			false - ���� ���������� �ӵ��� �����ϴ� ���� ������ �߻��� ��� false ���� ��ȯ�Ѵ�.<br>
	 */
	virtual bool setVelocity(double velocity, unsigned long time = 0) = 0;

	/**
	 *	���� ���߿������� �ӵ��� �д´�. type�� 0�� ��� ������ degree/s�̰� 1�� ��� ������ m/s�̴�.
	 *	@param velocity ���� ���߿������� �ӵ��� ����� ����
	 *	@return true - ���������� ���� ���������� �ӵ��� �о�� ��� true ���� ��ȯ�Ѵ�.<br>
	 *			false - ���� ���������� �ӵ��� �о���� ���� ������ �߻��� ��� false ���� ��ȯ�Ѵ�.<br>
	 */
	virtual bool getVelocity(double *velocity) = 0;

	/**
	 *	���� ���߿������� ��ġ�� �����Ѵ�. �� �������̽��� time �ð� ���� position ��ġ�� �̵���Ų��.
	 *	time�� �ʹ� �۾Ƽ� ���� ���߿����Ϳ��� �����ϴ� �ӵ����� ���� �ӵ��� ���������� ��ǥ ��ġ��
	 *	�̵��� �� �ִ� ��� ������ ��ȯ�Ѵ�. type�� 0�� ��� ������ degree�̰�, 1�� ��� ������ m �̴�.
	 *	@param position ���� ���߿������� ��ġ
	 *	@param time ms ������ ��� �ð�, time�� 0�� ��� �ٸ� ����� �Էµ��� ������ ������ ���� ���� �Ѵ�.
	 *	@return true - ���������� ���� ���������� ��ġ�� ������ ��� true ���� ��ȯ�Ѵ�.<br>
	 *			false - ���� ���������� ��ġ�� �����ϴ� ���� ������ �߻��� ��� false ���� ��ȯ�Ѵ�.<br>
	 */
	virtual bool setPosition(double position, unsigned long time = 0) = 0;

	/**
	 *	���� ���߿������� ��ġ�� �о�´�. type�� 0�� ��� ������ ����(degree)�̰�, 1�� ��� ������ �Ÿ�(m)�̴�.
	 *	@param position ���� ���߿������� ���� ��ġ�� ����� ����
	 *	@return true - ���������� ���� ���������� ���� ��ġ�� �о�� ��� true ���� ��ȯ�Ѵ�.<br>
	 *			false - ���� ���������� ���� ��ġ�� �о���� ���� ������ �߻��� ��� false ���� ��ȯ�Ѵ�.<br>
	 */
	virtual bool getPosition(double *position) = 0;
};

};

#endif	//	_SERVO_ACTUATOR_H_