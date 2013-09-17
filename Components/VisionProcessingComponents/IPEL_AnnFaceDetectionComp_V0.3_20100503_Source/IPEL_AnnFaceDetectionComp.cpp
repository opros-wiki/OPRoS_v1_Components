/*
 *  Generated sources by OPRoS Component Generator (OCG V2)
 *  
 */

#include "IPEL_AnnFaceDetectionComp.h"
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
IPEL_AnnFaceDetectionComp::IPEL_AnnFaceDetectionComp()
{
	portSetup();
}

//
// constructor declaration (with name)
//
IPEL_AnnFaceDetectionComp::IPEL_AnnFaceDetectionComp(const std::string &name)
{
	portSetup();
}

//
// destructor declaration
//

IPEL_AnnFaceDetectionComp::~IPEL_AnnFaceDetectionComp() 
{
	onDestroy();
}

void IPEL_AnnFaceDetectionComp::portSetup() {

	// provided service port setup
	ProvidedServicePort *pa1;
	pa1=new VisionRecognitionServiceProvided(this);
	addPort("VisionRecognitionService",pa1);
}

// Call back Declaration
ReturnType IPEL_AnnFaceDetectionComp::onInitialize()
{
	PrintMessage ("IPEL_AnnFaceDetectionComp::onInitialize()\n");

	std::map<std::string, std::string> temp = getPropertyMap();
	parameter.SetProperty(temp);
	
	return OPROS_SUCCESS;
}

ReturnType IPEL_AnnFaceDetectionComp::onStart()
{
	PrintMessage ("SUCCESS : IPEL_AnnFaceDetectionComp::onStart()\n");
	return OPROS_SUCCESS;
}
	
ReturnType IPEL_AnnFaceDetectionComp::onStop()
{
#if defined(WIN32)
	Sleep(100);
#endif

	return OPROS_SUCCESS;
}

ReturnType IPEL_AnnFaceDetectionComp::onReset()
{
	return OPROS_SUCCESS;
}

ReturnType IPEL_AnnFaceDetectionComp::onError()
{
	return OPROS_SUCCESS;
}

ReturnType IPEL_AnnFaceDetectionComp::onRecover()
{
	return OPROS_SUCCESS;
}

ReturnType IPEL_AnnFaceDetectionComp::onDestroy()
{
	return OPROS_SUCCESS;
}

ReturnType IPEL_AnnFaceDetectionComp::onEvent(Event *evt)
{
	//	IPEL_AnnFaceDetectionComp에서는 사용되지 않음.

	return OPROS_SUCCESS;
}

ReturnType IPEL_AnnFaceDetectionComp::onExecute()
{
	//PrintMessage("SUCCESS:IPEL_AnnFaceDetectionComp::onExecute()\n");

	return OPROS_SUCCESS;
}
	
ReturnType IPEL_AnnFaceDetectionComp::onUpdated()
{
	//	IPEL_AnnFaceDetectionComp에서는 사용되지 않음.

	return OPROS_SUCCESS;
}

ReturnType IPEL_AnnFaceDetectionComp::onPeriodChanged()
{
	//	IPEL_AnnFaceDetectionComp에서는 사용되지 않음.

	return OPROS_SUCCESS;
}


bool IPEL_AnnFaceDetectionComp::SetParameter(Property parameter)
{
	//	API 핸들이 NULL이거나 컴포넌트의 상태가 ACTIVE 또는 INACTIVE 상태가 아니면
	//	에러를 리턴
	if( (getStatus() != OPROS_CS_ACTIVE && getStatus() != OPROS_CS_INACTIVE)) {
		return false;
	}

	//	API의 SetParameter 함수 호출
	return true;
}
Property IPEL_AnnFaceDetectionComp::GetParameter()
{
	return this->parameter;
}

vector<VisionRecognitionResult> IPEL_AnnFaceDetectionComp::Recognize(vector<unsigned char> image,int width,int height,int pixelBytes)
{
	//PrintMessage("SUCCESS:IPEL_AnnFaceDetectionComp::Recognize()\n");

	vector<VisionRecognitionResult> _recognitionResult(0);

	// 입력영상은 모두 80x60으로 설정된다.
	double resizeRatio = 80.0/width;

	// 피라미드 영상을 위해 resize된 80x60영상은 다시 세가지 영상으로 interpolate된다.
	double scales[3] = {0.86, 0.73, 0.6};

	IplImage *cvImage = cvCreateImageHeader( cvSize(width, height), 8, pixelBytes );
	cvImage->imageData = (char *)&image[0];

	if(!_initAnn) {
		_scales.clear();
		for (unsigned int i=0;i<3;i++) _scales.push_back((float)scales[i]);

		_resize.init(cvImage->width, cvImage->height, (float)resizeRatio);
		_mDetect.init(_resize.gety()->width(), _resize.gety()->height());

		if (_scales.size()) {
			_fDetect.init(_resize.gety()->width(), _resize.gety()->height(), 19, 19,
				&_scales[0], (unsigned int)_scales.size());
		} 
		else {
			_fDetect.init(_resize.gety()->width(), _resize.gety()->height(), 19, 19);
		}

		_fDetect.load_face_classifier(L"face.nn");
		_fDetect.load_projection_matrix(L"pca.nn");
		_fDetect.load_skin_filter(L"skin.nn") ;
		_fDetect.load_preface_filter(L"preflt.nn");
		_fDetect.status_of_classifiers();

		_initAnn = true;
	}

	/* detect eyes and display image */

	if (_resize.gety()!=0) {

		_resize.resize((unsigned char*)cvImage->imageData);

		int nFaces = _fDetect.detect(_resize.gety(), _resize.getr(), _resize.getg(), _resize.getb(), _mDetect.detect(_resize.gety(), &_fDetect));
		if(nFaces>0) {

			_recognitionResult.resize (nFaces);

			for (int i = 0; i < nFaces; i++) {

				const RECT* r = _fDetect.get_face_rect(i);

				//rec.type = 1;
				char buffer[256];
				_recognitionResult[i].name = "Face";
				_itoa_s(i,buffer,sizeof(buffer),10);
				_recognitionResult[i].name.append( buffer );
				/*- Get Upper left rectangle corner coordinate -*/
				_recognitionResult[i].point1X = (int)((r->left) / resizeRatio + 0.5);
				_recognitionResult[i].point1Y = (int)((r->top) / resizeRatio + 0.5);
				/*- Get Upper right rectangle corner coordinate -*/
				_recognitionResult[i].point2X = (int)((r->right) / resizeRatio + 0.5);
				_recognitionResult[i].point2Y = (int)((r->top) / resizeRatio + 0.5);
				/*- Get Lower right rectangle corner coordinate -*/
				_recognitionResult[i].point3X = (int)((r->right) / resizeRatio + 0.5);
				_recognitionResult[i].point3Y = (int)((r->bottom) / resizeRatio + 0.5);
				/*- Get Lower left rectangle corner coordinate -*/
				_recognitionResult[i].point4X = (int)((r->left) / resizeRatio + 0.5);
				_recognitionResult[i].point4Y = (int)((r->bottom) / resizeRatio + 0.5);
			}
		}
	}
	cvReleaseImageHeader( &cvImage );

	PrintMessage("INFO : IPEL_AnnFaceDetectionComp::Recognize() -> %d\n", _recognitionResult.size());

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
	return new IPEL_AnnFaceDetectionComp();
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
	return new IPEL_AnnFaceDetectionComp();
}

void releaseComponent(Component *com)
{
	delete com;
}
#endif
#endif

