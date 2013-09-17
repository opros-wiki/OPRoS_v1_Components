/*
 *  Generated sources by OPRoS Component Generator (OCG V2)
 *  
 */

#include "IPEL_Haar2FaceEyeDetectionComp.h"
#include "OprosPrintMessage.h"

const char* cascade_face_name = "haarcascade_frontalface_alt.xml";
const char* cascade_eye_name = "haarcascade_eye.xml";

//
// constructor declaration
//
IPEL_Haar2FaceEyeDetectionComp::IPEL_Haar2FaceEyeDetectionComp()
{
	portSetup();
}

//
// constructor declaration (with name)
//
IPEL_Haar2FaceEyeDetectionComp::IPEL_Haar2FaceEyeDetectionComp(const std::string &name)
{
	portSetup();
}

//
// destructor declaration
//

IPEL_Haar2FaceEyeDetectionComp::~IPEL_Haar2FaceEyeDetectionComp() 
{
	onDestroy();
}

void IPEL_Haar2FaceEyeDetectionComp::portSetup() {

	// provided service port setup
	
	ProvidedServicePort *pa1;
	pa1=new VisionRecognitionServiceProvided(this);
	addPort("VisionRecognitionService",pa1);
}

// Call back Declaration
ReturnType IPEL_Haar2FaceEyeDetectionComp::onInitialize()
{
	PrintMessage ("IPEL_Haar2FaceEyeDetectionComp::onInitialize()\n");

	std::map<std::string, std::string> temp = getPropertyMap();
	parameter.SetProperty(temp);

	return OPROS_SUCCESS;
}

ReturnType IPEL_Haar2FaceEyeDetectionComp::onStart()
{
	_cascade_f = 0;
	_cascade_e = 0;
	_storage = 0;

	if( !_cascade_f ) {
		_cascade_f = (CvHaarClassifierCascade*)cvLoad( cascade_face_name, 0, 0, 0 );
		if(!_cascade_f) printf("Can not load %s\n",cascade_face_name);
	}
	if( !_cascade_e ) {
		_cascade_e = (CvHaarClassifierCascade*)cvLoad( cascade_eye_name, 0, 0, 0 );
		if(!_cascade_e) printf("Can not load %s\n",cascade_eye_name);
	}
	if( !_storage ) {
		_storage = cvCreateMemStorage(0);	
	}

	if( !_cascade_f || !_cascade_e || !_storage )
		return OPROS_CALLER_ERROR;


	PrintMessage ("SUCCESS : IPEL_Haar2FaceEyeDetectionComp::onStart()\n");
	return OPROS_SUCCESS;
}
	
ReturnType IPEL_Haar2FaceEyeDetectionComp::onStop()
{
#if defined(WIN32)
	Sleep(100);
#endif
	if( _storage ) {
		cvReleaseMemStorage( &_storage );
		_storage = 0;
		_cascade_f = 0;
		_cascade_e = 0;
		return OPROS_SUCCESS;
	}

	return OPROS_SUCCESS;
}

ReturnType IPEL_Haar2FaceEyeDetectionComp::onReset()
{
	return OPROS_SUCCESS;
}

ReturnType IPEL_Haar2FaceEyeDetectionComp::onError()
{
	return OPROS_SUCCESS;
}

ReturnType IPEL_Haar2FaceEyeDetectionComp::onRecover()
{
	return OPROS_SUCCESS;
}

ReturnType IPEL_Haar2FaceEyeDetectionComp::onDestroy()
{
	return OPROS_SUCCESS;
}

ReturnType IPEL_Haar2FaceEyeDetectionComp::onEvent(Event *evt)
{
	//	IPEL_Haar2FaceEyeDetectionComp에서는 사용되지 않음.

	return OPROS_SUCCESS;
}

ReturnType IPEL_Haar2FaceEyeDetectionComp::onExecute()
{
	//PrintMessage("SUCCESS:IPEL_Haar2FaceEyeDetectionComp::onExecute()\n");

	return OPROS_SUCCESS;
}
	
ReturnType IPEL_Haar2FaceEyeDetectionComp::onUpdated()
{
	//	IPEL_Haar2FaceEyeDetectionComp에서는 사용되지 않음.

	return OPROS_SUCCESS;
}

ReturnType IPEL_Haar2FaceEyeDetectionComp::onPeriodChanged()
{
	//	IPEL_Haar2FaceEyeDetectionComp에서는 사용되지 않음.

	return OPROS_SUCCESS;
}


bool IPEL_Haar2FaceEyeDetectionComp::SetParameter(Property parameter)
{
	//	API 핸들이 NULL이거나 컴포넌트의 상태가 ACTIVE 또는 INACTIVE 상태가 아니면
	//	에러를 리턴
	if( (getStatus() != OPROS_CS_ACTIVE && getStatus() != OPROS_CS_INACTIVE)) {
		return false;
	}

	//	API의 SetParameter 함수 호출
	return true;
}
Property IPEL_Haar2FaceEyeDetectionComp::GetParameter()
{
	return this->parameter;
}

