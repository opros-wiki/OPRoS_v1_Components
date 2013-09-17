#ifndef _GLOBAL_MAP_H_
#define _GLOBAL_MAP_H_

#include "Application.h"

namespace OPRoS
{
// ����
/**
 *	GlobalMap API�� �̵� �κ��� ���� ������ ���� ������ ������ �����ϴ� ǥ�� API�̴�. 
 *	��� �������� �����ϴ� API�� �� Ŭ������ ��ӹ޾� �����Ǿ�� �Ѵ�.
 *	GlobalMap API�� OPRoS Navigation Component�� ���� ����ȴ�. 
 *	GlobalMap API�� Navigation Component�κ��� �ĸ����͸� �޾� ���� �� �޸𸮸� �ʱ�ȭ �ϰ� �ε�� ����� �������� �����ϴ� API�� 
 *	������ �־����� ������ ������ �о� �޸𸮿� �����Ų��. 
 *	GlobalMap API�� ���� ���̺귯���� �����Ǹ� Navigation Component���� �ε��Ͽ� ���ȴ�.
 *	<center><table border=0><tr><td colspan=3><center><b>GlobalMap API���� ����ϴ� Parameter</b></center></td></tr>
 *	<tr><td bgcolor=#dddddd><center><b>Index</b></center></td><td bgcolor=#dddddd><center><b>Type of Value</b></center></td><td bgcolor=#dddddd><center><b>Description</b></center></td></tr>
 *	<tr><td><b>cellWidth</b></td><td>double</td><td>������ ������ �� �ȼ��� ���� �Ÿ��� �ǹ��Ѵ�.(����:m)</td></tr>
 *	<tr><td><b>mapFile</b></td><td>double</td><td>�������� �������� �ǹ��Ѵ�. (����:�ȼ���)</td></tr>
 *	<tr><td><b>safeRadius</b></td><td>double</td><td>�������� �������� �ǹ��Ѵ�. (����:�ȼ���)</td></tr>
 *	</table></center>
 */
class GlobalMap : public Application
{
public:
	GlobalMap(void) { };
	virtual ~GlobalMap(void) { };

public:
	/**
	 *	������ �������� �� �ȼ��� ������ ���� �Ÿ��� ������ ǥ�� �����̴�.
	 *	���� : m
	 */
	double cellWidth;

	/**
	 *	������ �������� ������ ũ�⸦ ������ ǥ�� �����̴�.
	 *	���� : pixel��
	 */
	int width;

	/**
	 *	������ �������� ������ ũ�⸦ ������ ǥ�� �����̴�.
	 *	���� : pixel��
	 */
	int height;

	/**
	 *	������ �����͸� ������ ǥ�� �����̴�.
	 *	���� : 0~255�� ��
	 */
	unsigned char *mapData;

	/**
	 *	GlobalMap API�� �ʱ�ȭ �ϴ� ǥ�� �Լ��̴�.
	 *  ������Ʈ�κ��� �Ķ���͸� �޾� GlobalMap API�� ���� �� �޸𸮸� �ʱ�ȭ �ϰ� �����Ϸκ��� �����͸� �о���δ�. 
	 *	@param parameter �ʱ�ȭ�� �ʿ��� �Ķ����.
	 *	@return true - �ʱ�ȭ ����<br>
	 *			false - �ʱ�ȭ ����<br>
	 */
	virtual bool initialize(Property parameter) = 0;

	/**
	 *	GlobalMap API�� ���� �ϴ� ǥ�� �Լ��̴�.
	 *  GlobalMap API���� ����ϴ� �޸𸮳� �ٸ� ���̺귯���� �����Ѵ�.
	 *	@return true - ���� ����<br>
	 *			false - ���� ����<br>
	 */
	virtual bool finalize(void) = 0;

	/**
	 *	GlobalMap API�� Ȱ��ȭ �ϴ� ǥ�� �Լ��̴�.
	 *	@return true - Ȱ��ȭ ����<br>
	 *			false - Ȱ��ȭ ����<br>
	 */
	virtual bool enable(void) = 0;
	
	/**
	 *	GlobalMap API�� ��Ȱ��ȭ �ϴ� ǥ�� �Լ��̴�.
	 *	@return true - ��Ȱ��ȭ ����<br>
	 *			false - ��Ȱ��ȭ ����<br>
	 */	
	virtual bool disable(void) = 0;

	/**
	 *	GlobalMap API�� �ĸ����͸� �����ϴ� ǥ�� �Լ��̴�.
	 *	@param parameter GlobalMap API�� �ʿ��� �Ķ����.
	 *	@return true - �ĸ����� ���� ����<br>
	 *			false - �Ķ���� ���� ����<br>
	 */
	virtual bool setParameter(Property parameter) = 0;

	/**
	 *	GlobalMap API�� �ĸ����͸� ��� ǥ�� �Լ��̴�.
	 *	@return parameter - GlobalMap API�� �Ķ����<br>
	 */
	virtual Property getParameter(void) = 0;

