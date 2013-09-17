#include "Varram_DRCCamera.h"
#include "OprosPrintMessage.h"

#if defined(WIN32)
#pragma warning(disable : 4996)
#endif

#include "cv.h"
#include "highgui.h"

#include "drc.h"

Varram_DRCCamera::Varram_DRCCamera(void)
:_id(0), _width(320), _height(240), _pixelByte(3), _flip(0)
{
}

Varram_DRCCamera::~Varram_DRCCamera(void)
{
}

int Varram_DRCCamera::Initialize(Property parameter)
{
	if( SetParameter(parameter) == API_ERROR ) {
		return API_ERROR;
	}
	return API_SUCCESS;
}

int Varram_DRCCamera::Enable(void)
{
	drcInit(_id, 2.470, 5, 0, 115200 ,100,  1.3);
	return API_SUCCESS;
}

int Varram_DRCCamera::Disable(void)
{
	return API_SUCCESS;
}

int Varram_DRCCamera::Finalize(void)
{
	return API_SUCCESS;
}

int Varram_DRCCamera::SetParameter(Property parameter)
{
	if (!parameter.FindName("CameraID") || 
		!parameter.FindName("Width") || 
		!parameter.FindName("Height") ||
		!parameter.FindName("PixelBytes") ||
		!parameter.FindName("Flip") )
	{
		if( !parameter.FindName("CameraID") )
			PrintMessage("Error:Varram_DRCCamera::SetParameter()->Can't find parameter ID.\n");
		if( !parameter.FindName("Width") )
			PrintMessage("Error:Varram_DRCCamera::SetParameter()->Can't find parameter Width.\n");
		if( !parameter.FindName("Height") )
			PrintMessage("Error:Varram_DRCCamera::SetParameter()->Can't find parameter Height.\n");
		if( !parameter.FindName("PixelBytes") )
			PrintMessage("Error:Varram_DRCCamera::SetParameter()->Can't find parameter PixelBytes.\n");
		if( !parameter.FindName("Flip") )
			PrintMessage("Error:Varram_DRCCamera::SetParameter()->Can't find parameter Flip.\n");

		PrintMessage("Error:Varram_DRCCamera::SetParameter()->Can't find parameter(s) name.\n");
		return API_ERROR;
	}

	_id = atoi( (parameter.GetValue("CameraID")).c_str() );
	_width = atoi( (parameter.GetValue("Width")).c_str() );
	_height = atoi( (parameter.GetValue("Height")).c_str() );
	_pixelByte = atoi( (parameter.GetValue("PixelBytes")).c_str() );
	_flip = atoi( (parameter.GetValue("Flip")).c_str() );

	this->parameter = parameter;

	return API_SUCCESS;
}

int Varram_DRCCamera::GetParameter(Property &parameter)
{
	parameter = this->parameter;

	return API_SUCCESS;
}

int Varram_DRCCamera::GetImage(unsigned char *image)
{
	IplImage *cvImage = drcGetImage(_id);
	if( cvImage ) {
		if( _flip  == 1 ) {
			cvFlip(cvImage, NULL, 0);	// x-axis
		}
		else if( _flip == 2 ) {
			cvFlip(cvImage, NULL, 1);	// y-axis
		}
		else if( _flip == 3 ) {
			cvFlip(cvImage, NULL, -1);	// xy-axis
		}

		if( cvImage->imageSize != _width*_height*_pixelByte ) {
			IplImage *resizeImage = cvCreateImage( cvSize(_width, _height), IPL_DEPTH_8U, _pixelByte );
			cvResize(cvImage, resizeImage);
			memcpy(image, resizeImage->imageData, _width*_height*_pixelByte);
			cvReleaseImage( &resizeImage );
		} else {
			memcpy(image, cvImage->imageData, _width*_height*_pixelByte);
		}

		cvSaveImage("Varram_DRCCamera.jpg", cvImage);
		cvReleaseImage(&cvImage);
		return API_SUCCESS;
	}
	else {
		return API_ERROR;
	}
}

#if defined(WIN32)
extern "C"
{
__declspec(dllexport) OprosApi *GetAPI();
__declspec(dllexport) void ReleaseAPI(OprosApi *api);
}

OprosApi *GetAPI()
{
	return new Varram_DRCCamera();
}

void ReleaseAPI(OprosApi *api)
{
	delete api;
}
#endif
