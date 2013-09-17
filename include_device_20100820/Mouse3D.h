#ifndef	_MOUSE_3D_H_
#define	_MOUSE_3D_H_

#include "Device.h"

class Mouse3D : public Device
{
public:
	Mouse3D(void) { };
	virtual ~Mouse3D(void) { };

	virtual int GetPosition(double &x, double &y, double &z) { return API_NOT_SUPPORTED; }
};

#endif	//	_MOUSE_3D_H_