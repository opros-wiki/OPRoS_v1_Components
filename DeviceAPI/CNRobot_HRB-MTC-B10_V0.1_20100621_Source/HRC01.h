#pragma once

class HRC01
{
public:
	HRC01(void);
	virtual ~HRC01(void);

private:
	bool isOpened;

public:
	int Open(void);
	void Close(void);

	int Reset(int axis = 0);
	int Enable(int axis = 0);
	int Stop(int axis = 0);
	int QuickStop(int axis = 0);

	//	PID Gain, 0 ~ 32767
	int SetPIDGain(int axis, unsigned short kp, unsigned short ki, unsigned short kd, unsigned short iSum = 32767);
	int SetPIDGain(	unsigned short kp1, unsigned short ki1, unsigned short kd1, unsigned short iSum1,
					unsigned short kp2, unsigned short ki2, unsigned short kd2, unsigned short iSum2,
					unsigned short kp3, unsigned short ki3, unsigned short kd3, unsigned short iSum3);

	
	//	Acceleration, 단위 : Encoder Pulse / S^2
	int SetAcceleration(int axis, unsigned int acceleration);
	int SetAcceleration(unsigned int acceleration1, unsigned int acceleration2, unsigned int acceleration3);

	//	Maximum Velocity 단위 : Encoder Pulse / S
	int SetMaximumVelocity(int axis, unsigned int maximumVelocity);
	int SetMaximumVelocity(unsigned int maximumVelocity1, unsigned int maximumVelocity2, unsigned int maximumVelocity3);

	//	Velocity Control
	int SetVelocity(int axis, int velocity);
	int SetVelocity(int velocity1, int velocity2, int velocity3);
	int GetVelocity(int axis, int &velocity);
	void GetVelocity(int velocity[3]);


	//	Position Control, 단위 : Encoder Pulse
	int SetPosition(int axis, int position);
	int SetPosition(int position1, int position2, int position3);
	int SetPositionDelta(int axis, int position);
	int SetPositionDelta(int position1, int position2, int position3);
	int GetPosition(int axis, int &position);
	void GetPosition(int position[3]);

};
