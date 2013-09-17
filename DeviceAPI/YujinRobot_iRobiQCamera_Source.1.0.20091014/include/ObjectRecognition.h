#ifndef _OBJECTRECOGNITION_H_
#define _OBJECTRECOGNITION_H_

#include "Application.h"
#include "OprosApiTypes.h"

namespace OPRoS
{

// ����
/**
 *	�繰�ν� API�� �̹��� ������ �Է¹޾� �ȸ��� �ν��ϴ� �������̽��̴�.
 *	<center><table border=0><tr><td colspan=3><center><b>GlobalMap API���� ����ϴ� Parameter</b></center></td></tr>
 *	<tr><td bgcolor=#dddddd><center><b>Index</b></center></td><td bgcolor=#dddddd><center><b>Type of Value</b></center></td><td bgcolor=#dddddd><center><b>Description</b></center></td></tr>
 *	<tr><td><b>dbName</b></td><td>string</td><td>�繰�ν� API���� ����� �����ͺ��̽� ���Ϸμ� ��ü�� ���� ������ ���ԵǾ� �ִ�.</td></tr>
 *	</table></center>
 */
class ObjectRecognition : public Application
{
public:
	ObjectRecognition(void) { };
	virtual ~ObjectRecognition(void) { };

public:
	/**
	 *	�̹������� ��ü�� �ν��Ѵ�.
	 *	@param image �ν��� ��ü�� �ִ� �̹���
	 *	@param width �̹����� ��
	 *	@param height �̹����� ����
	 *	@param pixelByte �� �ȼ��� ������ �޸��� ũ��
	 *	@return �繰 �ν��� ����� VisionRecognitionResult�������� ��ȯ�Ѵ�.<br>
	 */
	virtual std::valarray<VisionRecognitionResult>recognize(unsigned char *image, int width, int height, int pixelbyte) = 0;

	/**
	 *	Database�� ��ü �����͸� �߰��Ѵ�.
	 *	@param fileName ��ü �����͸� ���� �� �����ͺ��̽�
	 *	@return true - ���������� ��ü �����͸� ������ ��� true ���� ��ȯ�Ѵ�.<br>
	 *			false - ��ü ������ ������ ������ ��� false ���� ��ȯ�Ѵ�.<br>
	 */
	virtual bool addItem(std::string fileName) = 0;

	/**
	 *	��ü Database���� addItem���� �ԷµǾ��� name�� ��ü �����͸� �����Ѵ�.
	 *	@param name ���� ��ü �������� �̸�
	 *	@return true - ���������� �繰�ν� ������ ������ ��� true ���� ��ȯ�Ѵ�.<br>
	 *			false - �繰�ν� ���� ������ ������ ��� false ���� ��ȯ�Ѵ�.<br>
	 */
	virtual bool removeItem(std::string name) = 0;

	/**
	 *	��ü Database�� ��� �����Ѵ�.
	 *	@return true - ���������� �繰�ν� ���� �����ͺ��̽��� �ʱ�ȭ�� ��� true ���� ��ȯ�Ѵ�.<br>
	 *			false - �繰�ν� ���� �����ͺ��̽��� �ʱ�ȭ�� ������ ��� false ���� ��ȯ�Ѵ�.<br>
	 */
	virtual bool cleanUpItems(void) = 0;
};

};

#endif