vector<VisionRecognitionResult> IPEL_Haar2FaceEyeDetectionComp::Recognize(vector<unsigned char> image,int width,int height,int pixelBytes)
{
	//PrintMessage("SUCCESS:IPEL_Haar2FaceEyeDetectionComp::Recognize()\n");

	vector<VisionRecognitionResult> _recognitionResult(0);

	IplImage *cvImage = cvCreateImageHeader( cvSize(width, height), 8, pixelBytes );
	cvImage->imageData = (char *)&image[0];

	if( _storage ) cvClearMemStorage( _storage );

	if( _cascade_f ) {
		/* detect faces */
		CvSeq *faces = cvHaarDetectObjects(cvImage, _cascade_f, _storage,
			1.1, 3, CV_HAAR_DO_CANNY_PRUNING, cvSize( 30, 30 ) );

		if( faces && faces->total>0) {
			/* Get region of face */
			int nfaces = faces->total; // faces->total값이 변한다. 
			_recognitionResult.resize (nfaces);
			CvRect *fr = new CvRect[nfaces];

			for( int i = 0; i < (faces ? nfaces : 0); i++ ) {
				/* draw a rectangle */
				CvRect *r = (CvRect*)cvGetSeqElem(faces, i);
				memcpy(&fr[i],r,sizeof(CvRect));					

				//rec.type = 1;
				_recognitionResult[i].name = "Face";
				/*- Get Upper left rectangle corner coordinate -*/
				_recognitionResult[i].point1X = (int)((r->x) + 0.5);
				_recognitionResult[i].point1Y = (int)((r->y) + 0.5);
				/*- Get Upper right rectangle corner coordinate -*/
				_recognitionResult[i].point2X = (int)((r->x + r->width) + 0.5);
				_recognitionResult[i].point2Y = (int)((r->y) + 0.5);
				/*- Get Lower right rectangle corner coordinate -*/
				_recognitionResult[i].point3X = (int)((r->x + r->width) + 0.5);
				_recognitionResult[i].point3Y = (int)((r->y + r->height) + 0.5);
				/*- Get Lower left rectangle corner coordinate -*/
				_recognitionResult[i].point4X = (int)((r->x) + 0.5);
				_recognitionResult[i].point4Y = (int)((r->y + r->height) + 0.5);
			}

			// Haar함수를 두번 수행할때 결과가 다를수 있다.
			for( int i = 0; i < (faces ? nfaces : 0); i++ ) {
				/* reset buffer for the next object detection */
				cvClearMemStorage(_storage);

				/* Set the Region of Interest: estimate the eyes' position */
				cvSetImageROI(cvImage, cvRect(fr[i].x, fr[i].y + (int)(fr[i].height/5.5), fr[i].width, (int)(fr[i].height/3.0) ) );

				/* detect eyes */
				CvSeq* eyes = cvHaarDetectObjects(cvImage, _cascade_e, _storage,
					1.15, 3, CV_HAAR_DO_CANNY_PRUNING, cvSize(25, 15));

				/* draw a rectangle for each eye found */
				for(int j = 0; j < (eyes ? eyes->total : 0); j++ ) {
					if(j>1) break;
					CvRect *er = (CvRect*) cvGetSeqElem( eyes, j );
					cvRectangle(cvImage,
						cvPoint(er->x, er->y), 
						cvPoint(er->x + er->width, er->y + er->height),
						CV_RGB(255, 0, 0), 1, 8, 0);

				}

				cvResetImageROI(cvImage);
			}

			delete fr;
		}
	}

#if 0
	if( _recognitionResult.size() ) {
		for( std::vector<VisionRecognitionResult>::iterator it = _recognitionResult.begin()  ;  it != _recognitionResult.end()  ;  it++ ) {
			cvLine(cvImage,
				cvPoint(it->point1X,it->point1Y),
				cvPoint(it->point2X,it->point2Y),
				CV_RGB(0, 255, 0));
			cvLine(cvImage,
				cvPoint(it->point2X,it->point2Y),
				cvPoint(it->point3X,it->point3Y),
				CV_RGB(0, 255, 0));
			cvLine(cvImage,
				cvPoint(it->point3X,it->point3Y),
				cvPoint(it->point4X,it->point4Y),
				CV_RGB(0, 255, 0));
			cvLine(cvImage,
				cvPoint(it->point4X,it->point4Y),
				cvPoint(it->point1X,it->point1Y),
				CV_RGB(0, 255, 0));
		}
	}
#endif

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
	return new IPEL_Haar2FaceEyeDetectionComp();
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
	return new IPEL_Haar2FaceEyeDetectionComp();
}

void releaseComponent(Component *com)
{
	delete com;
}
#endif
#endif

