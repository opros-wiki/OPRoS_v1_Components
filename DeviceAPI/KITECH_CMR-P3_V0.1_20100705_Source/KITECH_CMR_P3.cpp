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
#include "KITECH_CMR_P3.h"
#include "OprosPrintMessage.h"

using namespace boost::posix_time;

enum eTetraMobileState {
	TS_IDLE = 0,
	TS_MOVE = 1,
	TS_TURN = 2,
	TS_STOP = 3,
};

KITECH_CMR_P3::KITECH_CMR_P3(void)
{
	leftWheel = NULL;
	rightWheel = NULL;

	hOprosAPI = NULL;

	pThread = NULL;
	threadOn = false;

	position = ObjectLocation (0, 0, 0);

	_forwardVelocity = 0;
	_forwardAccel = 0;
	_centripetalAccel = 0;
}

KITECH_CMR_P3::~KITECH_CMR_P3(void)
{
	Finalize();
}

int KITECH_CMR_P3::Initialize(Property parameter)
{
	if(InitializeServoActuator(parameter) < 0) {
		PrintMessage("ERROR : KITECH_CMR_P3::Initialize() -> Occur a error in InitializeServoActuator().\n");
		return API_ERROR;
	}

	if(SetParameter(parameter) == API_ERROR) {
		PrintMessage("ERROR : KITECH_CMR_P3::Initialize() -> Occur a error in SetParameter().\n");
		return API_ERROR;
	}

	leftWheel->GetPosition(leftWheelAnglePrev);
	rightWheel->GetPosition(rightWheelAnglePrev);

	currentForward = 0;
	currentTurn = 0;
	targetForward = 0;
	targetTurn = 0;

	mobileCommand = TS_IDLE;

	isRunning = false;

	StartTask(100);

	PrintMessage("SUCCESS : KITECH_CMR_P3::onInitialize()\n");

	return API_SUCCESS;
}

int KITECH_CMR_P3::Finalize(void)
{
	StopTask();

	FinalizeServoActuator();

	return API_SUCCESS;
}

int KITECH_CMR_P3::Enable(void)
{
	if(leftWheel == NULL || rightWheel == NULL) {
		return API_ERROR;
	}

	if(leftWheel->Enable() < 0) {
		return API_ERROR;
	}

	if(rightWheel->Enable() < 0) {
		return API_ERROR;
	}

	return API_SUCCESS;
}

int KITECH_CMR_P3::Disable(void)
{
	if(leftWheel == NULL || rightWheel == NULL) {
		return API_ERROR;
	}

	if(leftWheel->Disable() < 0) {
		return API_ERROR;
	}

	if(rightWheel->Disable() < 0) {
		return API_ERROR;
	}

	return API_SUCCESS;
}

int KITECH_CMR_P3::SetParameter(Property parameter)
{
	if (parameter.FindName("WheelDiameter") == false)		return API_ERROR;
	if (parameter.FindName("AxleDistance") == false)		return API_ERROR;
	if (parameter.FindName("VarianceDistance") == false)	return API_ERROR;
	if (parameter.FindName("VarianceDirection") == false)	return API_ERROR;
	if (parameter.FindName("SafeRadius") == false)			return API_ERROR;
	if (parameter.FindName("MaximumVelocity") == false)		return API_ERROR;
	if (parameter.FindName("Acceleration") == false)		return API_ERROR;
	
	_profile.wheelDiameter = atof (parameter.GetValue("WheelDiameter").c_str());
	_profile.axleDistance = atof (parameter.GetValue("AxleDistance").c_str());
	_profile.varianceDistance = atof (parameter.GetValue("VarianceDistance").c_str());
	_profile.varianceDirection = DEG2RAD (atof (parameter.GetValue("VarianceDirection").c_str()));
	_profile.safeRadius = atof (parameter.GetValue("SafeRadius").c_str());
	_profile.maximumVelocity = atof (parameter.GetValue("MaximumVelocity").c_str());
	_profile.acceleration = atof (parameter.GetValue("Acceleration").c_str());

	this->parameter = parameter;

	return API_SUCCESS;
}

