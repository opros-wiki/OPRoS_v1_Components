/*
 *  Generated sources by OPRoS Component Generator (OCG V2)
 *  
 */

#include "KITECH_HSVColorRecognitionComp.h"
#include "OprosPrintMessage.h"

#include "cv.h"
#include "highgui.h"
#include "BlobLabeling.h"

//
// constructor declaration
//
KITECH_HSVColorRecognitionComp::KITECH_HSVColorRecognitionComp()
{
	portSetup();
}

//
// constructor declaration (with name)
//
KITECH_HSVColorRecognitionComp::KITECH_HSVColorRecognitionComp(const std::string &name)
{
	portSetup();
}

//
// destructor declaration
//

KITECH_HSVColorRecognitionComp::~KITECH_HSVColorRecognitionComp() 
{
	onDestroy();
}

void KITECH_HSVColorRecognitionComp::portSetup() {

	// provided service port setup
	
	ProvidedServicePort *pa1;
	pa1=new VisionRecognitionServiceProvided(this);
	addPort("VisionRecognitionService",pa1);
}

// Call back Declaration
ReturnType KITECH_HSVColorRecognitionComp::onInitialize()
{
	PrintMessage ("KITECH_HSVColorRecognitionComp::onInitialize()\n");

	std::map<std::string, std::string> temp = getPropertyMap();
	parameter.SetProperty(temp);
	
	if(parameter.FindName("DBName") == false) {
		PrintMessage("ERROR : KITECH_HSVColorRecognitionComp::onInitialize() -> Can't find the DBName in property\n");
		return OPROS_FIND_PROPERTY_ERROR;
	}

	return OPROS_SUCCESS;
}

ReturnType KITECH_HSVColorRecognitionComp::onStart()
{
	if(parameter.FindName("DBName")) {
		GetDataFromDB(parameter.GetValue("DBName").c_str());
	}

	return OPROS_SUCCESS;
}
	
ReturnType KITECH_HSVColorRecognitionComp::onStop()
{
#if defined(WIN32)
	Sleep(100);
#endif
	if(parameter.FindName("DBName")) {
		SetDataToDB(parameter.GetValue("DBName").c_str());
	}

	return OPROS_SUCCESS;
}

ReturnType KITECH_HSVColorRecognitionComp::onReset()
{
	return OPROS_SUCCESS;
}

ReturnType KITECH_HSVColorRecognitionComp::onError()
{
	return OPROS_SUCCESS;
}

ReturnType KITECH_HSVColorRecognitionComp::onRecover()
{
	return OPROS_SUCCESS;
}

ReturnType KITECH_HSVColorRecognitionComp::onDestroy()
{
	return OPROS_SUCCESS;
}

ReturnType KITECH_HSVColorRecognitionComp::onEvent(Event *evt)
{
	//	KITECH_HSVColorRecognitionComp에서는 사용되지 않음.

	return OPROS_SUCCESS;
}

ReturnType KITECH_HSVColorRecognitionComp::onExecute()
{
	//PrintMessage("SUCCESS:KITECH_HSVColorRecognitionComp::onExecute()\n");

	return OPROS_SUCCESS;
}
	
ReturnType KITECH_HSVColorRecognitionComp::onUpdated()
{
	//	KITECH_HSVColorRecognitionComp에서는 사용되지 않음.

	return OPROS_SUCCESS;
}

ReturnType KITECH_HSVColorRecognitionComp::onPeriodChanged()
{
	//	KITECH_HSVColorRecognitionComp에서는 사용되지 않음.

	return OPROS_SUCCESS;
}


bool KITECH_HSVColorRecognitionComp::SetParameter(Property parameter)
{
	//	API 핸들이 NULL이거나 컴포넌트의 상태가 ACTIVE 또는 INACTIVE 상태가 아니면
	//	에러를 리턴
	if( (getStatus() != OPROS_CS_ACTIVE && getStatus() != OPROS_CS_INACTIVE)) {
		return false;
	}

	//	API의 SetParameter 함수 호출
	return true;
}
Property KITECH_HSVColorRecognitionComp::GetParameter()
{
	return this->parameter;
}

