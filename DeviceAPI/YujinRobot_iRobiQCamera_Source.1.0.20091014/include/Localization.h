#ifndef _LOCALIZATION_H_
#define _LOCALIZATION_H_

#include "Application.h"
#include "GlobalMap.h"
#include "OprosApiTypes.h"

namespace OPRoS
{
// ����
/**
 *	Localization API�� �̵� �κ��� ���� ������ ���� �κ��� ��ġ�� �����ϴ� ǥ�� API�̴�. 
 *	��� ��ġ �����ϴ� API�� �� Ŭ������ ��ӹ޾� �����Ǿ�� �Ѵ�.
 *	Localization API�� OPRoS Navigation Component�� ���� ����ȴ�. 
 *	Localization API�� Navigation Component�κ��� �ĸ����͸� �޾� ���� �� �޸𸮸� �ʱ�ȭ �Ѵ�.
 *	Localization API�� ���� ���̺귯���� �����Ǹ� Navigation Component���� �ε��Ͽ� ���ȴ�.
 *	<center><table border=0>
 *	<tr><td colspan=3><center><b>Localization API���� ����ϴ� Parameter</b></center></td></tr>
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
class Localization : public Application
{
public:
	Localization(void) { };
	virtual ~Localization(void) { };

public:
	/**
	 *	Localization API�� �ʱ�ȭ �ϴ� ǥ�� �Լ��̴�.
	 *  ������Ʈ�κ��� �Ķ���͸� �޾� Localization API�� ���� �� �޸𸮸� �ʱ�ȭ �Ѵ�. 
	 *	@param parameter �ʱ�ȭ�� �ʿ��� �Ķ����.
	 *	@return true - �ʱ�ȭ ����<br>
	 *			false - �ʱ�ȭ ����<br>
	 */
	virtual bool initialize(Property parameter) = 0;

	/**
	 *	Localization API�� ���� �ϴ� ǥ�� �Լ��̴�.
	 *  Localization API���� ����ϴ� �޸𸮳� �ٸ� ���̺귯���� �����Ѵ�.
	 *	@return true - ���� ����<br>
	 *			false - ���� ����<br>
	 */
	virtual bool finalize(void) = 0;

	/**
	 *	Localization API�� Ȱ��ȭ �ϴ� ǥ�� �Լ��̴�.
	 *	@return true - Ȱ��ȭ ����<br>
	 *			false - Ȱ��ȭ ����<br>
	 */
	virtual bool enable(void) = 0;

	/**
	 *	Localization API�� ��Ȱ��ȭ �ϴ� ǥ�� �Լ��̴�.
	 *	@return true - ��Ȱ��ȭ ����<br>
	 *			false - ��Ȱ��ȭ ����<br>
	 */	
	virtual bool disable(void) = 0;

	/**
	 *	Localization API�� �ĸ����͸� �����ϴ� ǥ�� �Լ��̴�.
	 *	@param parameter Localization API�� �ʿ��� �Ķ����.
	 *	@return true - �ĸ����� ���� ����<br>
	 *			false - �Ķ���� ���� ����<br>
	 */
	virtual bool setParameter(Property parameter) = 0;

	/**
	 *	Localization API�� �ĸ����͸� ��� ǥ�� �Լ��̴�.
	 *	@return parameter - Localization API�� �Ķ����<br>
	 */
	virtual Property getParameter(void) = 0;

	/**
	 *	�κ��� ���� ��ġ�� �����ϴ� ǥ�� �Լ��̴�.
	 *	@param position �κ��� ���� ��ġ(x, y, theta).
	 *	@return ����.
	 */
	virtual void setPosition(ObjectLocation position) = 0;

	/**
	 *	������ �κ��� ���� ��ġ�� ��� ǥ�� �Լ��̴�.
	 *	@param position ������ �κ��� ���� ��ġ(x, y, theta).
	 *	@return true - ��ȿ�� ��.
	 *			false - ��ȿ���� ���� ��.
	 */
	virtual bool getPosition(ObjectLocation *position) = 0;

	/**
	 *	�����ʰ� ������ ��ĳ�� ���� ������, �����Ƽ�� �̵����� �̿��� �κ��� ��ġ�� �����ϴ� ǥ�� �Լ��̴�.
	 *	@param globalMap ������.
	 *	@param laserData ������ ��ĳ�� ������ ��ĵ�� ������.
	 *	@param forwardDelta �κ��� ������.
	 *	@param angularDelta �κ��� ȸ����.
	 *	@return ����.
	 */
	virtual void localize(GlobalMap *globalMap, double laserData[], double deltaForward, double deltaAngular) = 0;

	/**
	 *	�����ʰ� ������ ��ĳ�� ���� ������, �����Ƽ�� ������Ʈ���� �̿��� �κ��� ��ġ�� �����ϴ� ǥ�� �Լ��̴�.
	 *	@param globalMap ������.
	 *	@param laserData ������ ��ĳ�� ������ ��ĵ�� ������.
	 *	@param robotPosition �����Ƽ�κ��� ���� �κ��� ���� ��ġ.
	 *	@return ����.
	 */
	virtual void localize(GlobalMap *globalMap, double laserData[], ObjectLocation robotPosition) = 0;
};

};

#endif