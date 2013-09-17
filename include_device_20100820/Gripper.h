#ifndef	_GRIPPER_H_
#define	_GRIPPER_H_

#include "Manipulator.h"

class Gripper : public Manipulator
{
public:
	Gripper(void) { };
	virtual ~Gripper(void) { };

public:
	virtual int StartGripping(void) { return API_NOT_SUPPORTED; }
	virtual int StopGripping(void) { return API_NOT_SUPPORTED; }
	virtual int IsGripped(void) { return API_NOT_SUPPORTED; }
};


#endif	//	_GRIPPER_H_