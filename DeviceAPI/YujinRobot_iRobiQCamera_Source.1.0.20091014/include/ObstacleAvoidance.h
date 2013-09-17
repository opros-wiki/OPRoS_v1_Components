#ifndef _OBSTACLE_AVOIDANCE_H_
#define _OBSTACLE_AVOIDANCE_H_

#include "Application.h"
#include "OprosApiTypes.h"

namespace OPRoS
{
// ����
/**
 *	ObstacleAvoidance API�� �̵� �κ��� ���� ������ ���� ���� ��ֹ��� ȸ���ϸ鼭 ���� ��θ� �����ϴ� ǥ�� API�̴�. 
 *	��� ��ֹ� ȸ�� API�� �� Ŭ������ ��ӹ޾� �����Ǿ�� �Ѵ�.
 *	ObstacleAvoidance API�� OPRoS Navigation Component�� ���� ����ȴ�. 
 *	ObstacleAvoidance API�� Navigation Component�κ��� �ĸ����͸� �޾� ���� �� �޸𸮸� �ʱ�ȭ �Ѵ�.
 *	ObstacleAvoidance API�� ���� ���̺귯���� �����Ǹ� Navigation Component���� �ε��Ͽ� ���ȴ�.
 *	<center><table border=0>
 *	<tr><td colspan=3><center><b>ObstacleAvoidance API���� ����ϴ� Parameter</b></center></td></tr>
 *	<tr><td bgcolor=#dddddd><center><b>Index</b></center></td><td bgcolor=#dddddd><center><b>Type of Value</b></center></td><td bgcolor=#dddddd><center><b>Description</b></center></td></tr>
 *	<tr><td><b>mapFile</b></td> <td>std::string</td> <td>globalMap API���� �ε�� �� ������ �̸��̴�.</td></tr>
 *	<tr><td><b>cellWidth</b></td> <td>double</td> <td>�ʿ� �ִ� �� �ȼ��� ���� �ʺ��̴�.(����:m)</td></tr>
 *	<tr><td><b>varianceDistance</b></td> <td>double</td> <td>�����Ƽ �Ķ���Ϳ��� �������� �����Ÿ����� �����̴�.</td></tr>
 *	<tr><td><b>varianceDirection</b></td> <td>double</td> <td>�����Ƽ �Ķ���Ϳ��� �������� ���Ⱒ������ �����̴�.</td></tr>
 *	<tr><td><b>safeRadius</b></td> <td>double</td> <td>�����Ƽ �Ķ���Ϳ��� �������� ���������� �������̴�.</td></tr>
 *	<tr><td><b>maximumVelocity</b></td> <td>double</td> <td>�����Ƽ �Ķ���Ϳ��� �������� �ְ�ӵ� �����̴�.</td></tr>
 *	<tr><td><b>acceleration</b></td> <td>double</td> <td>�����Ƽ �Ķ���Ϳ��� �������� ���ӵ��̴�.</td></tr>
 *	<tr><td><b>startAngle</b></td> <td>double</td> <td>��������ĳ�� �Ķ���Ϳ��� �������� �������� �����̴�.</td></tr>
 *	<tr><td><b>endAngle</b></td> <td>double</td> <td>��������ĳ�� �Ķ���Ϳ��� �������� ������ ���������̴�.</td></tr>
 *	<tr><td><b>minimumRange</b></td> <td>double</td> <td>��������ĳ�� �Ķ���Ϳ��� �������� �������� �ּ�ġ�̴�.</td></tr>
 *	<tr><td><b>maximumRange</b></td> <td>double</td> <td>��������ĳ�� �Ķ���Ϳ��� �������� �������� �ִ�ġ�̴�.</td></tr>
 *	<tr><td><b>sensorCount</b></td> <td>int</td> <td>��������ĳ���� ���� ���� ���� �����̴�.</td></tr>
 *	<tr><td><b>sensorVariance</b></td> <td>double</td> <td>��������ĳ�� �Ķ���Ϳ��� �������� ��ġ �������̴�.</td></tr>
 *	<tr><td><b>x</b></td> <td>double</td> <td>��������ĳ�� �Ķ���Ϳ��� �������� �������ġ�����̴�.</td></tr>
 *	<tr><td><b>y</b></td> <td>double</td> <td>��������ĳ�� �Ķ���Ϳ��� �������� �������ġ�����̴�.</td></tr>
 *	<tr><td><b>theta</b></td> <td>double</td> <td>��������ĳ�� �Ķ���Ϳ��� �������� ��������������̴�.
 *	NavigationComponent������ �������� roll, pitch, yaw �� yaw�� ��ȿ�ϹǷ� yaw���� theta�� �ִ´�.</td></tr>
 *	<tr><td><b>startPositionX</b></td> <td>double</td> <td>���� �ʿ����� �����Ƽ ���� ��ġ�� ��Ÿ����.</td></tr>
 *	<tr><td><b>startPositionY</b></td> <td>double</td> <td>���� �ʿ����� �����Ƽ ���� ��ġ�� ��Ÿ����.</td></tr>
 *	<tr><td><b>startPositionTheta</b></td> <td>double</td> <td>���� �ʿ����� �����Ƽ ���� ������ ��Ÿ����.</td></tr>
 *	</table></center>
 */
class ObstacleAvoidance : public Application
{
public:
	ObstacleAvoidance(void) { };
	virtual ~ObstacleAvoidance(void) { };

public:
	/**
	 *	ObstacleAvoidance API�� �ʱ�ȭ �ϴ� ǥ�� �Լ��̴�.
	 *  ������Ʈ�κ��� �Ķ���͸� �޾� ObstacleAvoidance API�� ���� �� �޸𸮸� �ʱ�ȭ �Ѵ�. 
	 *	@param parameter �ʱ�ȭ�� �ʿ��� �Ķ����.
	 *	@return true - �ʱ�ȭ ����<br>
	 *			false - �ʱ�ȭ ����<br>
	 */
	virtual bool initialize(Property parameter) = 0;

