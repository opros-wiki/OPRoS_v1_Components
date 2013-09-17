/*************************************************************

 file: DasaRobot_TetraMobile.cpp
 author: E.C. Shin
 begin: January 30 2010
 copyright: (c) 2010 KITECH, OPRoS
 email: unchol@kitech.re.kr

***************************************************************

OPRoS source code is provided under a dual license mode:
 LGPL and OPRoS individually.

LGPL: You can redistribute it and/or modify it under the terms
 of the Less GNU General Public License as published by the Free
 Software Foundation, either version 3 of the License.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of 
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
 Less GNU General Public License for more details. 

 You should have received a copy of the Less GNU General Public
 License along with this program. If not, see 
 <http://www.gnu.org/licenses/>.

OPRoS individual license: An individual license is a license for
 modifying the source code of OPRoS and distiributing it in a
 closed format for commercial purposes.

 If you are interested in this option, please see 
 <http://www.opros.or.kr>.

This license policy may be changed without prior notice.

***************************************************************/
#include "dsphal.h"
#include "DasaRobot_TetraMobile.h"
#include "OprosPrintMessage.h"

using namespace boost::posix_time;

//#define DUMMY

enum eTetraMobileState {
	TS_IDLE = 0,
	TS_MOVE = 1,
	TS_TURN = 2,
	TS_STOP = 3,
};


DasaRobot_TetraMobile::DasaRobot_TetraMobile(void)
{
	pThread = NULL;
	threadOn = false;
	
	position = ObjectLocation (0, 0, 0);
	_forwardVelocity = 0;
	_forwardAccel = 0;
	_centripetalAccel = 0;
}

DasaRobot_TetraMobile::~DasaRobot_TetraMobile(void)
{
	StopTask();
}

int DasaRobot_TetraMobile::Initialize(Property parameter)
{
	if(SetParameter(parameter) == API_ERROR) {
		PrintMessage("DasaRobot_TetraMobile::Initialize() ERROR -> SetParameter()\n");
		return API_ERROR;
	}

	SetPosition (ObjectLocation (0, 0, 0));
	SetVelocityControlMode ();
	//SetPositionControlMode ();

	ReadEncoder(&leftWheelEncoderPrev, &rightWheelEncoderPrev);

	currentForward = 0;
	currentTurn = 0;
	targetForward = 0;
	targetTurn = 0;

	mobileCommand = TS_IDLE;

	isRunning = false;

	StartTask(100);
	
	PrintMessage("DasaRobot_TetraMobile::Initialize()\n");

	return API_SUCCESS;
}

int DasaRobot_TetraMobile::Finalize(void)
{
	StopTask();
	PrintMessage("DasaRobot_TetraMobile::Finalize()\n");
	return API_SUCCESS;
}

int DasaRobot_TetraMobile::Enable(void)
{
	if (ServoOn()) {
		PrintMessage("DasaRobot_TetraMobile::Enable()\n");
		return API_SUCCESS;
	}
	return API_ERROR;
}

int DasaRobot_TetraMobile::Disable(void)
{
	if (ServoOff()) {
		PrintMessage("DasaRobot_TetraMobile::Disable()\n");
		return API_SUCCESS;
	}
	return API_ERROR;
}