	/**
	 *	�� ������ �о� GlobalMap API�� �� �����Ϳ� �����ϴ� ǥ�� �Լ��̴�.
	 *	@param fileName �� ������ �̸�.
	 *	@param cellWidth �� �������� �� �ȼ��� ���� ���� �Ÿ�.
	 *	@return true - �� ���� �б� ����<br>
	 *			false - �� ���� �б� ����<br>
	 */
	virtual bool loadMapFile(const char *fileName, double cellWidth) = 0;

	/**
	 *	GlobalMap API�� �� �����͸� ���Ϸ� �����ϴ� ǥ�� �Լ��̴�.
	 *	@param fileName ����� �� ������ �̸�.
	 *	@return true - �� ���� ���� ����<br>
	 *			false - �� ���� ���� ����<br>
	 */
	virtual bool saveMapFile(const char *fileName) = 0;

	/**
	 *	�����ʻ󿡼� ���� ��ġ�� ��ֹ� �����͸� ��� ǥ�� �Լ��̴�.
	 *	@param x ������ �󿡼� ���������� ���� ��ġ.
	 *	@param y ������ �󿡼� ���������� ���� ��ġ.
	 *	@return data - �� ������<br>
	 */
	virtual unsigned char getPixel(double x, double y) = 0;

	/**
	 *	�����ʻ󿡼� �ȼ� ��ġ�� ��ֹ� �����͸� ��� ǥ�� �Լ��̴�.
	 *	@param x ������ �󿡼� ���������� �ȼ� ��ġ.
	 *	@param y ������ �󿡼� ���������� �ȼ� ��ġ.
	 *	@return �� ������<br>
	 */
	virtual unsigned char getPixelCell(int x, int y) = 0;

	/**
	 *	�����ʻ��� ���� ��ġ�� ��ֹ��� ���� �����͸� ����ϴ� ǥ�� �Լ��Ѵ�.
	 *	@param x ������ �󿡼� ���������� ���� ��ġ.
	 *	@param y ������ �󿡼� ���������� ���� ��ġ.
	 *	@return data - �� ������<br>
	 */
	virtual void setPixel(double x, double y, unsigned char data) = 0;

	/**
	 *	�����ʻ��� �ȼ� ��ġ�� ��ֹ��� ���� �����͸� ����ϴ� ǥ�� �Լ��Ѵ�.
	 *	@param x ������ �󿡼� ���������� �ȼ� ��ġ.
	 *	@param y ������ �󿡼� ���������� �ȼ� ��ġ.
	 *	@return data - �� ������<br>
	 */
	virtual void setPixelCell(int x, int y, unsigned char data) = 0;

	/**
	 *	�Է��ϴ� ���� ��ġ�� ������ ���� ���� �ȿ� �ִ����� Ȯ���ϴ� ǥ�� �Լ��Ѵ�.
	 *	@param x ������ �󿡼� ���������� ���� ��ġ.
	 *	@param y ������ �󿡼� ���������� ���� ��ġ.
	 *	@return true - ������ ���� �ȿ� ����<br>
	 *			false - ������ ���� �ۿ� ����<br>
	 */
	virtual bool isIn(double x, double y) = 0;

	/**
	 *	�Է��ϴ� �ȼ� ��ġ�� ������ ���� ���� �ȿ� �ִ����� Ȯ���ϴ� ǥ�� �Լ��Ѵ�.
	 *	@param x ������ �󿡼� ���������� �ȼ� ��ġ.
	 *	@param y ������ �󿡼� ���������� �ȼ� ��ġ.
	 *	@return true - ������ ���� �ȿ� ����<br>
	 *			false - ������ ���� �ۿ� ����<br>
	 */
	virtual bool isInCell(int x, int y) = 0;

	/**
	 *	������ �󿡼� �� ���� ���� ��ġ ���� ����ġ ������ ū ��ֹ��� �ִ����� Ȯ���ϴ� ǥ�� �Լ��Ѵ�.
	 *	@param x1 ������ �󿡼� �� ���� ���� ������������ ���� ��ġ.
	 *	@param y1 ������ �󿡼� �� ���� ���� ������������ ���� ��ġ.
	 *	@param x2 ������ �󿡼� �ٸ� �� ���� ���� ������������ ���� ��ġ.
	 *	@param y2 ������ �󿡼� �ٸ� �� ���� ���� ������������ ���� ��ġ.
	 *	@param data ��ֹ��� �ν��ϱ� ���� ����ġ ��.
	 *	@return true - ��ֹ��� ����<br>
	 *			false - ��ֹ��� ����<br>
	 */
	virtual bool isIntersect(double x1, double y1, double x2, double y2, unsigned char data) = 0;

