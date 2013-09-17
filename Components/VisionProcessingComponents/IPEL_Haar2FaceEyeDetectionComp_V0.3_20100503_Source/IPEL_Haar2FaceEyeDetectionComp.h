#ifndef _IPEL_Haar2FaceEyeDetectionComponent_COMPONENT_H
#define _IPEL_Haar2FaceEyeDetectionComponent_COMPONENT_H
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
#include <ApiTypes.h>

#if defined(WIN32)
#include <windows.h>
#endif

#include "VisionRecognitionComp.h"
#include "VisionRecognitionServiceProvided.h"

#include "cv.h"
#include "highgui.h"

//����
/**
 *	<table><tr><td>
 * �� IPEL_Haar2FaceEyeDetector�� Haar �˰��������� �̿��� �󱼰��� ������Ʈ�̴�.
 * Human eye�� �����ϱ� ���� ���� ���� �����Ѵ�. �̶� ���� �˰������� OpenCV�� 
 * boosted cascade�� ���Ǵ� haar-like features�� �̿��� ����̴�. �׸��� XML eye
 * classifier�� ���ƴ�. ���������� ���� ������ �Ŀ�, eye�� ��ġ�� �����ϰ� eye 
 * ������ �����Ѵ�. �߸��� ������� ���̱� ���� eye ��ġ�� ������ �ʿ䰡 �ִ�.
 *	</td></tr><tr><td>
 *	<center><img src="../../images/uml/UML_ColorRecognition.jpg"></center>
 *	</td></tr></table>
 * �� ������Ʈ�� �����ϱ� ���ؼ��� OpenCV ���̺귯���� Lib ���丮�� �ִ�
 * cv200.dll cvaux200.dll cxcore200.dll highgui200.dll ���ϵ��
 * �� ������Ʈ ���丮�� �ִ� haarcascade_frontalface_alt.xml haarcascade_eye.xml ������ ���������� �ִ� ������ �ξ�� �Ѵ�.
*/
class IPEL_Haar2FaceEyeDetectionComp : public Component, public IVisionRecognitionService
{
protected:
	// �Ӽ�
	//	Variables for IPEL_Haar2FaceEyeDetectionComp
	/**
	 *	IPEL_Haar2FaceEyeDetectionComp�� �������������� �����ϴ� �����̴�.<br>
	*/
	Property parameter;

	/**
	* _cascade_f�� ���� �����ϱ� ���� ���Ǵ� 
	* Haar-like feature�� �̿��� classifier cascade �����̴�.
	* �� ����ü�� OpenCV���� �����Ѵ�.
	*/
	CvHaarClassifierCascade *_cascade_f;

	/**
	* _cascade_e�� ���� �����ϱ� ���� ���Ǵ� 
	* Haar-like feature�� �̿��� classifier cascade �����̴�.
	* �� ����ü�� OpenCV���� �����Ѵ�.
	*/
	CvHaarClassifierCascade *_cascade_e;

	/**
	* �� �����ϱ� ���� Haar-like feature�� �̿��� ���� ������ �ٷ�� 
	* ����ҷ� ���������� ���ȴ�.
	* �� ����ü�� OpenCV���� �����Ѵ�.
	*/
	CvMemStorage			*_storage;

public:
	/**
	 *	IPEL_Haar2FaceEyeDetectionComp Ŭ������ �⺻ �������̴�.<br>
	 *	��Ʈ�� �ʱ�ȭ��Ű�� �Լ��� ȣ���Ѵ�.
	*/
	IPEL_Haar2FaceEyeDetectionComp();

	/**
	 *	IPEL_Haar2FaceEyeDetectionComp Ŭ������ �������ڸ� ������ �������̴�.<br>
	 *	��Ʈ�� �ʱ�ȭ��Ű�� �Լ��� ȣ���Ѵ�.
	 *	@param compId ������Ʈ�� ID.
	*/
	IPEL_Haar2FaceEyeDetectionComp(const std::string &compId);