int DasaRobot_TetraMobile::SetParameter(Property parameter)
{
	if (parameter.FindName("WheelDiameter") == false) return API_ERROR;
	if (parameter.FindName("AxleDistance") == false) return API_ERROR;
	if (parameter.FindName("VarianceDistance") == false) return API_ERROR;
	if (parameter.FindName("VarianceDirection") == false) return API_ERROR;
	if (parameter.FindName("SafeRadius") == false) return API_ERROR;
	if (parameter.FindName("MaximumVelocity") == false) return API_ERROR;
	if (parameter.FindName("Acceleration") == false) return API_ERROR;
	if (parameter.FindName("RobotIP") == false) return API_ERROR;
	if (parameter.FindName("RobotPort") == false) return API_ERROR;

	profile.wheelDiameter = atof (parameter.GetValue("WheelDiameter").c_str());
	profile.axleDistance = atof (parameter.GetValue("AxleDistance").c_str());
	profile.varianceDistance = atof (parameter.GetValue("VarianceDistance").c_str());
	profile.varianceDirection = DEG2RAD (atof (parameter.GetValue("VarianceDirection").c_str()));
	profile.safeRadius = atof (parameter.GetValue("SafeRadius").c_str());
	profile.maximumVelocity = atof (parameter.GetValue("MaximumVelocity").c_str());
	profile.acceleration = atof (parameter.GetValue("Acceleration").c_str());
	robotIP = parameter.GetValue("RobotIP");
	robotPort = atoi (parameter.GetValue("RobotPort").c_str());

	PrintMessage("-- TetraMobile Parameter\n");
	PrintMessage("-- WheelDiameter     : %.3lf\n", profile.wheelDiameter);
	PrintMessage("-- AxleDistance      : %.3lf\n", profile.axleDistance);
	PrintMessage("-- VarianceDistance  : %.3lf\n", profile.varianceDistance);
	PrintMessage("-- VarianceDirection : %.3lf\n", RAD2DEG(profile.varianceDirection));
	PrintMessage("-- SafeRadius        : %.3lf\n", profile.safeRadius);
	PrintMessage("-- MaximumVelocity   : %.3lf\n", profile.maximumVelocity);
	PrintMessage("-- Acceleration      : %.3lf\n", profile.acceleration);
	PrintMessage("-- RobotIP           : %s\n", robotIP.c_str ());
	PrintMessage("-- RobotPort         : %d\n", robotPort);
	PrintMessage("\n");

	int velocity = (int)(profile.maximumVelocity * 1000.0);	// m/s -> mm/s
	if (velocity < 0) velocity = 0;
	if (1000 < velocity) velocity = 1000;
	if (SetParameter (8, velocity) == false) {
		PrintMessage ("ERROR -> SetParameter(8, %d)\n", velocity);
		return false;
	}
	PrintMessage("Set Max Velocity : %.3lf(%d)\n", profile.maximumVelocity, velocity);

	int accelTime = (int)((profile.maximumVelocity / profile.acceleration) * 100.0); // 8 ~ 1000
	if (SetParameter (6, accelTime) == false) {
		PrintMessage ("ERROR -> SetParameter (6, %d)\n", accelTime);
		return false;
	}
	PrintMessage("Set Acceleration : %.3lf(%d)\n", profile.acceleration, (int)(accelTime*100));

	this->parameter = parameter;

	return API_SUCCESS;
}

int DasaRobot_TetraMobile::GetParameter(Property &parameter)
{
	parameter = this->parameter;
	return API_SUCCESS;
}

int DasaRobot_TetraMobile::SetPosition(ObjectLocation position)
{
	this->position = position;
	return API_SUCCESS;
}

int DasaRobot_TetraMobile::GetPosition(ObjectLocation &position)
{
	position = this->position;
	return API_SUCCESS;
}

int DasaRobot_TetraMobile::Drive(double forwardVelocity, double angularVelocity)
{
	//PrintMessage ("DasaRobot_TetraMobile::Drive(%.3lf, %.3lf)\n", forwardVelocity, angularVelocity);

	EstimateAcceleration (forwardVelocity, angularVelocity, 0.1);
	if (fabs(forwardVelocity) < 0.01 &&  fabs(angularVelocity) < DEG2RAD(0.5)) {
		forwardVelocity = 0.;
		angularVelocity = 0.;
	}

	//PrintMessage ("DasaRobot_TetraMobile::EstimateAcceleration(%.3lf, %.3lf)\n", forwardVelocity, angularVelocity);

	forwardVelocity = bound (forwardVelocity, -profile.maximumVelocity, profile.maximumVelocity);
	angularVelocity = bound (angularVelocity, -DEG2RAD (40), DEG2RAD (40));

	//PrintMessage ("DasaRobot_TetraMobile::bound(%.3lf, %.3lf)\n", forwardVelocity, angularVelocity);

	angularVelocity = angularVelocity * profile.axleDistance / 2.0;

	int leftVelocity = (int)((forwardVelocity - angularVelocity) * 1000.0);	// m/s에서 mm/s로 변환하기 위해 1000.0을 곱한다.
	int rightVelocity = (int)((forwardVelocity + angularVelocity) * 1000.0);

	if (VelocityControl (leftVelocity, rightVelocity)) return API_SUCCESS;
	return API_ERROR;
}

int DasaRobot_TetraMobile::Move(double distance)
{
	if (0 < mobileCommand) {
		PrintMessage ("ERROR -> mobileCommand : %d\n", mobileCommand);
		return API_ERROR;
	}

	targetForward = currentForward + distance;
	mobileCommand = TS_MOVE;
	isRunning = true;

	PrintMessage("DasaRobot_TetraMobile::Move(%.3lf)\n", distance);

	return API_SUCCESS;
}