	/**
	 *	������ �󿡼� �� ���� �ȼ� ��ġ ���� ����ġ ������ ū ��ֹ��� �ִ����� Ȯ���ϴ� ǥ�� �Լ��Ѵ�.
	 *	@param x1 ������ �󿡼� �� ���� ���� ������������ �ȼ� ��ġ.
	 *	@param y1 ������ �󿡼� �� ���� ���� ������������ �ȼ� ��ġ.
	 *	@param x2 ������ �󿡼� �ٸ� �� ���� ���� ������������ �ȼ� ��ġ.
	 *	@param y2 ������ �󿡼� �ٸ� �� ���� ���� ������������ �ȼ� ��ġ.
	 *	@param data ��ֹ��� �ν��ϱ� ���� ����ġ ��.
	 *	@return true - ��ֹ��� ����<br>
	 *			false - ��ֹ��� ����<br>
	 */
	virtual bool isIntersectCell(int x1, int y1, int x2, int y2, unsigned char data) = 0;

	/**
	 *	������ �󿡼� ���� ��ġ�� �� ���� �����ϴ� ���� �׸��� ǥ�� �Լ��Ѵ�.
	 *	@param x1 ������ �󿡼� �� ���� ���� ������������ ���� ��ġ.
	 *	@param y1 ������ �󿡼� �� ���� ���� ������������ ���� ��ġ.
	 *	@param x2 ������ �󿡼� �ٸ� �� ���� ���� ������������ ���� ��ġ.
	 *	@param y2 ������ �󿡼� �ٸ� �� ���� ���� ������������ ���� ��ġ.
	 *	@param data �����ʿ� ������ ��ֹ� ��.
	 *	@return ����<br>
	 */
	virtual void drawLine(double x1, double y1, double x2, double y2, unsigned char data) = 0;

	/**
	 *	������ �󿡼� ���� ��ġ�� �� ���� �����ϴ� ���� �׸��� ǥ�� �Լ��Ѵ�.
	 *	@param x1 ������ �󿡼� �� ���� ���� ������������ �ȼ� ��ġ.
	 *	@param y1 ������ �󿡼� �� ���� ���� ������������ �ȼ� ��ġ.
	 *	@param x2 ������ �󿡼� �ٸ� �� ���� ���� ������������ �ȼ� ��ġ.
	 *	@param y2 ������ �󿡼� �ٸ� �� ���� ���� ������������ �ȼ� ��ġ.
	 *	@param data �����ʿ� ������ ��ֹ� ��.
	 *	@return ����<br>
	 */
	virtual void drawLineCell(int x1, int y1, int x2, int y2, unsigned char data) = 0;

	/**
	 *	�������� ��ֹ��� ���� ����ġ ������ ū ��ֹ��� ���� ������ŭ Ȯ���ϴ� ǥ�� �Լ��Ѵ�.
	 *	@param bulge Ȯ���ų ����ũ��.
	 *	@param threshold Ȯ���ų ��ֹ��� ����ġ ��.
	 *	@param data Ȯ�念���� �� ��ֹ� ������ ��.
	 *	@return ����<br>
	 */
	virtual void expandObstacle(int bulge, unsigned char threshold, unsigned char data) = 0;

	/**
	 *	�������� �޸� ������ ���Ҵ��ϴ� ǥ�� �Լ��Ѵ�.
	 *	@param offsetX ���������� ���� ��ġ.
	 *	@param offsetY ���������� ���� ��ġ.
	 *	@param width ������ ���� ��ġ�κ����� ��.
	 *	@param height ������ ���� ��ġ�κ����� ����.
	 *	@return true - �������� �޸� �Ҵ� ����<br>
	 *			false - �������� �޸� �Ҵ� ����<br>
	 */
	virtual bool reallocate(int offsetX, int offsetY, int width, int height) = 0;

	/**
	 *	������ �󿡼� �������� ���� ��ġ�� �ȼ� ��ġ�� ��ȯ�ϴ� ǥ�� �Լ��Ѵ�.
	 *	@param x ������ �󿡼� ���������� ���� ��ġ.
	 *	@return ������ �󿡼� ���������� �ȼ� ��ġ<br>
	 */
	virtual int m2CUx(double x) = 0;

	/**
	 *	������ �󿡼� �������� ���� ��ġ�� �ȼ� ��ġ�� ��ȯ�ϴ� ǥ�� �Լ��Ѵ�.
	 *	@param x ������ �󿡼� ���������� ���� ��ġ.
	 *	@return ������ �󿡼� ���������� �ȼ� ��ġ<br>
	 */
	virtual int m2CUy(double y) = 0;

	/**
	 *	������ �󿡼� �������� �ȼ� ��ġ�� ���� ��ġ�� ��ȯ�ϴ� ǥ�� �Լ��Ѵ�.
	 *	@param x ������ �󿡼� ���������� �ȼ� ��ġ.
	 *	@return ������ �󿡼� ���������� ���� ��ġ<br>
	 */
	virtual double cu2Mx(int x) = 0;

	/**
	 *	������ �󿡼� �������� �ȼ� ��ġ�� ���� ��ġ�� ��ȯ�ϴ� ǥ�� �Լ��Ѵ�.
	 *	@param x ������ �󿡼� ���������� �ȼ� ��ġ.
	 *	@return ������ �󿡼� ���������� ���� ��ġ<br>
	 */
	virtual double cu2My(int y) = 0;
};

};

#endif