int KITECH_CMR_P3::GetParameter(Property &parameter)
{
	parameter = this->parameter;

	return API_SUCCESS;
}

int KITECH_CMR_P3::SetPosition(ObjectLocation position)
{
	this->position = position;

	return API_SUCCESS;
}

int KITECH_CMR_P3::GetPosition(ObjectLocation &position)
{
	position = this->position;

	return API_SUCCESS;
}

int KITECH_CMR_P3::Drive(double forwardVelocity, double angularVelocity)
{
	if(leftWheel == NULL || rightWheel == NULL) {
		return API_ERROR;
	}

	EstimateAcceleration (forwardVelocity, angularVelocity, 0.1);
	if (fabs(forwardVelocity) < 0.01 &&  fabs(angularVelocity) < DEG2RAD(0.5)) {
		forwardVelocity = 0.;
		angularVelocity = 0.;
	}

	forwardVelocity = bound (forwardVelocity, -_profile.maximumVelocity, _profile.maximumVelocity);
	angularVelocity = bound (angularVelocity, -DEG2RAD (40), DEG2RAD (40));

	double f = 2.*forwardVelocity/_profile.wheelDiameter;
	double a = angularVelocity*_profile.axleDistance/_profile.wheelDiameter;

	if (leftWheel->SetVelocity (RAD2DEG(f - a)) == API_ERROR) return API_ERROR;
	if (rightWheel->SetVelocity (RAD2DEG(f + a)) == API_ERROR) return API_ERROR;

	return API_SUCCESS;
}

int KITECH_CMR_P3::Move(double distance)
{
	if (0 < mobileCommand) {
		return API_ERROR;
	}

	targetForward = currentForward + distance;
	mobileCommand = TS_MOVE;
	isRunning = true;

	return API_SUCCESS;
}

int KITECH_CMR_P3::Rotate(double degree)
{
	if (0 < mobileCommand) {
		return API_ERROR;
	}

	targetTurn = currentTurn + DEG2RAD (degree);
	mobileCommand = TS_TURN;
	isRunning = true;

	return API_SUCCESS;
}

int KITECH_CMR_P3::Stop(void)
{
	mobileCommand = TS_STOP;
	return API_SUCCESS;
}

int KITECH_CMR_P3::EmergencyStop(void)
{
	if(leftWheel == NULL || rightWheel == NULL) {
		return API_ERROR;
	}

	if(leftWheel->SetVelocity(0.0) < 0) {
		return API_ERROR;
	}

	if(rightWheel->SetVelocity(0.0) < 0) {
		return API_ERROR;
	}

	return API_SUCCESS;
}

