/*
 *  Generated sources by OPRoS Component Generator (OCG V2)
 *  
 */

#include "KITECH_VerilookFaceRecognitionComp.h"
#include "OprosPrintMessage.h"

//
// constructor declaration
//
KITECH_VerilookFaceRecognitionComp::KITECH_VerilookFaceRecognitionComp()
{
	portSetup();
}

//
// constructor declaration (with name)
//
KITECH_VerilookFaceRecognitionComp::KITECH_VerilookFaceRecognitionComp(const std::string &name)
{
	portSetup();
}

//
// destructor declaration
//

KITECH_VerilookFaceRecognitionComp::~KITECH_VerilookFaceRecognitionComp() 
{
	onDestroy();
}

void KITECH_VerilookFaceRecognitionComp::portSetup() {

	// provided service port setup
	
	ProvidedServicePort *pa1;
	pa1=new VisionRecognitionServiceProvided(this);
	addPort("VisionRecognitionService",pa1);
}

// Call back Declaration
ReturnType KITECH_VerilookFaceRecognitionComp::onInitialize()
{
	PrintMessage ("KITECH_VerilookFaceRecognitionComp::onInitialize()\n");

	std::map<std::string, std::string> temp = getPropertyMap();
	parameter.SetProperty(temp);

	return OPROS_SUCCESS;
}

ReturnType KITECH_VerilookFaceRecognitionComp::onStart()
{
	NleCreate(&_hExtractor);

	return OPROS_SUCCESS;
}
	
ReturnType KITECH_VerilookFaceRecognitionComp::onStop()
{
#if defined(WIN32)
	Sleep(100);
#endif
	NleFree(_hExtractor);

	return OPROS_SUCCESS;
}

ReturnType KITECH_VerilookFaceRecognitionComp::onReset()
{
	return OPROS_SUCCESS;
}

ReturnType KITECH_VerilookFaceRecognitionComp::onError()
{
	return OPROS_SUCCESS;
}

ReturnType KITECH_VerilookFaceRecognitionComp::onRecover()
{
	return OPROS_SUCCESS;
}

ReturnType KITECH_VerilookFaceRecognitionComp::onDestroy()
{
	return OPROS_SUCCESS;
}

ReturnType KITECH_VerilookFaceRecognitionComp::onEvent(Event *evt)
{
	//	KITECH_VerilookFaceRecognitionComp에서는 사용되지 않음.

	return OPROS_SUCCESS;
}

ReturnType KITECH_VerilookFaceRecognitionComp::onExecute()
{
	//PrintMessage("SUCCESS:KITECH_VerilookFaceRecognitionComp::onExecute()\n");

	return OPROS_SUCCESS;
}
	
ReturnType KITECH_VerilookFaceRecognitionComp::onUpdated()
{
	//	KITECH_VerilookFaceRecognitionComp에서는 사용되지 않음.

	return OPROS_SUCCESS;
}

ReturnType KITECH_VerilookFaceRecognitionComp::onPeriodChanged()
{
	//	KITECH_VerilookFaceRecognitionComp에서는 사용되지 않음.

	return OPROS_SUCCESS;
}


bool KITECH_VerilookFaceRecognitionComp::SetParameter(::Property parameter)
{
	//	API 핸들이 NULL이거나 컴포넌트의 상태가 ACTIVE 또는 INACTIVE 상태가 아니면
	//	에러를 리턴
	if( (getStatus() != OPROS_CS_ACTIVE && getStatus() != OPROS_CS_INACTIVE)) {
		return false;
	}

	//	API의 SetParameter 함수 호출
	return true;
}
::Property KITECH_VerilookFaceRecognitionComp::GetParameter()
{
	return this->parameter;
}

vector<VisionRecognitionResult> KITECH_VerilookFaceRecognitionComp::Recognize(vector<unsigned char> image,int width,int height,int pixelBytes)
{
	//PrintMessage("SUCCESS:KITECH_VerilookFaceRecognitionComp::Recognize()\n");

	vector<VisionRecognitionResult> _recognitionResult(0);

	HNImage hImage;
	MakeGrayNImage (&hImage, (BYTE *)&image[0], width, height, pixelBytes);
	DetectFaceOnce (_hExtractor, hImage, _recognitionResult);
	NImageFree(hImage);

	return _recognitionResult;
}


