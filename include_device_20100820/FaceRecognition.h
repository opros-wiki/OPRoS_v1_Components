#ifndef _FACERECOGNITION_H_
#define _FACERECOGNITION_H_

#include "OprosApi.h"

// ����
/**
 *	�ȸ��ν� API�� �̹��� ������ �Է¹޾� �ȸ��� �ν��ϴ� �������̽��̴�.
 *	<center><table border=0><tr><td colspan=3><center><b>GlobalMap API���� ����ϴ� Parameter</b></center></td></tr>
 *	<tr><td bgcolor=#dddddd><center><b>Index</b></center></td><td bgcolor=#dddddd><center><b>Type of Value</b></center></td><td bgcolor=#dddddd><center><b>Description</b></center></td></tr>
 *	<tr><td><b>dbName</b></td><td>string</td><td>�ȸ��ν� API���� ����� �����ͺ��̽� ���Ϸμ� �󱼿� ���� ������ ���ԵǾ� �ִ�.</td></tr>
 *	</table></center>
 */
class FaceRecognition : public OprosApi
{
public:
	FaceRecognition(void) { };
	virtual ~FaceRecognition(void) { };

public:
	/**
	 *	�̹������� �ȸ��� �ν��Ѵ�.
	 *	@param image �ν��� ���� �ִ� �̹���
	 *	@param width �̹����� ��
	 *	@param height �̹����� ����
	 *	@param pixelByte �� �ȼ��� ������ �޸��� ũ��
	 *	@return �ȸ� �ν��� ����� VisionRecognitionResult�������� ��ȯ�Ѵ�.<br>
	 */
	virtual std::valarray<VisionRecognitionResult>recognize(unsigned char *image, int width, int height, int pixelbyte) = 0;

	/**
	 *	Database�� �ȸ� �����͸� �߰��Ѵ�.
	 *	@param fileName �ȸ� �����͸� ���� �� �����ͺ��̽�
	 *	@return true - ���������� ���ν� ������ ������ ��� true ���� ��ȯ�Ѵ�.<br>
	 *			false - ���ν� ���� ������ ������ ��� false ���� ��ȯ�Ѵ�.<br>
	 */
	virtual bool addItem(std::string fileName) = 0;

	/**
	 *	�ȸ� Database���� addItem���� �ԷµǾ��� name�� �ȸ� �����͸� �����Ѵ�.
	 *	@param name ���� �ȸ� �������� �̸�
	 *	@return true - ���������� ���ν� ������ ������ ��� true ���� ��ȯ�Ѵ�.<br>
	 *			false - ���ν� ���� ������ ������ ��� false ���� ��ȯ�Ѵ�.<br>
	 */
	virtual bool removeItem(std::string name) = 0;

	/**
	 *	�ȸ� Database�� ��� �����Ѵ�.
	 *	@return true - ���������� ���ν� ���� �����ͺ��̽��� �ʱ�ȭ�� ��� true ���� ��ȯ�Ѵ�.<br>
	 *			false - ���ν� ���� �����ͺ��̽��� �ʱ�ȭ�� ������ ��� false ���� ��ȯ�Ѵ�.<br>
	 */
	virtual bool cleanUpItems(void) = 0;
};


#endif
