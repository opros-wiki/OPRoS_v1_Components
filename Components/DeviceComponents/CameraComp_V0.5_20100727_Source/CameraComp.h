#ifndef _CameraComponent_COMPONENT_H
#define _CameraComponent_COMPONENT_H
/*
 *  Generated sources by OPRoS Component Generator (OCG V2)
 *   
 */
#include <Component.h>
#include <InputDataPort.h>
#include <OutputDataPort.h>
#include <InputEventPort.h>
#include <OutputEventPort.h>
#include <Event.h>
#include <OPRoSTypes.h>
#if defined(WIN32)
#include <Windows.h>
#else
#include <dlfcn.h>
#endif

#include <Property.h>
#include "CameraCompServiceProvided.h"
#include "Camera.h"
#include "RawImage.h"
	

// ����
/**
 *	<table><tr><td>
 *	CameraComp�� �κ����� vision�� ������ �ϴ� ī�޶� ���� ������Ʈ�̴�.
 *	�̸� �̿��Ͽ� ��ü�ν�, ��ġ�ν� ����  �ð����� ������ �����ϴ�. CameraComp��
 *	CameraComp.xml, CameraCompServiceProvided.h�� ���ԵǾ���ϸ�,
 *	CameraComp.xml���� CameraComp�� ���������� ����Ǿ� �ִ�.
 *	CameraCompServiceProvided.h�� �� ������Ʈ���� �����ϴ� ���� ��Ʈ�� ȣ���� �� �ִ�
 *	�������̽��� �����Ѵ�.
 *	</td></tr><tr><td>
 *	<center><img src="../../images/uml/UML_Camera.jpg"></center>
 *	</td></tr></table>
 * �� ������Ʈ�� �����ϱ� ���ؼ��� OpenCV ���̺귯���� Lib ���丮�� �ִ�
 * cv200.dll cvaux200.dll cxcore200.dll highgui200.dll ������ ���������� �ִ� ������ �ξ�� �Ѵ�.
*/
class CameraComp : public Component, public ICameraService
{
protected:
	// �Ӽ�
	//	Variables for CameraComp
	/**
	 *	Camera API DLL�� �ڵ��� ����� �����̴�. 
	*/
#if defined(WIN32)
	HMODULE hOprosAPI;
#else
	void *hOprosAPI;
#endif
	
	/**
	 *	Camera�� API �ڵ�ν�, Camera API DLL���� ������
	 *	CameraŬ������ �����͸� �����ϴ� �����̴�.
	*/
	Camera *camera;

	/**
	 *	CameraComp�� �������������� �����ϴ� �����̴�.<br>
	 *	<!-- [ǥ] Parameter -->
	 *	<table border=1>
	 *	<tr><td bgcolor="#EEEEEE"><center><b>�̸�</b></center></td> <td bgcolor="#EEEEEE"><center><b>Ÿ��</b></center></td> <td bgcolor="#EEEEEE" colspan=2><center><b>����</b></center></td></tr>
	 *	<tr><td><b>ApiName</b></td> <td>std::string</td> <td>������Ʈ���� ����� dll������ �̸��̴�.</td></tr>
	 *	<tr><td><b>CameraID</b></td> <td>int</td> <td>������ �Է¹��� ī�޶��� ���̵��̴�.</td></tr>
	 *	<tr><td><b>Width</b></td> <td>int</td> <td>���� �Էµ������� �ʺ�(����:pixel)�̴�.</td></tr>
	 *	<tr><td><b>Height</b></td> <td>int</td> <td>���� �Էµ������� ����(����:pixel)�̴�.</td></tr>
	 *	<tr><td><b>PixelBytes</b></td> <td>int</td> <td>�� �ȼ��� �ʿ��� byte ���̴�. �� ������ ���� �޶�����. RGB�� 3byte�� �ʿ��ϴ�.</td></tr>
	 *	<tr><td><b>Flip</b></td> <td>int</td> <td>������ ���� �Ǵ� �������� �����´�. 0�� ���� �ƹ� ��ȯ�� ���� �ʴ´�. 1�� ���� x���� �������� ����(���Ϲ���),
	 *	2�� ���� y���� �������� ����(�¿����), 3�� ���� x,y���� �������� ����(�����¿����)�̴�. 3�� ���, ������ ������Ű�� �ʰ� 180�� ȸ����Ų ���¿� ����.</td></tr>
	 *	</table>
	*/
	Property parameter;