int DasaRobot_TetraMobile::Rotate(double degree)
{
	if (0 < mobileCommand) {
		PrintMessage ("ERROR -> mobileCommand : %d\n", mobileCommand);
		return API_ERROR;
	}

	targetTurn = currentTurn + DEG2RAD (degree);
	mobileCommand = TS_TURN;
	isRunning = true;

	PrintMessage("DasaRobot_TetraMobile::Rotate(%.3lf)\n", degree);

	return API_SUCCESS;
}

int DasaRobot_TetraMobile::Stop(void)
{
	PrintMessage("DasaRobot_TetraMobile::Stop()\n");

	mobileCommand = TS_STOP;
	return API_SUCCESS;
}

int DasaRobot_TetraMobile::EmergencyStop(void)
{
	mobileCommand = TS_STOP;
	return API_SUCCESS;
}

bool DasaRobot_TetraMobile::ServoOn ()
{
	bool ret = true;
#ifndef DUMMY
	dsphal_tcp_client_t *tcp_client;

	if ((tcp_client = dsphal_tcp_client_create ((char *)robotIP.c_str (), robotPort)) == NULL) {
		PrintMessage ("ERROR : can't create client to Tetra\n");
		return false;
	}

	if (0 <= dsphal_tcp_client_connect (tcp_client)) {
		dsphal_request_method_call(tcp_client, (char *)"ServoOn", NULL);
	}
	else {
		PrintMessage ("ERROR : datalist_arg is NULL\n");
		ret = false;

	}

	dsphal_tcp_client_destroy(tcp_client);
#else
	printf ("DasaRobot_TetraMobile::ServoOn ()\n");
#endif
	return ret;
}

bool DasaRobot_TetraMobile::ServoOff ()
{
	bool ret = true;
#ifndef DUMMY
	dsphal_tcp_client_t *tcp_client;

	if ((tcp_client = dsphal_tcp_client_create ((char *)robotIP.c_str (), robotPort)) == NULL) {
		PrintMessage ("ERROR : can't create client to Tetra\n");
		return false;
	}

	if (0 <= dsphal_tcp_client_connect (tcp_client)) {
		dsphal_request_method_call(tcp_client, (char *)"ServoOff", NULL);
	}
	else {
		PrintMessage ("ERROR : datalist_arg is NULL\n");
		ret = false;
	}

	dsphal_tcp_client_destroy(tcp_client);
#else
	printf ("DasaRobot_TetraMobile::ServoOff ()\n");
#endif
	return ret;
}

bool DasaRobot_TetraMobile::VelocityControl (int leftVelocity, int rightVelocity)
{
#ifndef DUMMY
	bool ret = false;
	dsphal_tcp_client_t *tcp_client;
	
	//PrintMessage ("DasaRobot_TetraMobile::VelocityControl (%d, %d)\n", leftVelocity, rightVelocity);

	if ((tcp_client = dsphal_tcp_client_create ((char *)robotIP.c_str (), robotPort)) == NULL) {
		PrintMessage ("ERROR : can't create client to Tetra\n");
		return false;
	}

	if (0 <= dsphal_tcp_client_connect (tcp_client)) {
		dsphal_datalist_t *datalist_arg = dsphal_build_root_datalist((char *)"[{i}{i}]", leftVelocity, rightVelocity);
		if (datalist_arg) {
			dsphal_request_method_call(tcp_client, (char *)"VelocityControl", datalist_arg);
			dsphal_datalist_destroy(datalist_arg);
			ret = true;
		}
		else {
			PrintMessage ("ERROR : datalist_arg is NULL\n");
			ret = false;
		}
	}
	else {
		PrintMessage ("ERROR : can't connect to Tetra\n");
		ret = false;
	}

	dsphal_tcp_client_destroy(tcp_client);
#else
	bool ret = true;
#endif
	return ret;
}