	/**
	 *	ObstacleAvoidance API�� ���� �ϴ� ǥ�� �Լ��̴�.
	 *  ObstacleAvoidance API���� ����ϴ� �޸𸮳� �ٸ� ���̺귯���� �����Ѵ�.
	 *	@return true - ���� ����<br>
	 *			false - ���� ����<br>
	 */
	virtual bool finalize(void) = 0;

	/**
	 *	ObstacleAvoidance API�� Ȱ��ȭ �ϴ� ǥ�� �Լ��̴�.
	 *	@return true - Ȱ��ȭ ����<br>
	 *			false - Ȱ��ȭ ����<br>
	 */
	virtual bool enable(void) = 0;

	/**
	 *	ObstacleAvoidance API�� ��Ȱ��ȭ �ϴ� ǥ�� �Լ��̴�.
	 *	@return true - ��Ȱ��ȭ ����<br>
	 *			false - ��Ȱ��ȭ ����<br>
	 */	
	virtual bool disable(void) = 0;

	/**
	 *	ObstacleAvoidance API�� �ĸ����͸� �����ϴ� ǥ�� �Լ��̴�.
	 *	@param parameter ObstacleAvoidance API�� �ʿ��� �Ķ����.
	 *	@return true - �ĸ����� ���� ����<br>
	 *			false - �Ķ���� ���� ����<br>
	 */
	virtual bool setParameter(Property parameter) = 0;

	/**
	 *	ObstacleAvoidance API�� �ĸ����͸� ��� ǥ�� �Լ��̴�.
	 *	@return parameter - ObstacleAvoidance API�� �Ķ����<br>
	 */
	virtual Property getParameter(void) = 0;
	/**
	 *	�κ��� ���� ��ġ�� �����ϴ� ǥ�� �Լ��̴�.
	 *	@param position �κ��� ���� ��ġ(x, y, theta).
	 *	@return ����.
	 */
	virtual void setPosition(ObjectLocation position) = 0;

	/**
	 *	�κ��� ���� ��ġ�� ������ ��ġ ������ �׸��� ���� �����͸� �̿��� ��ֹ��� ȸ���ϴ� ǥ�� �Լ��̴�.
	 *  ��ֹ��� ȸ���ϸ鼭 ���������� �̵��ϱ� ���� �κ��� ���� �ӵ��� ȸ�� �ӵ��� ����Ѵ�.
	 *	@param currentPosition �κ��� ���� ��ġ.
	 *	@param targetPosition �κ��� ������ ��ġ.
	 *	@param laserData ������ ��ĳ�� ������ ��ĵ�� ������.
	 *	@param forwardVelocity ���� �����Ƽ�� ���� �ӵ�.
	 *	@param angularVelocity ���� �����Ƽ�� ȸ�� �ӵ�.
	 *	@return ����.
	 */
	virtual void avoid(ObjectLocation currentPosition, ObjectLocation targetPosition, double laserData[], double *forwardVelocity, double *angularVelocity) = 0;

	/**
	 *	������ ��ġ������ ���� �Ÿ��� ��ȯ�ϴ� ǥ�� �Լ��̴�.
	 *	@return ������������ ���� �Ÿ�(����:m).
	 */
	virtual double getRemainingDistance(void) = 0;
};

};

#endif
