#ifndef	_GRIPPER_H_
#define	_GRIPPER_H_

#include "Device.h"
#include "OprosApiTypes.h"

namespace OPRoS
{

// ����
/**
 *	�׸��� (Gripper)�� ������ �繰�� ���� �� �ִ� ��ġ�� ���� ������Ʈ�̴�.
 *	�Ϲ������� �׸��۴� �Ŵ�ǽ������ ������ġ(end effector)�� ���� �� �ϳ��� ���Ǿ�
 *	������ �繰�� ��� ������ �� �� �ְ� �ȴ�. �� ���������� �׸����� ����� �����ϴ� �������̽��� �ٷ��.
 *	�׸��۴� Mainpulator�� ��ӹ޾ұ� ������ Manipulator API���� �����ϴ� �������̽��� �����Ѵ�.
 *	<tr><td><b>dllName</b></td> <td>std::string</td> <td colspan=2>������Ʈ���� ����� dll������ �̸��̴�.</td></tr>
 *	<tr><td><b>size</b></td> <td>int</td> <td colspan=2>�Ŵ�ǽ�������� �������� �������� ����(��������)�� �����̴�. dllName, size�� ������ ������ �Ķ���͵��� ��� ������ ���� ������ ������, �� ���� ������ Ư¡�� ���� �޶�����.</td></tr>
 *	<tr><td><b>a</b></td> <td>double</td> <td>�ش� �������� ���� �������� x�� ������ �Ÿ��̴�.(����:m)</td> <td rowspan=5><img src="../../images/DHParameter.jpg"></td></tr>
 *	<tr><td><b>b</b></td> <td>double</td> <td>�ش� �������� ���� �������� y�� ������ �Ÿ��̴�.(����:m)</td></tr>
 *	<tr><td><b>alpha</b></td> <td>double</td> <td>���ӵ� ������ ��Ʋ�� ����, �ش� ���� z��� �������� z�� ������ �����̴�.(����:degree)</td></tr>
 *	<tr><td><b>d</b></td> <td>double</td> <td>���ӵ� ������ ��Ż����, z���� �������� �ش� ������ x��� ���� ������ x�� ������ �Ÿ��̴�.(����:m)</td></tr>
 *	<tr><td><b>theta</b></td> <td>double</td> <td>���ӵ� ������ ȸ������, z���� �������� �ش� ������ x��� ���� ������ x�� ������ �����̴�.(����:degree)</td></tr>
 *	<tr><td><b>direction</b></td> <td>int</td> <td colspan=2>�Ŵ�ǽ�������� ȸ������ ���������̴�. �κ��� ��Ī�� ������ ���, ������ �Ŵ�ǽ�����Ϳ� ���� �Ŵ�ǽ�������� ���۹����� �ݴ�� �������־�� �� ��, 1�Ǵ� -1�� ���� �־� ���ȴ�.</td></tr>
 *	<tr><td><b>isVirtual</b></td> <td>bool</td> <td colspan=2>�ش������ ���� ������ ������ �������� �����Ѵ�. 0�� ���� ��, 1�� ������ ���� ��Ÿ����.</td></tr>
 *	<tr><td><b>jointType</b></td> <td>string</td> <td colspan=2>�ش������ �������� ������ �����Ѵ�. revolute�� ȸ��Ÿ��, prismatic�� ����Ÿ��, fixed�� ��������� ��Ÿ����.</td></tr>
 *	<tr><td><b>minimumRange</b></td> <td>double</td> <td colspan=2>�ش������ �ּ� ������ġ�̴�. maximumRange�� �Բ� ���۹����� �����Ѵ�.</td></tr>
 *	<tr><td><b>maximumRange</b></td> <td>double</td> <td colspan=2>�ش������ �ִ� ������ġ�̴�. minimumRange�� �Բ� ���۹����� �����Ѵ�.</td></tr>
 *	<tr><td><b>maximumVelocity</b></td> <td>double</td> <td colspan=2>�ش������ �ִ� ���ۼӵ��̴�.</td></tr>
 *	<tr><td><b>acceleration</b></td> <td>double</td> <td colspan=2>�ش������ ���ӵ��̴�.</td></tr>
 *	<tr><td><b>id</b></td> <td>int</td> <td colspan=2>�ش������ index�� �������ش�. 1���� �����Ͽ� index ID�� �ű� �� ������, ��������� ��� 0���� ǥ���Ѵ�.</td></tr>
 *	<tr><td><b>powerUnit</b></td> <td>int</td> <td colspan=2>power�� ������ �������ش�. 0�� ���� torque(Nm), 1�� ���� �Ŀ�(W), 2�� ���� ����(A), 3�� ���� ����(%)�� �����Ѵ�.</td></tr>
 *	</table></center>
 */
class Gripper : public Device
{
public:
	Gripper(void) { };
	virtual ~Gripper(void) { };

public:
	/**
	 *	���߿������� ����� �����Ѵ�.
	 *	@param power ���������� ��°�
	 *	@param time ms ������ ��� �ð�, time�� 0�� ��� �ٸ� ����� �Էµ��� ������ ������ ���� ���� �Ѵ�.
	 *	@return true - ���������� ���������� ����� ������ ��� true ���� ��ȯ�Ѵ�.<br>
				false - ���������� ����� �����ϴ� ���� ������ �߻��� ��� false ���� ��ȯ�Ѵ�.<br>
	 */
	virtual bool runGripping(void) = 0;
	virtual bool stopGripping(void) = 0;
	virtual bool isGripped(void) = 0;
	virtual bool isStopGripped(void) = 0;
};

};

#endif	//	_GRIPPER_H_