bool DasaRobot_TetraMobile::ReadEncoder(long *leftEncoder, long *rightEncoder)
{
#ifndef DUMMY
	bool ret = false;
	dsphal_tcp_client_t *tcp_client;

	if ((tcp_client = dsphal_tcp_client_create ((char *)robotIP.c_str (), robotPort)) == NULL) {
		PrintMessage ("ERROR : can't create client to Tetra\n");
		return false;
	}

	if (0 <= dsphal_tcp_client_connect (tcp_client)) {
		dsphal_datalist_t *datalist_ret = dsphal_request_method_call(tcp_client, (char *)"ReadEncoder", NULL);
		if (datalist_ret) {
			dsphal_decompose_root_datalist(datalist_ret, (char *)"[{i}{i}]", leftEncoder, rightEncoder);
			dsphal_datalist_destroy(datalist_ret);
			ret = true;
		}
		else {
			PrintMessage ("ERROR : datalist_ret is NULL\n");
			ret = false;
		}
	}
	else {
		PrintMessage ("ERROR : can't connect to Tetra\n");
		ret = false;
	}

	dsphal_tcp_client_destroy(tcp_client);
#else
	bool ret = true;
	*leftEncoder = 0;
	*rightEncoder = 0;
#endif
	return ret;
}

bool DasaRobot_TetraMobile::ReadPosition (int *x, int *y, int *th)
{
#ifndef DUMMY
	bool ret = false;
	dsphal_tcp_client_t *tcp_client;

	if ((tcp_client = dsphal_tcp_client_create ((char *)robotIP.c_str (), robotPort)) == NULL) {
		PrintMessage ("ERROR : can't create client to Tetra\n");
		return false;
	}

	if (0 <= dsphal_tcp_client_connect (tcp_client)) {
		dsphal_datalist_t *datalist_ret = dsphal_request_method_call(tcp_client, (char *)"ReadPosition", NULL);
		if (datalist_ret) {
			dsphal_decompose_root_datalist(datalist_ret, (char *)"[{i}{i}{i}]", x, y, th);
			dsphal_datalist_destroy(datalist_ret);
			ret = true;
		}
		else {
			PrintMessage ("ERROR : datalist_ret is NULL\n");
			ret = false;
		}
	}
	else {
		printf ("ERROR : can't connect to Tetra\n");
		ret = false;
	}

	dsphal_tcp_client_destroy(tcp_client);
#else
	bool ret = true;
	*x = 0;
	*y = 0;
	*th = 0;
#endif
	return ret;
}

bool DasaRobot_TetraMobile::ChangePosition (int x, int y, int th)
{
#ifndef DUMMY
	bool ret = false;
	dsphal_tcp_client_t *tcp_client;

	if ((tcp_client = dsphal_tcp_client_create ((char *)robotIP.c_str (), robotPort)) == NULL) {
		PrintMessage ("ERROR : can't create client to Tetra\n");
		return false;
	}

	if (0 <= dsphal_tcp_client_connect (tcp_client)) {
		dsphal_datalist_t *datalist_arg = dsphal_build_root_datalist((char *)"[{i}{i}{i}]", x, y, th);
		if (datalist_arg) {
			dsphal_request_method_call(tcp_client, (char *)"ChangePosition", datalist_arg);
			dsphal_datalist_destroy(datalist_arg);
			ret = true;
		}
		else {
			PrintMessage ("ERROR : datalist_arg is NULL\n");
			ret = false;
		}
	}
	else {
		PrintMessage ("ERROR : can't connect to Tetra\n");
		ret = false;
	}

	dsphal_tcp_client_destroy(tcp_client);
#else
	bool ret = true;
#endif
	return ret;
}

bool DasaRobot_TetraMobile::SetParameter (int index, int parameter)
{
#ifndef DUMMY
	bool ret = false;
	dsphal_tcp_client_t *tcp_client;

	if ((tcp_client = dsphal_tcp_client_create ((char *)robotIP.c_str (), robotPort)) == NULL) {
		PrintMessage ("ERROR : can't create client to Tetra\n");
		return false;
	}

	if (0 <= dsphal_tcp_client_connect (tcp_client)) {
		dsphal_datalist_t *datalist_arg = dsphal_build_root_datalist((char *)"[{i}{i}]", index, parameter);
		if (datalist_arg) {
			dsphal_request_method_call(tcp_client, (char *)"SetParameter", datalist_arg);
			dsphal_datalist_destroy(datalist_arg);
			ret = true;
		}
		else {
			PrintMessage ("ERROR : datalist_arg is NULL\n");
			ret = false;
		}
	}
	else {
		PrintMessage ("ERROR : can't connect to Tetra\n");
		ret = false;
	}

	dsphal_tcp_client_destroy(tcp_client);
#else
	bool ret = true;
	printf ("DasaRobot_TetraMobile::SetParameter (%d, %d)\n", index, parameter);
#endif
	return ret;
}