	/**
	 *	IPEL_Haar2FaceEyeDetectionComp Ŭ������ �⺻ �Ҹ����̴�.
	*/
	virtual ~IPEL_Haar2FaceEyeDetectionComp();

	/**
	 *	IPEL_Haar2FaceEyeDetectionComp���� �����ϴ� ���� ��Ʈ�� �ʱ�ȭ�ϰ� ����Ѵ�.
	*/
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
	 *	IPEL_Haar2FaceEyeDetectionComp������ ������ ����.
	 *	@return OPROS_SUCCESS &nbsp;
	 */
	virtual ReturnType onEvent(Event *evt);

	/**
	 *	������Ʈ�� �ֱ������� ������ �� ȣ��Ǵ� �ݹ��Լ��̴�.
	 *	�Է� ��������Ʈ���� ī�޶��� ������ �ԷµǸ�
	 *	������ ���ۿ� �����ϰ�, recognize�� ȣ���Ͽ� �����ν��� �����Ѵ�.
	 *	@return OPROS_SUCCESS - ����<br>
	 *			OPROS_PRECONDITION_NOT_MET - API�ڵ��� NULL�� ����<br>
	 */
	virtual ReturnType onExecute();

	/**
	 *	������Ʈ�� �ֱ������� ������ �� ȣ��Ǵ� �ݹ��Լ��̴�.
	 *	IPEL_Haar2FaceEyeDetectionComp������ ������ ����.
	 *	@return OPROS_SUCCESS &nbsp;
	 */
	virtual ReturnType onUpdated();

	/**
	 *	������Ʈ�� ���� �ֱⰡ ����Ǿ��� �� ȣ��Ǵ� �ݹ��Լ��̴�.
	 *	IPEL_Haar2FaceEyeDetectionComp������ ������ ����.
	 *	@return OPROS_SUCCESS &nbsp;
	 */
	virtual ReturnType onPeriodChanged();


	// ������Ʈ
	/**
	 *	IPEL_Haar2FaceEyeDetectionComp�� ���������� �����Ѵ�.
	 *	�ٸ� ������Ʈ���� �� ������Ʈ�� ���������� ������ �� ���ȴ�.
	 *	API�� SetParameter�� ȣ���Ͽ� �� ����� �����Ѵ�.
	 *	@param parameter ������ �Ķ���� ����
	 *	@return true - �Ķ���� �����ͼ��� ����<br>
	 *			false - �Ķ���� �����ͼ����� �����߰ų�, API�ڵ��� NULL�� ���, �Ǵ�<br>
	 * &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ������Ʈ�� ���°� ACTIVE, INACTIVE�� �ƴ� �ٸ� ������ ���<br>
	 */
	virtual bool SetParameter(Property parameter);

	/**
	 *	IPEL_Haar2FaceEyeDetectionComp�� ���������� �ٸ� ������Ʈ���� ������ �� ���ȴ�.
	 *	@return property - �Ķ���� ������<br>
	 */
	virtual Property GetParameter();

	/**
	*	���ν��� �����ϴ� �Լ��̴�.
	*	recognize �Լ��� �����ϸ� ī�޶� ������Ʈ�� ����� service port�� ������ �о�ͼ�
	*	���� �ν��Ͽ� ���� ���� Ư�� ������ ��Ÿ���� 4���� ��ǥ ���·� �Ѱ��ش�.
	*	@param image ���� �̹���<br>
	*          width �̹����� ���� �ػ�<br>
	*          height �̹����� ���� �ػ�<br>
	*          pixelBytes �̹����� �ȼ��� ����Ʈ ��<br>
	*	@return ������� �νĵ� ���� ���� ��ǥ<br>

	*/
	virtual vector<VisionRecognitionResult> Recognize(vector<unsigned char> image,int width,int height,int pixelBytes);

	int GetError() {return 0;};
};

#endif