int KITECH_CMR_P3::InitializeServoActuator(Property parameter)
{
	//	CAN API 초기화
	if(parameter.FindName("ServoActuatorAPIName") == false) {
		PrintMessage("ERROR -> KITECH_CMR_P3::InitializeServoActuator() -> Can't find the ServoActuatorAPIName\n");
		return API_ERROR;
	}

	Property leftWheelParameter;
	Property rightWheelParameter;
	char *error = NULL;

	//	Servo Actuator Profile for Left Wheel
	if(parameter.FindName("MaximumPower0") == false)				goto KITECH_CMR_P3_INIT_ERROR;
	leftWheelParameter.SetValue("MaximumPower", parameter.GetValue("MaximumPower0"));

	if(parameter.FindName("LinePerRevolution0") == false)			goto KITECH_CMR_P3_INIT_ERROR;
	leftWheelParameter.SetValue("LinePerRevolution", parameter.GetValue("LinePerRevolution0"));
	
	if(parameter.FindName("ReductionRatio0") == false)				goto KITECH_CMR_P3_INIT_ERROR;
	leftWheelParameter.SetValue("ReductionRatio", parameter.GetValue("ReductionRatio0"));

	if(parameter.FindName("MaximumVelocity0") == false)				goto KITECH_CMR_P3_INIT_ERROR;
	leftWheelParameter.SetValue("MaximumVelocity", parameter.GetValue("MaximumVelocity0"));

	if(parameter.FindName("Acceleration0") == false)				goto KITECH_CMR_P3_INIT_ERROR;
	leftWheelParameter.SetValue("Acceleration", parameter.GetValue("Acceleration0"));

	if(parameter.FindName("MinimumPositionLimit0") == false)		goto KITECH_CMR_P3_INIT_ERROR;
	leftWheelParameter.SetValue("MinimumPositionLimit", parameter.GetValue("MinimumPositionLimit0"));

	if(parameter.FindName("MaximumPositionLimit0") == false)		goto KITECH_CMR_P3_INIT_ERROR;
	leftWheelParameter.SetValue("MaximumPositionLimit", parameter.GetValue("MaximumPositionLimit0"));

	if(parameter.FindName("ID0") == false)							goto KITECH_CMR_P3_INIT_ERROR;
	leftWheelParameter.SetValue("ID", parameter.GetValue("ID0"));

	//	Servo Actuator Profile for Right Wheel
	if(parameter.FindName("MaximumPower1") == false)				goto KITECH_CMR_P3_INIT_ERROR;
	rightWheelParameter.SetValue("MaximumPower", parameter.GetValue("MaximumPower1"));

	if(parameter.FindName("LinePerRevolution1") == false)			goto KITECH_CMR_P3_INIT_ERROR;
	rightWheelParameter.SetValue("LinePerRevolution", parameter.GetValue("LinePerRevolution1"));
	
	if(parameter.FindName("ReductionRatio1") == false)				goto KITECH_CMR_P3_INIT_ERROR;
	rightWheelParameter.SetValue("ReductionRatio", parameter.GetValue("ReductionRatio1"));

	if(parameter.FindName("MaximumVelocity1") == false)				goto KITECH_CMR_P3_INIT_ERROR;
	rightWheelParameter.SetValue("MaximumVelocity", parameter.GetValue("MaximumVelocity1"));

	if(parameter.FindName("Acceleration1") == false)				goto KITECH_CMR_P3_INIT_ERROR;
	rightWheelParameter.SetValue("Acceleration", parameter.GetValue("Acceleration1"));

	if(parameter.FindName("MinimumPositionLimit1") == false)		goto KITECH_CMR_P3_INIT_ERROR;
	rightWheelParameter.SetValue("MinimumPositionLimit", parameter.GetValue("MinimumPositionLimit1"));

	if(parameter.FindName("MaximumPositionLimit1") == false)		goto KITECH_CMR_P3_INIT_ERROR;
	rightWheelParameter.SetValue("MaximumPositionLimit", parameter.GetValue("MaximumPositionLimit1"));

	if(parameter.FindName("ID1") == false)							goto KITECH_CMR_P3_INIT_ERROR;
	rightWheelParameter.SetValue("ID", parameter.GetValue("ID1"));

	//	CAN Profile
	if(parameter.FindName("CANAPIName") == false)					goto KITECH_CMR_P3_INIT_ERROR;
	leftWheelParameter.SetValue("CANAPIName", parameter.GetValue("CANAPIName"));
	rightWheelParameter.SetValue("CANAPIName", parameter.GetValue("CANAPIName"));

	if(parameter.FindName("TimeOut") == false)						goto KITECH_CMR_P3_INIT_ERROR;
	leftWheelParameter.SetValue("TimeOut", parameter.GetValue("TimeOut"));
	rightWheelParameter.SetValue("TimeOut", parameter.GetValue("TimeOut"));

	if(parameter.FindName("Channel") == false)						goto KITECH_CMR_P3_INIT_ERROR;
	leftWheelParameter.SetValue("Channel", parameter.GetValue("Channel"));
	rightWheelParameter.SetValue("Channel", parameter.GetValue("Channel"));
	
	if(parameter.FindName("BitRate") == false)						goto KITECH_CMR_P3_INIT_ERROR;
	leftWheelParameter.SetValue("BitRate", parameter.GetValue("BitRate"));
	rightWheelParameter.SetValue("BitRate", parameter.GetValue("BitRate"));

	if(parameter.FindName("AcceptanceMask") == false)				goto KITECH_CMR_P3_INIT_ERROR;
	leftWheelParameter.SetValue("AcceptanceMask", parameter.GetValue("AcceptanceMask"));
	rightWheelParameter.SetValue("AcceptanceMask", parameter.GetValue("AcceptanceMask"));

	if(parameter.FindName("AcceptanceCode") == false)				goto KITECH_CMR_P3_INIT_ERROR;
	leftWheelParameter.SetValue("AcceptanceCode", parameter.GetValue("AcceptanceCode"));
	rightWheelParameter.SetValue("AcceptanceCode", parameter.GetValue("AcceptanceCode"));

	if(parameter.FindName("Mode") == false)							goto KITECH_CMR_P3_INIT_ERROR;
	leftWheelParameter.SetValue("Mode", parameter.GetValue("Mode"));
	rightWheelParameter.SetValue("Mode", parameter.GetValue("Mode"));

#if defined(WIN32)
	hOprosAPI = LoadLibrary((LPCSTR)parameter.GetValue("ServoActuatorAPIName").c_str());
	if(hOprosAPI == NULL) {
		PrintMessage("ERROR : KITECH_CMR_P3::InitializeServoActuator() -> Can't find the ServoActuatorAPIName in property\n");
		return API_ERROR;
	}

	GET_OPROS_API getOprosAPI;
	getOprosAPI = (GET_OPROS_API)GetProcAddress(hOprosAPI, "GetAPI");
	if(getOprosAPI == NULL) {
		PrintMessage("ERROR : KITECH_CMR_P3::InitializeServoActuator() -> Can't get a handle of GetAPI Funtion\n");
		FinalizeServoActuator();
		return API_ERROR;
	}
#else
	hOprosAPI = dlopen(parameter.GetValue("ServoActuatorAPIName").c_str(), RTLD_LAZY);
	if(hOprosAPI == NULL) {
		PrintMessage("ERROR : KITECH_CMR_P3::InitializeServoActuator() -> Can't find the ServoActuatorAPIName in property\n");
		return API_ERROR;
	}

	GET_OPROS_API getOprosAPI;
	getOprosAPI = (GET_OPROS_API)dlsym(hOprosAPI, "GetAPI");
	error = dlerror();
	if(error != NULL) {
		PrintMessage("ERROR : KITECH_CMR_P3::InitializeServoActuator() -> Can't get a handle of GetAPI Funtion\n");
		dlclose(hOprosAPI);
		FinalizeServoActuator();
		return API_ERROR;
	}
#endif

	leftWheel = dynamic_cast<ServoActuator *>(getOprosAPI());
	if(leftWheel == NULL) {
		PrintMessage("ERROR : KITECH_CMR_P3::InitializeServoActuator() -> Can't get a handle of ServoActuator API\n");
		FinalizeServoActuator();
		return API_ERROR;
	}

	if(leftWheel->Initialize(leftWheelParameter) == API_ERROR) {
		FinalizeServoActuator();
		return API_ERROR;
	}

	rightWheel = dynamic_cast<ServoActuator *>(getOprosAPI());
	if(rightWheel == NULL) {
		PrintMessage("ERROR : KITECH_CMR_P3::InitializeServoActuator() -> Can't get a handle of ServoActuator API\n");
		FinalizeServoActuator();
		return API_ERROR;
	}

	if(rightWheel->Initialize(rightWheelParameter) == API_ERROR) {
		FinalizeServoActuator();
		return API_ERROR;
	}

	return 0;

KITECH_CMR_P3_INIT_ERROR :
	PrintMessage("ERROR : KITECH_CMR_P3::InitializeServoActuator() -> Can't find parameters\n");
	return API_ERROR;
}