	/**
	 *	�̹��� �����͸� �ӽ÷� ������ �����̴�. ī�޶�κ��� ���� �����Ͱ� ����Ǹ�,
	 *	��µ����� ��Ʈ�� ���ؼ� �ٸ� ������Ʈ�� �����Ѵ�.
	 */
	std::vector<unsigned char> imageBuffer;
	
	// ��������Ʈ
	/**
	 *	�̹��� �����͸� ������ ��� ��������Ʈ�̴�.
	 *	�� ��Ʈ�� ���� ī�޶�κ��� ���� �����Ͱ� �ٸ� ������Ʈ�� ���޵ȴ�.
	 */
	OutputDataPort< vector<unsigned char> > imageData;

public:
	CameraComp();
	CameraComp(const std::string &compId);
	virtual ~CameraComp();
	virtual void portSetup();

protected:
	// Callback API
	/**
	 *	������Ʈ�� �ʱ�ȭ�� �� ȣ��Ǵ� �ݹ��Լ��̴�.
	 *	XML�� ����� ������Ƽ������ �о DLL�� �ε��ϰ�,
	 *	�ʿ��� API�� �ε��� �� �ʱ�ȭ �Ѵ�.
	 *	@return OPROS_SUCCESS - ������Ʈ �ʱ�ȭ ����<br>
	 *			OPROS_FIND_PROPERTY_ERROR - ������Ƽ������ DLL�����̸��� ����<br>
	 *			OPROS_FIND_DLL_ERROR - DLL�� ã�� �� ����<br>
	 *			OPROS_LOAD_DLL_ERROR - DLL�� �ε��� �� ����<br>
	 *			OPROS_INITIALIZE_API_ERROR - API�ʱ�ȭ ���� �����߻�<br>
	 */
	virtual ReturnType onInitialize();

	/**
	 *	������Ʈ�� Ȱ��ȭ�� �� ȣ��Ǵ� �ݹ��Լ��̴�.
	 *	@return OPROS_SUCCESS - ������Ʈ Ȱ��ȭ ����<br>
	 *			OPROS_PRECONDITION_NOT_MET - API�ڵ��� NULL�̰ų� ������Ʈ�� ���°� READY�Ǵ� INACTIVE ���°� �ƴ�<br>
	 *			OPROS_ENABLE_API_ERROR - APIȰ��ȭ ���� �����߻�<br>
	 */
	virtual ReturnType onStart();

	/**
	 *	������Ʈ�� ��Ȱ��ȭ�� �� ȣ��Ǵ� �ݹ��Լ��̴�.
	 *	@return OPROS_SUCCESS - ������Ʈ ��Ȱ��ȭ ����<br>
	 *			OPROS_PRECONDITION_NOT_MET - API�ڵ��� NULL�̰ų� ������Ʈ�� ���°� ACTIVE ���°� �ƴ�<br>
	 *			OPROS_DISABLE_API_ERROR - API��Ȱ��ȭ ���� �����߻�<br>
	 */
	virtual ReturnType onStop();

	/**
	 *	������Ʈ�� ���� �� �� ȣ��Ǵ� �ݹ��Լ��̴�.
	 *	�����۾��� ������ �� APIȣ�� ������ Finalize, Initialize, Enable���̴�.
	 *	����ϴ� ��� API�� ���� ���� �۾��� �����Ѵ�.
	 *	ȣ�⿡ ������ ��� ������ ���� �Ѵ�. Enableȣ�⿡ �����ϸ� �ٽ� Finalize�� ȣ���Ѵ�.
	 *	@return OPROS_SUCCESS - ������Ʈ ���� ����<br>
	 *			OPROS_PRECONDITION_NOT_MET - API�ڵ��� NULL�� ����<br>
	 *			OPROS_RESET_API_ERROR - API���� ���� �����߻�<br>
	 */
	virtual ReturnType onReset();

	/**
	 *	������Ʈ�� ������ �߻����� �� ȣ��Ǵ� �ݹ��Լ��̴�.
	 *	������ �߻��ϸ� API�� Disable�� ȣ���Ͽ� ��Ȱ��ȭ ��Ų��.
	 *	����ϴ� ��� API�� ���� ���� �۾��� �����Ѵ�.
	 *	@return OPROS_SUCCESS - �����߻� �� ��Ȱ��ȭ ����<br>
	 *			OPROS_PRECONDITION_NOT_MET - API�ڵ��� NULL�� ����<br>
	 *			OPROS_DISABLE_API_ERROR - API��Ȱ��ȭ ���� �����߻�<br>
	 */
	virtual ReturnType onError();

