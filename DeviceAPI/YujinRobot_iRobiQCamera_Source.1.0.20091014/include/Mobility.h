#ifndef _MOBILITY_H_
#define _MOBILITY_H_

#include "Application.h"
#include "OprosApiTypes.h"

namespace OPRoS
{
// ����
/**
 *	Mobility API�� �̵� �κ��� ������Ű�� ǥ�� API�̴�. ��� Mobility�� �� Ŭ������ ��ӹ޾� �����Ǿ�� �ϸ�,
 *	Mobility API��OPRoS Mobility Component�� ���� ����ȴ�. 
 *	Mobility API�� Mobility Component�κ��� �ĸ����͸� �޾� ���� �� �޸𸮸� �ʱ�ȭ �ϰ�, Mobility �ϵ������� �ʱ�ȭ�� �����Ѵ�. 
 *	Mobility API�� ���� ���̺귯���� �����Ǹ� Mobility Component���� �ε��Ͽ� ���ȴ�.
 *	<center><table border=0>
 *	<tr><td colspan=3><center><b>Mobility API���� ����ϴ� Parameter</b></center></td></tr>
 *	<tr><td bgcolor=#dddddd><center><b>Index</b></center></td><td bgcolor=#dddddd><center><b>Type of Value</b></center></td><td bgcolor=#dddddd><center><b>Description</b></center></td></tr>
 *	<tr><td><b>wheelDiameter</b></td><td>double</td><td>�̵� ��ġ�� ���� ������ �����̴�.(����:m)</td></tr>
 *	<tr><td><b>axleDistance</b></td><td>double</td><td>�ϳ��� �� �� �ִ� �� �������� �Ÿ��̴�.(����:m)</td></tr>
 *	<tr><td><b>varianceDistance</b></td><td>double</td><td>10m �̵��Ͽ��� �� �߻��ϴ� �����Ÿ����� �����̴�.(����:m)</td></tr>
 *	<tr><td><b>varianceDirection</b></td><td>double</td><td>360�� ȸ���Ͽ��� �� �߻��ϴ� ���Ⱒ������ �����̴�.(����:degree)</td></tr>
 *	<tr><td><b>safeRadius</b></td><td>double</td><td>�̵��ϴ� ��ü�� �κ��� �����ϴ� ������ �������̴�.(����:m)</td></tr>
 *	<tr><td><b>maximumVelocity</b></td><td>double</td><td>�̵� ��ġ�� �ְ�ӵ� �����̴�.</td></tr>
 *	<tr><td><b>acceleration</b></td><td>double</td><td>�̵� ��ġ�� ���ӵ��̴�.</td></tr>
 *	</table></center>
 */
class Mobility : public Application
{
public:
	Mobility(void) { };
	virtual ~Mobility(void) { };

public:
	/**
	 *	Mobility API�� �ʱ�ȭ �ϴ� ǥ�� �Լ��̴�.
	 *  Mobility Component�κ��� �Ķ���͸� �޾� Mobility API�� ���� �� �޸𸮸� �ʱ�ȭ �ϰ�,
	 *	Mobility API���� ����ϴ� ���̺귯������ �ʱ�ȭ �Ѵ�.
	 *	@param parameter �ʱ�ȭ�� �ʿ��� �Ķ����.
	 *	@return true - �ʱ�ȭ ����<br>
	 *			false - �ʱ�ȭ ����<br>
	 */
	virtual bool initialize(Property parameter) = 0;

	/**
	 *	Mobility API�� ���� �ϴ� ǥ�� �Լ��̴�.
	 *  Mobility API���� ����ϴ� �޸𸮳� �ٸ� ���̺귯���� �����Ѵ�.
	 *	@return true - ���� ����<br>
	 *			false - ���� ����<br>
	 */
	virtual bool finalize(void) = 0;

	/**
	 *	Mobility API�� Ȱ��ȭ �ϴ� ǥ�� �Լ��̴�.
	 *	�� �Լ��� ȣ��Ǹ� Mobility�� actuator�� servo on�ϰ� �ǰ� Mobility�� ������ �� �ִ�.
	 *	@return true - Ȱ��ȭ ����<br>
	 *			false - Ȱ��ȭ ����<br>
	 */
	virtual bool enable(void) = 0;

	/**
	 *	Mobility API�� ��Ȱ��ȭ �ϴ� ǥ�� �Լ��̴�.
	 *	�� �Լ��� ȣ��Ǹ� Mobility�� actuatorf�� servo off�ϰ� �ǰ� Mobility�� ������ �� ����.
	 *	@return true - ��Ȱ��ȭ ����<br>
	 *			false - ��Ȱ��ȭ ����<br>
	 */	
	virtual bool disable(void) = 0;