int KITECH_CMR_P3::FinalizeServoActuator(void)
{
	if(leftWheel != NULL) {
		delete leftWheel;
		leftWheel = NULL;
	}

	if(rightWheel != NULL) {
		delete rightWheel;
		rightWheel = NULL;
	}

	if(hOprosAPI != NULL) {
#if defined(WIN32)
		FreeLibrary(hOprosAPI);
#else
		dlclose(hOprosAPI);
#endif
		hOprosAPI = NULL;
	}

	return 0;
}

bool KITECH_CMR_P3::UpdatePosition()
{
	double leftWheelAngle;
	double rightWheelAngle;
	leftWheel->GetPosition(leftWheelAngle);
	rightWheel->GetPosition(rightWheelAngle);

	double dl = DEG2RAD(leftWheelAngle  - leftWheelAnglePrev);
	double dr = DEG2RAD(rightWheelAngle - rightWheelAnglePrev);

	leftWheelAnglePrev = leftWheelAngle;
	rightWheelAnglePrev = rightWheelAngle;

	double moveDelta = (dr + dl)/2 * _profile.wheelDiameter*.5;
	double turnDelta = (dr - dl)/_profile.axleDistance * _profile.wheelDiameter*.5;

	// 바퀴의 엔코더가 한번에 너무 많이 변하지 않은 경우, 
	// 유효한 엔코더로 생각한다.
	const double acceptableForwardDelta = 1.;
	const double acceptableTurnDelta = M_PI/2;
	if (-acceptableForwardDelta < moveDelta && moveDelta < acceptableForwardDelta &&
		-acceptableTurnDelta < turnDelta && turnDelta < acceptableTurnDelta ){

		//_locationPf->Predict (forwardDelta, turnDelta);
		double th = position.theta + turnDelta/2.;
		double dx = moveDelta*cos(th);
		double dy = moveDelta*sin(th);
		double dth = turnDelta;
		position += ObjectLocation (dx, dy, dth);

		currentForward += moveDelta;
		currentTurn += turnDelta;

		double varDist = moveDelta*_profile.varianceDistance;
		double varAng = turnDelta*_profile.varianceDirection;
		variance = ObjectLocation (varDist*fabs(cos(position.theta)), varDist*fabs(sin(position.theta)), fabs(varAng));
	}
	else {
		PrintMessage ("ERROR : KITECH_CMR_P3::UpdatePosition() -> Move too many:moveDelta = %g, turnDelta = %g", moveDelta, turnDelta);
	}

	return true;
}