bool DasaRobot_TetraMobile::GetParameter (int index, int *parameter)
{
#ifndef DUMMY
	bool ret = false;
	dsphal_tcp_client_t *tcp_client;

	if ((tcp_client = dsphal_tcp_client_create ((char *)robotIP.c_str (), robotPort)) == NULL) {
		PrintMessage ("ERROR : can't create client to Tetra\n");
		return false;
	}

	if (0 <= dsphal_tcp_client_connect (tcp_client)) {
		dsphal_datalist_t *datalist_arg = dsphal_build_root_datalist((char *)"[{i}]", index);
		if (datalist_arg) {
			dsphal_datalist_t *datalist_ret = dsphal_request_method_call(tcp_client, (char *)"GetParameter", datalist_arg);
			if (datalist_ret) {
				dsphal_decompose_root_datalist(datalist_ret, (char *)"[{i}]", parameter);
				dsphal_datalist_destroy(datalist_ret);
				ret = true;
			}
			else {
				ret = false;
			}
			dsphal_datalist_destroy(datalist_arg);
		}
		else {
			PrintMessage ("ERROR : datalist_arg is NULL\n");
			ret = false;
		}
	}
	else {
		PrintMessage ("ERROR : can't connect to Tetra\n");
		ret = false;
	}

	dsphal_tcp_client_destroy(tcp_client);
#else
	bool ret = true;
	*parameter = 0;
	printf ("GetParameter (%d, %d)\n", index, *parameter);
#endif
	return ret;
}

bool DasaRobot_TetraMobile::SetVelocityControlMode (void)
{
	bool ret = true;
#ifndef DUMMY
	dsphal_tcp_client_t *tcp_client;

	if ((tcp_client = dsphal_tcp_client_create ((char *)robotIP.c_str (), robotPort)) == NULL) {
		PrintMessage ("ERROR : can't create client to Tetra\n");
		return false;
	}

	if (0 <= dsphal_tcp_client_connect (tcp_client)) {
		dsphal_request_method_call(tcp_client, (char *)"SetVelocityControl", NULL);
	}
	else {
		PrintMessage ("ERROR : can't connect to Tetra\n");
		ret = false;
	}

	dsphal_tcp_client_destroy(tcp_client);
#else
	printf ("DasaRobot_TetraMobile::SetVelocityControlMode ()\n");
#endif
	return ret;
}

bool DasaRobot_TetraMobile::SetPositionControlMode (void)
{
	bool ret = true;
#ifndef DUMMY
	dsphal_tcp_client_t *tcp_client;

	if ((tcp_client = dsphal_tcp_client_create ((char *)robotIP.c_str (), robotPort)) == NULL) {
		PrintMessage ("ERROR : can't create client to Tetra\n");
		return false;
	}

	if (0 <= dsphal_tcp_client_connect (tcp_client)) {
		dsphal_request_method_call(tcp_client, (char *)"SetPositionControl", NULL);
	}
	else {
		PrintMessage ("ERROR : can't connect to Tetra\n");
		ret = false;
	}

	dsphal_tcp_client_destroy(tcp_client);
#else
	printf ("DasaRobot_TetraMobile::SetPositionControlMode ()\n");
#endif
	return ret;
}

bool DasaRobot_TetraMobile::UpdatePosition()
{
	long leftWheelEncoder;
	long rightWheelEncoder;

	if(!ReadEncoder(&leftWheelEncoder, &rightWheelEncoder)) {
		PrintMessage ("ERROR : readEncoder()\n");
		return false;
	}

	double diffLeftEnc = leftWheelEncoder - leftWheelEncoderPrev;
	double diffRightEnc = rightWheelEncoder - rightWheelEncoderPrev;

	double diffLeft = M_PI*profile.wheelDiameter*(diffLeftEnc/10000/20);
	double diffRight = M_PI*profile.wheelDiameter*(diffRightEnc/10000/20);

	// 아래의 3가지 변수 값을 계산해야 한다.
	double dL = (diffRight + diffLeft) / 2.0;
	double dA = (diffRight - diffLeft) / profile.axleDistance;

	currentForward += dL;
	currentTurn += dA;
	position += ObjectLocation (dL*cos(position.theta + dA/2), dL*sin(position.theta + dA/2), dA);

	double varDist = dL*profile.varianceDistance;
	double varAng = dA*profile.varianceDirection;
	variance = ObjectLocation (varDist*fabs(cos(position.theta)), varDist*fabs(sin(position.theta)), fabs(varAng));

	leftWheelEncoderPrev = leftWheelEncoder;
	rightWheelEncoderPrev = rightWheelEncoder;

	return true;
}