/**
 *	카메라에서 받은 이미지를 OpenCV를 이용하여 Gray image로 변환 후 이를 다시 HNImage 형태로 변환한다.
 */
void KITECH_VerilookFaceRecognitionComp::MakeGrayNImage (HNImage *nImage, const BYTE *RGBimage, int width, int height, int pixelByte)
{
	IplImage *cvRGBImage = cvCreateImageHeader( cvSize(width, height), IPL_DEPTH_8U, pixelByte );
	cvRGBImage->imageData = (char *)RGBimage;

	IplImage *cvGrayImage = cvCreateImage( cvGetSize(cvRGBImage), IPL_DEPTH_8U, 1 );
	cvConvertImage( cvRGBImage, cvGrayImage, CV_BGR2GRAY );	// RGB이미지를 Gray이미지로 변환

	// Create HNImage from Grayscale Image data
	NResult result = NImageCreateFromData(npfGrayscale, (NUInt)width, (NUInt)height, (NSizeType)width, 0.0, 0.0, (NSizeType)width, cvGrayImage->imageData, nImage);

	// Release OpenCV variables
	cvReleaseImage(&cvGrayImage);
	cvReleaseImageHeader(&cvRGBImage);
}

/**
 * Detects face in single frame/image.
 * @param	image				image for face detection.
 */
NResult KITECH_VerilookFaceRecognitionComp::DetectFaceOnce(HNLExtractor _hExtractor, HNImage hImage, std::vector<VisionRecognitionResult> &faceResult)
{
	NInt faceCount = 0;
	NleFace *fd = NULL;
	NResult res = NleDetectFaces(_hExtractor, hImage, &faceCount, &fd);

	if (NSucceeded(res))
	{
		if (faceCount > 0)
		{
			NleDetectionDetails *details = (NleDetectionDetails *) malloc(sizeof(NleDetectionDetails) * faceCount);
			for (int i = 0; i < faceCount; ++i)
			{
				details[i].FaceAvailable = NTrue;
				details[i].Face = fd[i];
				if (i == 0)
				{
					details[i].EyesAvailable = NTrue;
					res = NleDetectFacialFeatures(_hExtractor, hImage, &fd[i], &details[i]);
					if (NFailed(res))
					{
						details[i].EyesAvailable = NFalse;
					}
				}
				else
				{
					details[i].EyesAvailable = NFalse;
				}
			}

			NFree(fd);
			faceResult.resize (faceCount);
			// 찾은 얼굴을 저장
			int n = 0;
			for (int i = 0; i < faceCount; ++i)
			{
				if( details[i].FaceAvailable )
				{
					faceResult[n].name = "Face";
					faceResult[n].point1X = details[i].Face.Rectangle.X;
					faceResult[n].point1Y = details[i].Face.Rectangle.Y;
					faceResult[n].point2X = details[i].Face.Rectangle.X+details[i].Face.Rectangle.Width;
					faceResult[n].point2Y = details[i].Face.Rectangle.Y;
					faceResult[n].point3X = details[i].Face.Rectangle.X+details[i].Face.Rectangle.Width;
					faceResult[n].point3Y = details[i].Face.Rectangle.Y+details[i].Face.Rectangle.Height;
					faceResult[n].point4X = details[i].Face.Rectangle.X;
					faceResult[n].point4Y = details[i].Face.Rectangle.Y+details[i].Face.Rectangle.Height;
					n++;
				}
			}
			free(details);
		}
		else
		{
			// - fail if no face was detected
			faceResult.resize(0);
			res = N_E_FAILED;
		}
	}

	return res;
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
	return new KITECH_VerilookFaceRecognitionComp();
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
	return new KITECH_VerilookFaceRecognitionComp();
}

void releaseComponent(Component *com)
{
	delete com;
}
#endif
#endif