vector<VisionRecognitionResult> KITECH_HSVColorRecognitionComp::Recognize(vector<unsigned char> image,int width,int height,int pixelBytes)
{
	//PrintMessage("SUCCESS:KITECH_HSVColorRecognitionComp::Recognize()");

	vector<VisionRecognitionResult> _recognitionResult(0);
	VisionRecognitionResult tmpResult;
	
	IplImage *cvImage = cvCreateImageHeader( cvSize(width, height), 8, pixelBytes );
	cvImage->imageData = (char *)&image[0];

	IplImage *hsvImage = cvCreateImage( cvGetSize(cvImage), 8, pixelBytes );
	cvCvtColor(cvImage, hsvImage, CV_BGR2HSV);

	IplImage *cvMask= cvCreateImage( cvSize(width, height), IPL_DEPTH_8U, 1 );

	for( unsigned int p = 0  ;  p < _colorRange.size()  ;  p++ ) {

		cvInRangeS( hsvImage,
				cvScalar(_colorRange[p].min1,_colorRange[p].min2,_colorRange[p].min3,0),
				cvScalar(_colorRange[p].max1,_colorRange[p].max2,_colorRange[p].max3,255),
				cvMask );

		CBlobLabeling blob;
		blob.SetParam( cvMask, width*height/1000 );
		blob.DoLabeling();

//		_recognitionResult.resize(blob.m_nBlobs);
		for( int i = 0  ;  i < blob.m_nBlobs  ;  i++ ) {
			tmpResult.name = _colorRange[p].name;

			tmpResult.point1X = blob.m_recBlobs[i].x;
			tmpResult.point1Y = blob.m_recBlobs[i].y;
			tmpResult.point2X = blob.m_recBlobs[i].x + blob.m_recBlobs[i].width;
			tmpResult.point2Y = blob.m_recBlobs[i].y;
			tmpResult.point3X = blob.m_recBlobs[i].x + blob.m_recBlobs[i].width;
			tmpResult.point3Y = blob.m_recBlobs[i].y + blob.m_recBlobs[i].height;
			tmpResult.point4X = blob.m_recBlobs[i].x;
			tmpResult.point4Y = blob.m_recBlobs[i].y + blob.m_recBlobs[i].height;
			_recognitionResult.push_back(tmpResult);
			//PrintMessage("SUCCESS:KITECH_HSVColorRecognitionComp::Recognize() -> I found %d data.(%d=%s)\n", blob.m_nBlobs, i, tmpResult.name.c_str());
		}
	}

	//cvSaveImage("KITECH_HSVColorRecognitionComp.jpg", cvImage);

	cvReleaseImage(&cvMask);
	cvReleaseImage(&hsvImage);
	cvReleaseImageHeader(&cvImage);

	return _recognitionResult;
}

void KITECH_HSVColorRecognitionComp::GetDataFromDB(const char* database)
{
	char str[256];
	CvFileStorage *fs = cvOpenFileStorage(database, 0, CV_STORAGE_READ);
	int colorCount = cvReadIntByName(fs, 0, "color_count");
	ColorRange colorRange;
	for( int i = 0  ;  i < colorCount  ;  i++ ) {
		sprintf(str, "color%d", i);
		CvSeq *s = cvGetFileNodeByName(fs, 0, str)->data.seq;
		colorRange.name = cvReadString( (CvFileNode*)cvGetSeqElem(s, 0) );
		colorRange.min1 = cvReadInt( (CvFileNode*)cvGetSeqElem(s, 1) );
		colorRange.max1 = cvReadInt( (CvFileNode*)cvGetSeqElem(s, 2) );
		colorRange.min2 = cvReadInt( (CvFileNode*)cvGetSeqElem(s, 3) );
		colorRange.max2 = cvReadInt( (CvFileNode*)cvGetSeqElem(s, 4) );
		colorRange.min3 = cvReadInt( (CvFileNode*)cvGetSeqElem(s, 5) );
		colorRange.max3 = cvReadInt( (CvFileNode*)cvGetSeqElem(s, 6) );
		_colorRange.push_back(colorRange);
//		PrintMessage("INFO:KITECH_HSVColorRecognitionComp::Add color data : %s\n", colorRange.name.c_str());
	}
}

void KITECH_HSVColorRecognitionComp::SetDataToDB(const char* database)
{
	char str[256];
	CvFileStorage *fs = cvOpenFileStorage(database, 0, CV_STORAGE_WRITE);
	cvWriteInt(fs, "color_count", (int)_colorRange.size());
	for( int i = 0  ;  i < (int)_colorRange.size()  ;  i++ ) {
		sprintf(str, "color%d", i);
		cvStartWriteStruct(fs, str, CV_NODE_SEQ);
		cvWriteString( fs, 0, _colorRange[i].name.c_str() );
		cvWriteInt( fs, 0, _colorRange[i].min1 );
		cvWriteInt( fs, 0, _colorRange[i].max1 );
		cvWriteInt( fs, 0, _colorRange[i].min2 );
		cvWriteInt( fs, 0, _colorRange[i].max2 );
		cvWriteInt( fs, 0, _colorRange[i].min3 );
		cvWriteInt( fs, 0, _colorRange[i].max3 );
		cvEndWriteStruct(fs);
	}
	cvReleaseFileStorage(&fs);
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
	return new KITECH_HSVColorRecognitionComp();
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
	return new KITECH_HSVColorRecognitionComp();
}

void releaseComponent(Component *com)
{
	delete com;
}
#endif
#endif

