/*
 *  Generated sources by OPRoS Component Generator (OCG V2)
 *  
 */

#include "IPEL_Haar3FaceEyeDetectionComp.h"
#include "OprosPrintMessage.h"

static const CvScalar Colors[] =
{   
	{{0,0,255}}, {{0,128,255}}, {{0,255,255}},   
	{{0,255,0}}, {{255,128,0}}, {{255,255,0}},   
	{{255,0,0}}, {{255,0,255}}   
};   

//
// constructor declaration
//
IPEL_Haar3FaceEyeDetectionComp::IPEL_Haar3FaceEyeDetectionComp()
{
	portSetup();
}

//
// constructor declaration (with name)
//
IPEL_Haar3FaceEyeDetectionComp::IPEL_Haar3FaceEyeDetectionComp(const std::string &name)
{
	portSetup();
}

//
// destructor declaration
//

IPEL_Haar3FaceEyeDetectionComp::~IPEL_Haar3FaceEyeDetectionComp() 
{
	onDestroy();
}

void IPEL_Haar3FaceEyeDetectionComp::portSetup() {

	// provided service port setup
	
	ProvidedServicePort *pa1;
	pa1=new VisionRecognitionServiceProvided(this);
	addPort("VisionRecognitionService",pa1);
}

// Call back Declaration
ReturnType IPEL_Haar3FaceEyeDetectionComp::onInitialize()
{
	PrintMessage ("IPEL_Haar3FaceEyeDetectionComp::onInitialize()\n");

	std::map<std::string, std::string> temp = getPropertyMap();
	parameter.SetProperty(temp);

	return OPROS_SUCCESS;
}

ReturnType IPEL_Haar3FaceEyeDetectionComp::onStart()
{
	_faceLocator = 0;

	if( !_faceLocator ) {
		_faceLocator = new FaceLocator();
	}

	if( !_faceLocator )
		return OPROS_CALLER_ERROR;

	PrintMessage ("SUCCESS : IPEL_Haar3FaceEyeDetectionComp::onStart()\n");
	return OPROS_SUCCESS;
}
	
ReturnType IPEL_Haar3FaceEyeDetectionComp::onStop()
{
#if defined(WIN32)
	Sleep(100);
#endif
	if( _faceLocator ) {
		delete _faceLocator;
		_faceLocator = 0;
		return OPROS_SUCCESS;
	}

	return OPROS_SUCCESS;
}

ReturnType IPEL_Haar3FaceEyeDetectionComp::onReset()
{
	return OPROS_SUCCESS;
}

ReturnType IPEL_Haar3FaceEyeDetectionComp::onError()
{
	return OPROS_SUCCESS;
}

ReturnType IPEL_Haar3FaceEyeDetectionComp::onRecover()
{
	return OPROS_SUCCESS;
}

ReturnType IPEL_Haar3FaceEyeDetectionComp::onDestroy()
{
	return OPROS_SUCCESS;
}

ReturnType IPEL_Haar3FaceEyeDetectionComp::onEvent(Event *evt)
{
	//	IPEL_Haar3FaceEyeDetectionComp에서는 사용되지 않음.

	return OPROS_SUCCESS;
}

ReturnType IPEL_Haar3FaceEyeDetectionComp::onExecute()
{
	//PrintMessage("SUCCESS:IPEL_Haar3FaceEyeDetectionComp::onExecute()\n");

	return OPROS_SUCCESS;
}
	
ReturnType IPEL_Haar3FaceEyeDetectionComp::onUpdated()
{
	//	IPEL_Haar3FaceEyeDetectionComp에서는 사용되지 않음.

	return OPROS_SUCCESS;
}

ReturnType IPEL_Haar3FaceEyeDetectionComp::onPeriodChanged()
{
	//	IPEL_Haar3FaceEyeDetectionComp에서는 사용되지 않음.

	return OPROS_SUCCESS;
}


bool IPEL_Haar3FaceEyeDetectionComp::SetParameter(Property parameter)
{
	//	API 핸들이 NULL이거나 컴포넌트의 상태가 ACTIVE 또는 INACTIVE 상태가 아니면
	//	에러를 리턴
	if( (getStatus() != OPROS_CS_ACTIVE && getStatus() != OPROS_CS_INACTIVE)) {
		return false;
	}

	//	API의 SetParameter 함수 호출
	return true;
}
Property IPEL_Haar3FaceEyeDetectionComp::GetParameter()
{
	return this->parameter;
}

vector<VisionRecognitionResult> IPEL_Haar3FaceEyeDetectionComp::Recognize(vector<unsigned char> image,int width,int height,int pixelBytes)
{
	//PrintMessage("SUCCESS:IPEL_Haar3FaceEyeDetectionComp::Recognize()\n");

	vector<VisionRecognitionResult> _recognitionResult(0);

	IplImage *cvImage = cvCreateImageHeader( cvSize(width, height), 8, pixelBytes );
	cvImage->imageData = (char *)&image[0];

	const double scale = 1;
	IplImage* gray = cvCreateImage( cvSize(cvImage->width,cvImage->height), 8, 1 );
	IplImage* small_img = cvCreateImage( 
		cvSize( cvRound (cvImage->width/scale), cvRound (cvImage->height/scale)), 8, 1 );

	cvCvtColor( cvImage, gray, CV_BGR2GRAY );
	cvResize( gray, small_img, CV_INTER_LINEAR );
	//cvEqualizeHist( small_img, small_img );

	int nfaces = _faceLocator->DetectFaces(small_img);

	for(int i = 0; i < nfaces; i++)
	{                        
		// face
		int lx, ly, rx, ry, res;
		_faceLocator->GetFaceCordinates(i, lx, ly, rx, ry);

		_recognitionResult.resize (nfaces);

		//rec.type = 1;
		_recognitionResult[i].name = "Face";
		/*- Get Upper left rectangle corner coordinate -*/
		_recognitionResult[i].point1X = (int)((lx) * scale + 0.5);
		_recognitionResult[i].point1Y = (int)((ly) * scale + 0.5);
		/*- Get Upper right rectangle corner coordinate -*/
		_recognitionResult[i].point2X = (int)((lx + rx) * scale + 0.5);
		_recognitionResult[i].point2Y = (int)((ly) * scale + 0.5);
		/*- Get Lower right rectangle corner coordinate -*/
		_recognitionResult[i].point3X = (int)((lx + rx) * scale + 0.5);
		_recognitionResult[i].point3Y = (int)((ly + ry) * scale + 0.5);
		/*- Get Lower left rectangle corner coordinate -*/
		_recognitionResult[i].point4X = (int)((lx) * scale + 0.5);
		_recognitionResult[i].point4Y = (int)((ly + ry) * scale + 0.5);

		// eyes
		res = _faceLocator->GetEyeCordinates(small_img,i, lx, ly, rx, ry);

		if(res > 1)
		{  
			CvPoint leye = cvPoint(lx,ly);
			CvPoint reye = cvPoint(rx,ry);
			int radius = 10;
			cvCircle( cvImage, leye, radius, Colors[(i+1)%8], 1, 8, 0 );
			cvCircle( cvImage, reye, radius, Colors[(i+1)%8], 1, 8, 0 );
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
	return new IPEL_Haar3FaceEyeDetectionComp();
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
	return new IPEL_Haar3FaceEyeDetectionComp();
}

void releaseComponent(Component *com)
{
	delete com;
}
#endif
#endif