	/**
	 *	Mobility API�� �ĸ����͸� �����ϴ� ǥ�� �Լ��̴�.
	 *	Mobility�� �ĸ����͸� �����԰� ���ÿ� �ִ�ӵ�, ���ӵ� ���� ���������� actuator�� �ݿ��� �ȴ�.
	 *	@param parameter Mobility API�� �ʿ��� �Ķ����.
	 *	@return true - �ĸ����� ���� ����<br>
	 *			false - �Ķ���� ���� ����<br>
	 */
	virtual bool setParameter(Property parameter) = 0;

	/**
	 *	Mobility API�� ������ �ִ� �ĸ����� ������ ��� ǥ�� �Լ��̴�.
	 *	@return parameter - Mobility API�� �Ķ����<br>
	 */
	virtual Property getParameter(void) = 0;

	/**
	 *	�κ��� ��ġ�� �����ϴ� ǥ�� �Լ��̴�.
	 *	@param position �κ��� ��ġ.
	 *	@return true - ���� ����<br>
	 *			false - ���� ����<br>
	 */
	virtual bool setPosition(ObjectLocation position) = 0;

	/**
	 *	�κ��� ��ġ�� ��� ǥ�� �Լ��̴�.
	 *	@param position �κ��� ��ġ.
	 *	@return true - ��ȿ�� ������<br>
	 *			false - ��ȿ���� ���� ������<br>
	 */
	virtual bool getPosition(ObjectLocation *position) = 0;

	/**
	 *	�κ��� ���� ������ ���� ������ ȸ���� ��� ǥ�� �Լ��̴�.
	 *	@param leftEncoder ������ ���� ������ ȸ����.
	 *	@param rightEncoder ������ ������ ������ ȸ����.
	 *	@return true - ��ȿ�� ������<br>
	 *			false - ��ȿ���� ���� ������<br>
	 */
	virtual bool readEncoder(long *leftEncoder, long *rightEncoder) = 0;

	/**
	 *	�Է� �Ÿ���ŭ �κ��� ������Ű�� ǥ�� �Լ��̴�.
	 *	@param distance ���� �Ÿ�(����:m).
	 *	@return true - ��� ������ ����<br>
	 *			false - ��� ������ ����<br>
	 */
	virtual bool move(double distance) = 0;

	/**
	 *	�Է� �Ÿ���ŭ �κ��� ȸ����Ű�� ǥ�� �Լ��̴�.
	 *	@param degree ȸ�� ����(����:��).
	 *	@return true - ��� ������ ����<br>
	 *			false - ��� ������ ����<br>
	 */
	virtual bool rotate(double degree) = 0;

	/**
	 *	�Է� �����ӵ�, ȸ���ӵ��� �κ��� �����̴� ǥ�� �Լ��̴�.
	 *	@param forwardVelocity ���� �ӵ�(m/s).
	 *	@param angularVelocity ȸ�� �ӵ�(rad/s).
	 *	@return true - ��� ������ ����<br>
	 *			false - ��� ������ ����<br>
	 */
	virtual bool drive(double forwardVelocity, double angularVelocity) = 0;

	/**
	 *	Mobility�� ���ߴ� ǥ�� �Լ��̴�.
	 *	�� �Լ��� Mobility�� �����Ǿ� �ִ� ���ӵ��� �����ϱ� ������ �����ؼ� ���⶧ ������ �Ÿ��� ����ؾ��Ѵ�.
	 *	@return true - ��� ������ ����.<br>
	 *			false - ��� ������ ����.<br>	
	 */
	virtual bool stop(void) = 0;

	/**
	 *	Mobility�� �����̰� �ִ����� Ȯ���ϴ� ǥ�� �Լ��̴�.
	 *	@return true - �����̰� �ִ� ����.<br>
	 *			false - �����ִ� ����.<br>	
	 */
	virtual bool isWheelRunning(void) = 0;

	/**
	 *	Mobility���� �ֱ������� ������ �� �ְԱ� �����ϴ� ǥ�� callback �Լ��̴�.
	 *	���� �ֱ�� Mobility Component�� �����ֱ�� �����ϸ�, �� �Լ��� none blocking ���°� �Ǿ�� �Ѵ�.
	 *	@return true - ������ ����.<br>
	 *			false - ������ ����.<br>	
	 */
	virtual bool execute(void) = 0;

	/**
	 *	Mobility���� �ֱ������� ������ �� �ְԱ� �����ϴ� ǥ�� callback �Լ��̴�.
	 *	���� �ֱ�� Mobility Component�� �����ֱ�� �����ϸ� �����ֱ�� �����ϴ�.
	 *	�� �Լ��� none blocking ���°� �Ǿ�� �Ѵ�.
	 *	@return true - ������ ����.<br>
	 *			false - ������ ����.<br>	
	 */
	virtual bool update(void) = 0;
};

};

#endif