void DasaRobot_TetraMobile::StartTask (long period)
{
	if((threadOn == false) && (pThread == NULL)) {
		taskPeriod = period;
		pThread = new boost::thread(boost::bind(&DasaRobot_TetraMobile::ThreadFunc, this));
		threadOn = true;
	}
}

void DasaRobot_TetraMobile::StopTask ()
{
	if((threadOn == true) && pThread) {
		threadOn = false;
		pThread->join();
		delete pThread;
		pThread = NULL;
	}
}

void DasaRobot_TetraMobile::DoTask()
{
	UpdatePosition ();

	switch (mobileCommand) {
		case TS_IDLE:
			isRunning = false;
			break;
		case TS_MOVE: {
			double dLength = bound (targetForward - currentForward, -profile.maximumVelocity, profile.maximumVelocity);
			if (fabs (dLength) < 0.05) {
				mobileCommand = TS_STOP;
			}
			else {
				Drive(dLength, 0);
				isRunning = true;
			}
			break;
		}
		case TS_TURN: {
			double dAngle = bound (targetTurn - currentTurn, -DEG2RAD (45), DEG2RAD (45));
			if (fabs(dAngle) < DEG2RAD(3.)) {
				mobileCommand = TS_STOP;
			}
			else {
				Drive(0 ,dAngle);
				isRunning = true;
			}
			break;
		}
		case TS_STOP: {
			Drive(0, 0);
			if (fabs (_forwardVelocity) == 0 && fabs (_forwardAccel) == 0) {
				mobileCommand = TS_IDLE;
			}
			break;
		}
		default:
			isRunning = false;
			break;
	}
}

void DasaRobot_TetraMobile::EstimateAcceleration (double &forwardVelocity, double &angularVelocity, double deltaTime)
{
	const double maxJerk  = 1.5;						// Unit: m/s^3
	const double maxAccel = profile.acceleration;		// Unit: m/s^2

	double accel = (forwardVelocity - _forwardVelocity)/deltaTime;
	accel = bound (accel, -maxAccel, +maxAccel);

	double jerk  = (accel - _forwardAccel)/deltaTime;
	jerk = bound (jerk, -maxJerk, maxJerk);

	accel = _forwardAccel + jerk*deltaTime;
	double accelLimit = sqrt(2.*maxJerk*fabs(forwardVelocity - _forwardVelocity));
	accel = bound (accel, -accelLimit, accelLimit);

	forwardVelocity = _forwardVelocity + accel*deltaTime;

	_forwardVelocity = forwardVelocity;
	_forwardAccel = accel;	
	_centripetalAccel = forwardVelocity*angularVelocity;
}

void DasaRobot_TetraMobile::ThreadFunc()
{
	while(threadOn) {
		ptime beginTime(microsec_clock::local_time());	// 시작 시간
		DoTask();										// 실행
		ptime endTime(microsec_clock::local_time());	// 완료 시간

		// 실행시간을 계산해서 sleep할 시간을 계산한다.
		time_period elapsedTime(beginTime, endTime);	// 경과 시간
		long elapsedMicrosec = (long)elapsedTime.length().total_microseconds();  // elapsed micro sec
		long sleepTime = (long)(taskPeriod * 1000) - elapsedMicrosec;
		// 주기를 over해서 실행한 경우로써 warning을 report해야함.
		if(sleepTime < 0) {
#ifdef _DEBUG
			//cerr << "WARNING : Deadline missed !!!!!!" << endl;
#endif
		}
		else {
			boost::posix_time::microsec sleepBoostTime(sleepTime); // sleep 시간 설정 (microsec)
			boost::this_thread::sleep<boost::posix_time::microsec>(sleepBoostTime);
		}
	}
}

#if !defined(DEVICE_TEST)
#if defined(WIN32)
extern "C"
{
	__declspec(dllexport) OprosApi *GetAPI();
}

OprosApi *GetAPI()
{
	return new DasaRobot_TetraMobile();
}
#else
extern "C"
{
	OprosApi *GetAPI();
}

OprosApi *GetAPI()
{
	return new DasaRobot_TetraMobile();
}
#endif
#endif