#ifndef _RECOGNITION_H_
#define _RECOGNITION_H_

#include "Application.h"
#include "OprosApiTypes.h"

namespace OPRoS
{

// ����
/**
 *	�ν� API�� �ֺ� ȯ���� �̹��� ������ ī�޶�� �Է¹��� �� �̸� �м��Ͽ� Ư���� ��ü��
 *	�̸�, ����, ��ġ �׸��� Ʋ���� ���� ���� ������ �ν��ϴµ� �ʿ��� �������̽��� ���Ѵ�.
 */
class Recognition : public Application
{
public:
	Recognition(void) { };
	virtual ~Recognition(void) { };

public:
	/**
	 *	�����ͺ��̽��� ���ο� ��ü �����͸� �߰��Ѵ�.
	 *	@param fileName ��ü �����͸� ���� �� �����ͺ��̽�
	 *	@return true - ���������� �����͸� ������ ��� true ���� ��ȯ�Ѵ�.<br>
	 *			false - �ν� ������ ������ ������ ��� false ���� ��ȯ�Ѵ�.<br>
	 */
	virtual bool add(const char *fileName) = 0;

	/**
	 *	�̹������� ����� �ν��Ѵ�.
	 *	@param image �ν��� ����� �ִ� �̹���
	 *	@param width �̹����� ��
	 *	@param height �̹����� ����
	 *	@param pixelByte �� �ȼ��� ������ �޸��� ũ��
	 *	@return ��� �ν��� ����� VisionRecognitionResult�������� ��ȯ�Ѵ�.<br>
	 */
	virtual std::valarray<VisionRecognitionResult>recognize(unsigned char *image, int width, int height, int pixelbyte) = 0;

	/**
	 *	�����ͺ��̽����� Ư�� ����� �����͸� �����.
	 *	@param name ���� �������� �̸�
	 *	@return true - ���������� �ν� ������ ������ ��� true ���� ��ȯ�Ѵ�.<br>
	 *			false - �ν� ���� ������ ������ ��� false ���� ��ȯ�Ѵ�.<br>
	 */
	virtual bool remove(const char *name) = 0;

	/**
	 *	�����ͺ��̽��� �ʱ�ȭ�Ѵ�.
	 *	@return true - ���������� �ν� ���� �����ͺ��̽��� �ʱ�ȭ�� ��� true ���� ��ȯ�Ѵ�.<br>
	 *			false - �ν� ���� �����ͺ��̽��� �ʱ�ȭ�� ������ ��� false ���� ��ȯ�Ѵ�.<br>
	 */
	virtual bool cleanUp(void) = 0;
};

};

#endif
