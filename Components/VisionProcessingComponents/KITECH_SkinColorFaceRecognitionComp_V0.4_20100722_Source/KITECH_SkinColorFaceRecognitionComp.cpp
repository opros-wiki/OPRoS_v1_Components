/*
 *  Generated sources by OPRoS Component Generator (OCG V2)
 *  
 */

#include "KITECH_SkinColorFaceRecognitionComp.h"
#include "OprosPrintMessage.h"

#include "cv.h"
#include "highgui.h"
#include "BlobLabeling.h"

//
// constructor declaration
//
KITECH_SkinColorFaceRecognitionComp::KITECH_SkinColorFaceRecognitionComp()
{
	portSetup();
}

//
// constructor declaration (with name)
//
KITECH_SkinColorFaceRecognitionComp::KITECH_SkinColorFaceRecognitionComp(const std::string &name)
{
	portSetup();
}

//
// destructor declaration
//

KITECH_SkinColorFaceRecognitionComp::~KITECH_SkinColorFaceRecognitionComp() 
{
	onDestroy();
}

void KITECH_SkinColorFaceRecognitionComp::portSetup() {

	// provided service port setup
	
	ProvidedServicePort *pa1;
	pa1=new VisionRecognitionServiceProvided(this);
	addPort("VisionRecognitionService",pa1);
}

// Call back Declaration
ReturnType KITECH_SkinColorFaceRecognitionComp::onInitialize()
{
	PrintMessage ("KITECH_SkinColorFaceRecognitionComp::onInitialize()\n");

	std::map<std::string, std::string> temp = getPropertyMap();
	parameter.SetProperty(temp);
	
	return OPROS_SUCCESS;
}

ReturnType KITECH_SkinColorFaceRecognitionComp::onStart()
{

	return OPROS_SUCCESS;
}
	
ReturnType KITECH_SkinColorFaceRecognitionComp::onStop()
{
#if defined(WIN32)
	Sleep(100);
#endif

	return OPROS_SUCCESS;
}

ReturnType KITECH_SkinColorFaceRecognitionComp::onReset()
{
	return OPROS_SUCCESS;
}

ReturnType KITECH_SkinColorFaceRecognitionComp::onError()
{
	return OPROS_SUCCESS;
}

ReturnType KITECH_SkinColorFaceRecognitionComp::onRecover()
{
	return OPROS_SUCCESS;
}

ReturnType KITECH_SkinColorFaceRecognitionComp::onDestroy()
{
	return OPROS_SUCCESS;
}

ReturnType KITECH_SkinColorFaceRecognitionComp::onEvent(Event *evt)
{
	//	KITECH_SkinColorFaceRecognitionComp에서는 사용되지 않음.

	return OPROS_SUCCESS;
}

ReturnType KITECH_SkinColorFaceRecognitionComp::onExecute()
{
	//PrintMessage("SUCCESS:KITECH_SkinColorFaceRecognitionComp::onExecute()\n");

	return OPROS_SUCCESS;
}
	
ReturnType KITECH_SkinColorFaceRecognitionComp::onUpdated()
{
	//	KITECH_SkinColorFaceRecognitionComp에서는 사용되지 않음.

	return OPROS_SUCCESS;
}

ReturnType KITECH_SkinColorFaceRecognitionComp::onPeriodChanged()
{
	//	KITECH_SkinColorFaceRecognitionComp에서는 사용되지 않음.

	return OPROS_SUCCESS;
}


bool KITECH_SkinColorFaceRecognitionComp::SetParameter(Property parameter)
{
	//	API 핸들이 NULL이거나 컴포넌트의 상태가 ACTIVE 또는 INACTIVE 상태가 아니면
	//	에러를 리턴
	if( (getStatus() != OPROS_CS_ACTIVE && getStatus() != OPROS_CS_INACTIVE)) {
		return false;
	}

	//	API의 SetParameter 함수 호출
	return true;
}
Property KITECH_SkinColorFaceRecognitionComp::GetParameter()
{
	return this->parameter;
}

vector<VisionRecognitionResult> KITECH_SkinColorFaceRecognitionComp::Recognize(vector<unsigned char> image,int width,int height,int pixelBytes)
{
	//PrintMessage("SUCCESS:KITECH_SkinColorFaceRecognitionComp::Recognize()");

	vector<VisionRecognitionResult> _recognitionResult(0);

	IplImage *cvImage = cvCreateImageHeader( cvSize(width, height), 8, pixelBytes );
	cvImage->imageData = (char *)&(image)[0];

	IplImage *ycrcbImage = cvCreateImage( cvGetSize(cvImage), 8, pixelBytes );
	cvCvtColor(cvImage, ycrcbImage, CV_BGR2YCrCb);

	IplImage *cvMask= cvCreateImage( cvSize(width, height), IPL_DEPTH_8U, 1 );

	cvInRangeS( ycrcbImage, cvScalar(0,133,77), cvScalar(255,173,127), cvMask );

	CBlobLabeling blob;
	blob.SetParam( cvMask, width*height/100 );
	blob.DoLabeling();

	_recognitionResult.resize(blob.m_nBlobs);
	for( int i = 0  ;  i < blob.m_nBlobs  ;  i++ ) {
		_recognitionResult[i].name = "Face";

		_recognitionResult[i].point1X = blob.m_recBlobs[i].x;
		_recognitionResult[i].point1Y = blob.m_recBlobs[i].y;
		_recognitionResult[i].point2X = blob.m_recBlobs[i].x + blob.m_recBlobs[i].width;
		_recognitionResult[i].point2Y = blob.m_recBlobs[i].y;
		_recognitionResult[i].point3X = blob.m_recBlobs[i].x + blob.m_recBlobs[i].width;
		_recognitionResult[i].point3Y = blob.m_recBlobs[i].y + blob.m_recBlobs[i].height;
		_recognitionResult[i].point4X = blob.m_recBlobs[i].x;
		_recognitionResult[i].point4Y = blob.m_recBlobs[i].y + blob.m_recBlobs[i].height;
		//PrintMessage("SUCCESS:KITECH_SkinColorFaceRecognitionComp::recognize() -> I found %d data.(%d=%s)\n", blob.m_nBlobs, i, _recognitionResult[i].name.c_str());
	}

	//cvSaveImage("KITECH_SkinColorFaceRecognitionComp.jpg", cvImage);

	cvReleaseImage(&cvMask);
	cvReleaseImage(&ycrcbImage);
	cvReleaseImageHeader(&cvImage);

	return _recognitionResult;
}

#ifdef MAKE_COMPONENT_DLL
#ifdef WIN32

extern "C"
{
__declspec(dllexport) Component *getComponent();
__declspec(dllexport) void releaseComponent(Component *pcom);
}

Component *getComponent()
{
	return new KITECH_SkinColorFaceRecognitionComp();
}

void releaseComponent(Component *com)
{
	delete com;
}


#else
extern "C"
{
	Component *getComponent();
	void releaseComponent(IComponent *com);
}
Component *getComponent()
{
	return new KITECH_SkinColorFaceRecognitionComp();
}

void releaseComponent(Component *com)
{
	delete com;
}
#endif
#endif

