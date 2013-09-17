#ifndef _COLORRECOGNITION_H_
#define _COLORRECOGNITION_H_

#include "OprosApi.h"

// ����
/**
 *	�����ν� API�� �̹��� ������ �Է¹޾� Ư���� ������ �ν��ϴ� �������̽��̴�.
 *	<center><table border=0><tr><td colspan=3><center><b>GlobalMap API���� ����ϴ� Parameter</b></center></td></tr>
 *	<tr><td bgcolor=#dddddd><center><b>Index</b></center></td><td bgcolor=#dddddd><center><b>Type of Value</b></center></td><td bgcolor=#dddddd><center><b>Description</b></center></td></tr>
 *	<tr><td><b>dbName</b></td><td>string</td><td>�����ν� API���� ����� �����ͺ��̽� ���Ϸμ� �÷��� �� ���� ������ ���ԵǾ� �ִ�.</td></tr>
 *	</table></center>
 */
class ColorRecognition : public OprosApi
{
public:
	ColorRecognition(void) { };
	virtual ~ColorRecognition(void) { };

public:
	/**
	 *	�̹������� ���� �ν��Ѵ�.
	 *	@param image �ν��� ������ �ִ� �̹���
	 *	@param width �̹����� ��
	 *	@param height �̹����� ����
	 *	@param pixelByte �� �ȼ��� ������ �޸��� ũ��
	 *	@return ���� �ν��� ����� VisionRecognitionResult�������� ��ȯ�Ѵ�.<br>
	 */
	virtual std::valarray<VisionRecognitionResult> recognize(unsigned char *image, int width, int height, int pixelbyte) = 0;

	/**
	 *	Database�� �� �����͸� �߰��Ѵ�.
	 *	@param image �ν��� ��ü�� �ִ� �̹���
	 *	@param name �� ������ �̸�
	 *	@param min1 ù��° ä��(Hue)�� �ּ� ����
	 *	@param max1 ù��° ä��(Hue)�� �ִ� ����
	 *	@param min2 �ι�° ä��(Saturation)�� �ּ� ����
	 *	@param max2 �ι�° ä��(Saturation)�� �ִ� ����
	 *	@param min3 ����° ä��(Value)�� �ּ� ����
	 *	@param max3 ����° ä��(Value)�� �ִ� ����
	 *	@return true - ���������� �� ������ ������ ��� true ���� ��ȯ�Ѵ�.<br>
	 *			false - �� ���� ������ ������ ��� false ���� ��ȯ�Ѵ�.<br>
	 */
	virtual bool addItem(std::string name, unsigned char min1, unsigned char max1, unsigned char min2, unsigned char max2, unsigned char min3, unsigned char max3) = 0;

	/**
	 *	�� Database���� addItem���� �ԷµǾ��� name�� �� �����͸� �����Ѵ�.
	 *	@param name ���� �� �������� �̸�
	 *	@return true - ���������� �� ������ ������ ��� true ���� ��ȯ�Ѵ�.<br>
	 *			false - �� ���� ������ ������ ��� false ���� ��ȯ�Ѵ�.<br>
	 */
	virtual bool removeItem(std::string name) = 0;

	/**
	 *	�� Database���� addItem���� �ԷµǾ��� name�� �� �����͸� �����Ѵ�.
	 *	@param name ���� �� �������� �̸�
	 *	@return true - ���������� �� ���� �����ͺ��̽��� �ʱ�ȭ�� ��� true ���� ��ȯ�Ѵ�.<br>
	 *			false - �� ���� �����ͺ��̽��� �ʱ�ȭ�� ������ ��� false ���� ��ȯ�Ѵ�.<br>
	 */
	virtual bool cleanUpItems(void) = 0;
};


#endif
