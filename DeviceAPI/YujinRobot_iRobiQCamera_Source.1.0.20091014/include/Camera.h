#ifndef	_CAMERA_H_
#define	_CAMERA_H_

#include "Device.h"

namespace OPRoS
{

class Camera : public Device
{
public:
	Camera(void) { };
	virtual ~Camera(void) { };

public:
	virtual bool getImage(unsigned char *image) = 0;
};

};

#endif	//	_CAMERA_H_