/*
 *  Generated sources by OPRoS Component Generator (OCG V2)
 *  
 */

#include "KITECH_HaarFaceRecognitionComp.h"
#include "OprosPrintMessage.h"

const char* cascade_name = "haarcascade_frontalface_alt2.xml";

//
// constructor declaration
//
KITECH_HaarFaceRecognitionComp::KITECH_HaarFaceRecognitionComp()
{
	portSetup();
}

//
// constructor declaration (with name)
//
KITECH_HaarFaceRecognitionComp::KITECH_HaarFaceRecognitionComp(const std::string &name)
{
	portSetup();
}

//
// destructor declaration
//

KITECH_HaarFaceRecognitionComp::~KITECH_HaarFaceRecognitionComp() 
{
	onDestroy();
}

void KITECH_HaarFaceRecognitionComp::portSetup() {

	// provided service port setup
	
	ProvidedServicePort *pa1;
	pa1=new VisionRecognitionServiceProvided(this);
	addPort("VisionRecognitionService",pa1);
}

// Call back Declaration
ReturnType KITECH_HaarFaceRecognitionComp::onInitialize()
{
	PrintMessage ("KITECH_HaarFaceRecognitionComp::onInitialize()\n");

	parameter.SetProperty(getPropertyMap());

	return OPROS_SUCCESS;
}

ReturnType KITECH_HaarFaceRecognitionComp::onStart()
{
	_cascade = 0;
	_storage = 0;

	if( !_cascade ) {
		_cascade = (CvHaarClassifierCascade*)cvLoad( cascade_name, 0, 0, 0 );
	}
	if( !_storage ) {
		_storage = cvCreateMemStorage(0);	
	}

	if( !_cascade ) {
		PrintMessage ("ERROR : KITECH_HaarFaceRecognitionComp::onStart() -> Can't initialize cascade!\n");
		return OPROS_CALLER_ERROR;
	}

	PrintMessage ("SUCCESS : KITECH_HaarFaceRecognitionComp::onStart()\n");
	return OPROS_SUCCESS;
}
	
ReturnType KITECH_HaarFaceRecognitionComp::onStop()
{
#if defined(WIN32)
	Sleep(100);
#endif
	if( _storage ) {
		cvReleaseMemStorage( &_storage );
		_storage = 0;
		_cascade = 0;
		return OPROS_SUCCESS;
	}

	return OPROS_SUCCESS;
}

ReturnType KITECH_HaarFaceRecognitionComp::onReset()
{
	return OPROS_SUCCESS;
}

ReturnType KITECH_HaarFaceRecognitionComp::onError()
{
	return OPROS_SUCCESS;
}

ReturnType KITECH_HaarFaceRecognitionComp::onRecover()
{
	return OPROS_SUCCESS;
}

ReturnType KITECH_HaarFaceRecognitionComp::onDestroy()
{
	return OPROS_SUCCESS;
}

ReturnType KITECH_HaarFaceRecognitionComp::onEvent(Event *evt)
{
	//	KITECH_HaarFaceRecognitionComp에서는 사용되지 않음.

	return OPROS_SUCCESS;
}

ReturnType KITECH_HaarFaceRecognitionComp::onExecute()
{
	//PrintMessage("SUCCESS:KITECH_HaarFaceRecognitionComp::onExecute()\n");

	return OPROS_SUCCESS;
}
	
ReturnType KITECH_HaarFaceRecognitionComp::onUpdated()
{
	//	KITECH_HaarFaceRecognitionComp에서는 사용되지 않음.

	return OPROS_SUCCESS;
}

ReturnType KITECH_HaarFaceRecognitionComp::onPeriodChanged()
{
	//	KITECH_HaarFaceRecognitionComp에서는 사용되지 않음.

	return OPROS_SUCCESS;
}


bool KITECH_HaarFaceRecognitionComp::SetParameter(Property parameter)
{
	//	API 핸들이 NULL이거나 컴포넌트의 상태가 ACTIVE 또는 INACTIVE 상태가 아니면
	//	에러를 리턴
	if( (getStatus() != OPROS_CS_ACTIVE && getStatus() != OPROS_CS_INACTIVE)) {
		return false;
	}

	//	API의 SetParameter 함수 호출
	return true;
}
Property KITECH_HaarFaceRecognitionComp::GetParameter()
{
	return this->parameter;
}

vector<VisionRecognitionResult> KITECH_HaarFaceRecognitionComp::Recognize(vector<unsigned char> image,int width,int height,int pixelBytes)
{
	//PrintMessage("SUCCESS:KITECH_HaarFaceRecognitionComp::Recognize()\n");

	vector<VisionRecognitionResult> _recognitionResult(0);

	IplImage *cvImage = cvCreateImageHeader( cvSize(width, height), 8, pixelBytes );
	cvImage->imageData = (char *)&image[0];

	double scale = 1.5;
	IplImage* gray = cvCreateImage( cvSize(cvImage->width,cvImage->height), 8, 1 );
	IplImage* small_img = cvCreateImage( cvSize( cvRound (cvImage->width/scale), cvRound (cvImage->height/scale)), 8, 1 );

	cvCvtColor( cvImage, gray, CV_BGR2GRAY );
	cvResize( gray, small_img, CV_INTER_LINEAR );
	cvEqualizeHist( small_img, small_img );
	if( _storage ) {
		cvClearMemStorage( _storage );
	}

	if( _cascade ) {
		CvSeq* faces = cvHaarDetectObjects( small_img, _cascade, _storage,
							1.1, 2, CV_HAAR_DO_CANNY_PRUNING,
							cvSize(30, 30) );
		if( faces->total ) {
			_recognitionResult.resize (faces->total);

			for( int i = 0; i < (faces ? faces->total : 0); i++ ) {
				CvRect* rect = (CvRect*)cvGetSeqElem( faces, i );

				//rec.type = 1;
				_recognitionResult[i].name = "Face";
				/*- Get Upper left rectangle corner coordinate -*/
				_recognitionResult[i].point1X = (int)((rect->x) * scale + 0.5);
				_recognitionResult[i].point1Y = (int)((rect->y) * scale + 0.5);
				/*- Get Upper right rectangle corner coordinate -*/
				_recognitionResult[i].point2X = (int)((rect->x + rect->width) * scale + 0.5);
				_recognitionResult[i].point2Y = (int)((rect->y) * scale + 0.5);
				/*- Get Lower right rectangle corner coordinate -*/
				_recognitionResult[i].point3X = (int)((rect->x + rect->width) * scale + 0.5);
				_recognitionResult[i].point3Y = (int)((rect->y + rect->height) * scale + 0.5);
				/*- Get Lower left rectangle corner coordinate -*/
				_recognitionResult[i].point4X = (int)((rect->x) * scale + 0.5);
				_recognitionResult[i].point4Y = (int)((rect->y + rect->height) * scale + 0.5);
			}
			//cvSaveImage("faces.jpg", cvImage);
			//PrintMessage("KITECH_HaarFaceRecognitionComp::Recognize() -> I found %d faces.\n", faces->total);
		}
	}
	cvReleaseImage( &gray );
	cvReleaseImage( &small_img );
	cvReleaseImageHeader( &cvImage );

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
	return new KITECH_HaarFaceRecognitionComp();
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
	return new KITECH_HaarFaceRecognitionComp();
}

void releaseComponent(Component *com)
{
	delete com;
}
#endif
#endif