	/**
	 *	������Ʈ�� ������ ������ �� ȣ��Ǵ� �ݹ��Լ��̴�.
	 *	���� ���� �� APIȣ�� ������ Finalize, Initialize���̴�.
	 *	����ϴ� ��� API�� ���� ���� �۾��� �����Ѵ�.
	 *	@return OPROS_SUCCESS - �������� ����<br>
	 *			OPROS_PRECONDITION_NOT_MET - API�ڵ��� NULL�� ����<br>
	 *			OPROS_RECOVER_API_ERROR - API���� ���� �����߻�<br>
	 */
	virtual ReturnType onRecover();

	/**
	 *	������Ʈ�� ����� �� ȣ��Ǵ� �ݹ��Լ��̴�.
	 *	Finalize�� ȣ���Ͽ� API�� �����ϰ�, API�ڵ�� DLL�ڵ��� �����Ѵ�.
	 *	����ϴ� ��� API�� ���� ���� �۾��� �����Ѵ�.
	 *	@return OPROS_SUCCESS - ������Ʈ ���� ����<br>
	 *			OPROS_PRECONDITION_NOT_MET - API�ڵ��� NULL�� ����<br>
	 *			OPROS_FINALIZE_API_ERROR - API���� ���� �����߻�<br>
	 */
	virtual ReturnType onDestroy();

public:
	/**
	 *	������Ʈ�� �̺�Ʈ�� �޾��� �� ȣ��Ǵ� �ݹ��Լ��̴�.
	 *	CameraComp������ ������ ����.
	 *	@return OPROS_SUCCESS &nbsp;
	 */
	virtual ReturnType onEvent(Event *evt);

	/**
	 *	������Ʈ�� �ֱ������� ������ �� ȣ��Ǵ� �ݹ��Լ��̴�.
	 *	API�� GetImage�� ȣ���Ͽ� ī�޶�� ���� �̹����� �����ͼ�
	 *	��������Ʈ�� push�Ѵ�.
	 *	@return OPROS_SUCCESS - ���ۼ���<br>
	 *			OPROS_PRECONDITION_NOT_MET - API�ڵ��� NULL�� ����<br>
	 *			OPROS_CALL_API_ERROR - APIȣ�� ���� ���� �߻�<br>
	 */
	virtual ReturnType onExecute();

	/**
	 *	������Ʈ�� �ֱ������� ������ �� ȣ��Ǵ� �ݹ��Լ��̴�.
	 *	CameraComp������ ������ ����.
	 *	@return OPROS_SUCCESS &nbsp;
	 */
	virtual ReturnType onUpdated();

	/**
	 *	������Ʈ�� ���� �ֱⰡ ����Ǿ��� �� ȣ��Ǵ� �ݹ��Լ��̴�.
	 *	CameraComp������ ������ ����.
	 *	@return OPROS_SUCCESS &nbsp;
	 */
	virtual ReturnType onPeriodChanged();


	// ������Ʈ
	/**
	 *	CameraComp�� ���������� �����Ѵ�.
	 *	�ٸ� ������Ʈ���� �� ������Ʈ�� ���������� ������ �� ���ȴ�.
	 *	API�� SetParameter�� ȣ���Ͽ� �� ����� �����Ѵ�.
	 *	@param parameter ������ �Ķ���� ����
	 *	@return true - �Ķ���� �����ͼ��� ����<br>
	 *			false - �Ķ���� �����ͼ����� �����߰ų�, API�ڵ��� NULL�� ���, �Ǵ�<br>
	 * &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ������Ʈ�� ���°� ACTIVE, INACTIVE�� �ƴ� �ٸ� ������ ���<br>
	 */
	virtual bool SetParameter(Property parameter);

	/**
	 *	CameraComp�� ���������� �ٸ� ������Ʈ���� ������ �� ���ȴ�.
	 *	CameraComp������ ������ ����.
	 *	@return parameter �Ķ��������
	 */
	virtual Property GetParameter();

	virtual int GetError();

	/**
	 *	ī�޶�κ��� �̹��� �����͸� �����´�.
	 *	������ ũ�⸦ �Ķ���������� �̿��Ͽ� �ʿ��� ũ��� �����ϰ�,
	 *	API�� GetImage�� ȣ���Ͽ� ī�޶󿡼� �̹��� �����͸� �����ͼ�
	 *	���ۿ� �����Ѵ�. ���ۿ��� �ʿ��� size�� 0������ ���,
	 *	false�� ���� �԰� ���ÿ� ���� �޽����� ����Ѵ�.
	 *	CameraComp������ ������ ����.
	 *	@return �̹��� ������
	 */
	virtual vector<unsigned char> GetImage();

private:
	int error;
};

#endif

