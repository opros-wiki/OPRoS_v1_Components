#include "OpenCV_USBCamera.h"
#include "OprosPrintMessage.h"

#if defined(WIN32)
#pragma warning(disable : 4996)
#endif

OpenCV_USBCamera::OpenCV_USBCamera(void)
: _capture(0), _id(0), _width(320), _height(240), _pixelByte(3), _flip(0)
{
//	cvNamedWindow("OpenCV_USBCamera");
}

OpenCV_USBCamera::~OpenCV_USBCamera(void)
{
//	cvDestroyWindow("OpenCV_USBCamera");
}

int OpenCV_USBCamera::Initialize(Property parameter)
{
	if( SetParameter(parameter) == API_ERROR ) {
		return API_ERROR;
	}
	return API_SUCCESS;
}

int OpenCV_USBCamera::Enable(void)
{
	_capture = cvCaptureFromCAM(_id);
	if(!_capture) {
		PrintMessage("ERROR : OpenCV_USBCamera::Enable() -> Can't Enable camera device.\n");
		return API_ERROR;
	}

	cvSetCaptureProperty( _capture, CV_CAP_PROP_FRAME_WIDTH, (double)_width );
	cvSetCaptureProperty( _capture, CV_CAP_PROP_FRAME_HEIGHT, (double)_height );

	PrintMessage("SUCCESS : OpenCV_USBCamera::Enable() -> OpenCV_USBCamera enabled.\n");
	return API_SUCCESS;
}

int OpenCV_USBCamera::Disable(void)
{
	if (_capture) {
		cvReleaseCapture( &_capture );
		_capture = 0;
		PrintMessage("SUCCESS : OpenCV_USBCamera::Disable()\n");
	}

	return API_SUCCESS;
}

int OpenCV_USBCamera::Finalize(void)
{
	return API_SUCCESS;
}

int OpenCV_USBCamera::SetParameter(Property parameter)
{
	if (!parameter.FindName("CameraID") || 
		!parameter.FindName("Width") || 
		!parameter.FindName("Height") ||
		!parameter.FindName("PixelBytes") ||
		!parameter.FindName("Flip") )
	{
		if( !parameter.FindName("CameraID") )
			PrintMessage("Error:OpenCV_USBCamera::SetParameter()->Can't find parameter ID.\n");
		if( !parameter.FindName("Width") )
			PrintMessage("Error:OpenCV_USBCamera::SetParameter()->Can't find parameter Width.\n");
		if( !parameter.FindName("Height") )
			PrintMessage("Error:OpenCV_USBCamera::SetParameter()->Can't find parameter Height.\n");
		if( !parameter.FindName("PixelBytes") )
			PrintMessage("Error:OpenCV_USBCamera::SetParameter()->Can't find parameter PixelBytes.\n");
		if( !parameter.FindName("Flip") )
			PrintMessage("Error:OpenCV_USBCamera::SetParameter()->Can't find parameter Flip.\n");

		PrintMessage("Error:OpenCV_USBCamera::SetParameter()->Can't find parameter(s) name.\n");
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

int OpenCV_USBCamera::GetParameter(Property &parameter)
{
	parameter = this->parameter;

	return API_SUCCESS;
}

int OpenCV_USBCamera::GetImage(unsigned char *image)
{
	if(_capture) {
		_cvImage = cvQueryFrame(_capture);
		if(_cvImage) {

			if( _flip  == 1 ) {
				cvFlip(_cvImage, NULL, 0);	// x-axis
			}
			else if( _flip == 2 ) {
				cvFlip(_cvImage, NULL, 1);	// y-axis
			}
			else if( _flip == 3 ) {
				cvFlip(_cvImage, NULL, -1);	// xy-axis
			}

			if( _cvImage->imageSize != _width*_height*_pixelByte ) {
				IplImage *resizeImage = cvCreateImage( cvSize(_width, _height), 8, _pixelByte );
				cvResize(_cvImage, resizeImage );
				memcpy(image, resizeImage->imageData, _width*_height*_pixelByte);
				cvReleaseImage( &resizeImage );
			} else {
				memcpy(image, _cvImage->imageData, _width*_height*_pixelByte);
			}

			//cvSaveImage("OpenCV_USBCamera.jpg", _cvImage);

			return API_SUCCESS;
		}
		else {
			PrintMessage("ERROR:OpenCV_USBCamera::GetImage() -> Can't capture camera.\n");
			return API_ERROR;
		}
		//cvReleaseImage(&_cvImage);
	}
	else {
		PrintMessage("ERROR:OpenCV_USBCamera::GetImage() -> There is no camera.\n");
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
	return new OpenCV_USBCamera();
}

void ReleaseAPI(OprosApi *api)
{
	delete api;
}
#endif