void KITECH_CMR_P3::StartTask (long period)
{
	if((threadOn == false) && (pThread == NULL)) {
		taskPeriod = period;
		pThread = new boost::thread(boost::bind(&KITECH_CMR_P3::ThreadFunc, this));
		threadOn = true;
	}
}

void KITECH_CMR_P3::StopTask ()
{
	if((threadOn == true) && pThread) {
		threadOn = false;
		pThread->join();
		delete pThread;
		pThread = NULL;
	}
}

void KITECH_CMR_P3::DoTask()
{
	UpdatePosition ();

	switch (mobileCommand) {
		case TS_IDLE:
			isRunning = false;
			break;
		case TS_MOVE: {
			double dLength = bound (targetForward - currentForward, -_profile.maximumVelocity, _profile.maximumVelocity);
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
			if (fabs(dAngle) < DEG2RAD(10.)) {
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
				mobileCommand = TS_IDLE	;
			}
			break;
		}
		default:
			isRunning = false;
			break;
	}
}

void KITECH_CMR_P3::EstimateAcceleration (double &forwardVelocity, double &angularVelocity, double deltaTime)
{
	const double maxJerk  = 1.0;						// Unit: m/s^3
	const double maxAccel = _profile.acceleration;		// Unit: m/s^2

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


void KITECH_CMR_P3::ThreadFunc()
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
	return new KITECH_CMR_P3();
}
#else
extern "C"
{
	OprosApi *GetAPI();
}

OprosApi *GetAPI()
{
	return new KITECH_CMR_P3();
}
#endif
#endif