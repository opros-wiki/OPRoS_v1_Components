#pragma once

#include "Joystick.h"

class MicroSoft_Joystick : public Joystick
{
public:
	MicroSoft_Joystick(void);
	virtual ~MicroSoft_Joystick(void);

public:
	virtual int Initialize(Property parameter);
	virtual int Finalize(void);
	virtual int Enable(void);
	virtual int Disable(void);
	virtual int SetParameter(Property parameter);
	virtual int GetParameter(Property &parameter);
	virtual int GetJoystickData(JoystickData &joystickData);

private:
	Property parameter;
};
