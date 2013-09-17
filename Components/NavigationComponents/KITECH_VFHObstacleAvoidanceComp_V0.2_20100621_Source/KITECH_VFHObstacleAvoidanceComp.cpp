/*************************************************************

file: KITECH_VFHObstacleAvoidanceComp.cpp
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
/*
 *  Generated sources by OPRoS Component Generator (OCG V2)
 *  
 */
#include <Component.h>
#include <InputDataPort.h>
#include <OutputDataPort.h>
#include <InputEventPort.h>
#include <OutputEventPort.h>
#include <OPRoSTypes.h>
#include <EventData.h>

#include "ObstacleAvoidanceServiceProvided.h"
#include "KITECH_VFHObstacleAvoidanceComp.h"
#include "OprosPrintMessage.h"

//
// constructor declaration
//
KITECH_VFHObstacleAvoidanceComp::KITECH_VFHObstacleAvoidanceComp()
{
	error = 0;
	localMap = NULL;
	portSetup();
}

//
// constructor declaration (with name)
//
KITECH_VFHObstacleAvoidanceComp::KITECH_VFHObstacleAvoidanceComp(const std::string &name):Component(name)
{
	error = 0;
	localMap = NULL;
	portSetup();
}

//
// destructor declaration
//
KITECH_VFHObstacleAvoidanceComp::~KITECH_VFHObstacleAvoidanceComp()
{
	if (localMap) {
		delete localMap;
		localMap = NULL;
	}
}

void KITECH_VFHObstacleAvoidanceComp::portSetup()
{
	// provided service port setup
	ProvidedServicePort *pa1 = new ObstacleAvoidanceServiceProvided(this);
	addPort("ObstacleAvoidanceService",pa1);

	ptrLaserScannerService = new LaserScannerServiceRequired();
	addPort("LaserScannerService", ptrLaserScannerService);
}

// Call back Declaration
ReturnType KITECH_VFHObstacleAvoidanceComp::onInitialize()
{
	PrintMessage ("KITECH_VFHObstacleAvoidanceComp::onInitialize()\n");

	parameter.SetProperty(getPropertyMap());
	if (!LoadProperty()) return OPROS_FIND_PROPERTY_ERROR;

	localMap = new 	CLocalMap (startAngle, endAngle, sensorCount, minRange, maxRange, sensorPosition); 
	if (localMap == NULL) {
		return OPROS_INTERNAL_FAULT;
	}

	error = 0;

	return OPROS_SUCCESS;
}

ReturnType KITECH_VFHObstacleAvoidanceComp::onStart()
{
	// user code here
	return OPROS_SUCCESS;
}
	
ReturnType KITECH_VFHObstacleAvoidanceComp::onStop()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_VFHObstacleAvoidanceComp::onReset()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_VFHObstacleAvoidanceComp::onError()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_VFHObstacleAvoidanceComp::onRecover()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_VFHObstacleAvoidanceComp::onDestroy()
{
	if (localMap) {
		delete localMap;
		localMap = NULL;
	}

	return OPROS_SUCCESS;
}

ReturnType KITECH_VFHObstacleAvoidanceComp::onEvent(Event *evt)
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_VFHObstacleAvoidanceComp::onExecute()
{
	// user code here
	return OPROS_SUCCESS;
}
	
ReturnType KITECH_VFHObstacleAvoidanceComp::onUpdated()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_VFHObstacleAvoidanceComp::onPeriodChanged()
{
	// user code here
	return OPROS_SUCCESS;
}

bool KITECH_VFHObstacleAvoidanceComp::SetParameter(Property parameter)
{
	this->parameter = parameter;
	if (!LoadProperty ()) return false;
	return true;
}

Property KITECH_VFHObstacleAvoidanceComp::GetParameter()
{
	error = 0;
	return parameter;
}

int KITECH_VFHObstacleAvoidanceComp::GetError()
{
	return error;
}

void KITECH_VFHObstacleAvoidanceComp::SetPosition(ObjectLocation position)
{
	error = 0;

	currentPosition = position;
	localMap->Predict (currentPosition);

	targetDistance = targetPosition.Distance (currentPosition);
	targetDirection = atan2 (targetPosition.y - currentPosition.y, targetPosition.x - currentPosition.x) - currentPosition.theta;
	localMap->Clear ();
	localMap->Predict (currentPosition);

	steerDirection = 0;
	steerForwardVel = 0;
	steerAngularVel = 0;
}

WheelControlVelocity KITECH_VFHObstacleAvoidanceComp::Avoid(ObjectLocation currentPosition, ObjectLocation targetPosition)
{
	WheelControlVelocity velocity;
	error = 0;

	this->currentPosition = currentPosition;
	this->targetPosition = targetPosition;

	targetDistance = this->targetPosition.Distance (this->currentPosition);
	targetDirection = atan2 (this->targetPosition.y - this->currentPosition.y, this->targetPosition.x - this->currentPosition.x) - this->currentPosition.theta;
	localMap->Predict(this->currentPosition);


	vector<double> laserData;
	if (ptrLaserScannerService) {
		laserData = ptrLaserScannerService->GetLaserScannerData();
		if (ptrLaserScannerService->GetError () == 0) {
			if (0 < laserData.size()) {
				double *sensorData = new double [laserData.size()];
				memcpy (sensorData, &laserData[0], sizeof (double) * laserData.size());
				localMap->Update(sensorData);
				delete [] sensorData;
			}
		}
		else {
			error = -1;
			velocity.forward = 0;
			velocity.angular = 0;
			return velocity;
		}
	}
	else {
		error = -1;
		velocity.forward = 0;
		velocity.angular = 0;
		return velocity;
	}

	MakeDirectionHistogram ();

	CalcDrivingVelocity (&velocity.forward, &velocity.angular);

	return velocity;
}

void KITECH_VFHObstacleAvoidanceComp::CalcDrivingVelocity (double *forwardVel, double *angularVel)
{
	double steerAngle = 0;
	double steerForward = 0;
	double maxValue = 0;
	double maxVelocity = min (maximumVelocity, sqrt (2.*targetDistance*acceleration));

	for (int r = 0; r < 360; ++r) {
		double histogramVelocity = maximumVelocity - polarHistogram[r];
		if (0 < histogramVelocity) {
			histogramVelocity = min (maxVelocity, histogramVelocity);

			double rr = DEG2RAD(r);
			double diffTarget      = DeltaRad(localMap->_pos.theta + targetDirection, rr);
			double diffDirection   = DeltaRad(localMap->_pos.theta + steerDirection, rr);
			double diffOrientation = DeltaRad(localMap->_pos.theta, rr);

			double value = histogramVelocity *
				exp (-2.0*(diffTarget*diffTarget)/(M_PI_2*M_PI_2)) * 
				exp (-0.5*(diffDirection*diffDirection)/(M_PI_2*M_PI_2)) * 
				exp (-1.5*(diffOrientation*diffOrientation)/(M_PI_2*M_PI_2));

			if (maxValue < value) {
				maxValue = value;
				steerAngle = DeltaRad (rr, localMap->_pos.theta);
				steerForward = histogramVelocity;
			}
		}
	}
	steerDirection = steerAngle;

	// 각속도가 클 경우 전진속도를 제한한다.
	const double limitAngle = 15.;	// !!! 전진 속도를 제한하는 각도값
	*forwardVel = steerForwardVel = steerForward*exp (-(steerAngle*steerAngle)/(2*DEG2RAD(limitAngle)*DEG2RAD(limitAngle)));
	*angularVel = steerAngularVel = steerDirection;

	//return targetDistance;
}

void KITECH_VFHObstacleAvoidanceComp::MakeDirectionHistogram ()
{
	int x, y, r;
	double polarHisto[360];
	fill (polarHisto, polarHisto + 360, 0.0);

	for (y=0; y<LOCALMAP_SIZE; ++y) {
		for (x=0; x<LOCALMAP_SIZE; ++x) {
			if (0 < localMap->_cell[y][x]) {
				double mx = localMap->CU2Mx (x);
				double my = localMap->CU2My (y);
				double l = Length (mx, my);

				if ((safeRadius*3) < l) {
					double vel = sqrt (2.*(l - safeRadius)*acceleration);
					int ang_mean = INTEGER(RAD2DEG (atan2 (my, mx)));
					int ang_cov = (int)RAD2DEG (asin (safeRadius/l));

					for (r = -ang_cov; r <= ang_cov; ++r) {
						int idx = (ang_mean + r + 360*2) % 360;
						double vel_resistance = (maximumVelocity - vel);
						polarHisto[idx] = max (polarHisto[idx], vel_resistance);
					}
				}
				else {
					double vel = 0.;
					int ang_mean = INTEGER(RAD2DEG (atan2 (my, mx)));
					int ang_cov = (int)(90 + 90*(safeRadius - l)/safeRadius);

					for (r = -ang_cov; r <= ang_cov; ++r) {
						int idx = (ang_mean + r + 360*2) % 360;
						double vel_resistance = (maximumVelocity - vel);
						polarHisto[idx] = max (polarHisto[idx], vel_resistance);
					}

					if (l < safeRadius*3/4) {
						localMap->_cell[y][x] = 0;
					}
				}
			}
		}
	}
#if defined(WIN32)
	copy (polarHisto, polarHisto + 360, stdext::checked_array_iterator<double *>(polarHistogram, 360));
#else
	copy (polarHisto, polarHisto + 360, polarHistogram);
#endif
}

bool KITECH_VFHObstacleAvoidanceComp::LoadProperty ()
{
	if (parameter.FindName ("MobileMaximumVelocity") == false) {
		PrintMessage ("ERROR -> Can not found MobilityMaximumVelocity parameter\n");
		return false;
	}
	maximumVelocity = atof ((char *)parameter.GetValue("MobileMaximumVelocity").c_str());
	PrintMessage ("<KITECH_VFHObstacleAvoidanceComp Parameter> MobileMaximumVelocity : %.3lf\n", maximumVelocity);

	if (parameter.FindName ("MobileAcceleration") == false) {
		PrintMessage ("ERROR -> Can not found MobileAcceleration parameter\n");
		return false;
	}
	acceleration = atof ((char *)parameter.GetValue("MobileAcceleration").c_str());
	PrintMessage ("<KITECH_VFHObstacleAvoidanceComp Parameter> MobileAcceleration : %.3lf\n", acceleration);

	if (parameter.FindName ("MobileSafeRadius") == false) {
		PrintMessage ("ERROR -> Can not found MobileSafeRadius parameter\n");
		return false;
	}
	safeRadius = atof ((char *)parameter.GetValue("MobileSafeRadius").c_str());
	PrintMessage ("<KITECH_VFHObstacleAvoidanceComp Parameter> MobileSafeRadius : %.3lf\n", safeRadius);

	if (parameter.FindName ("LaserSensorStartAngle") == false) {
		PrintMessage ("ERROR -> Can not found LaserSensorStartAngle parameter\n");
		return false;
	}
	startAngle = DEG2RAD(atof ((char *)parameter.GetValue("LaserSensorStartAngle").c_str()));
	PrintMessage ("<KITECH_VFHObstacleAvoidanceComp Parameter> LaserSensorStartAngle : %.3lf\n", RAD2DEG(startAngle));

	if (parameter.FindName ("LaserSensorEndAngle") == false) {
		PrintMessage ("ERROR -> Can not found LaserSensorEndAngle parameter\n");
		return false;
	}
	endAngle = DEG2RAD(atof ((char *)parameter.GetValue("LaserSensorEndAngle").c_str()));
	PrintMessage ("<KITECH_VFHObstacleAvoidanceComp Parameter> LaserSensorEndAngle : %.3lf\n", RAD2DEG(endAngle));

	if (parameter.FindName ("LaserSensorMinimumRange") == false) {
		PrintMessage ("ERROR -> Can not found LaserSensorMinimumRange parameter\n");
		return false;
	}
	minRange = atof ((char *)parameter.GetValue("LaserSensorMinimumRange").c_str());
	PrintMessage ("<KITECH_VFHObstacleAvoidanceComp Parameter> LaserSensorMinimumRange : %.3lf\n", minRange);

	if (parameter.FindName ("LaserSensorMaximumRange") == false) {
		PrintMessage ("ERROR -> Can not found LaserSensorMaximumRange parameter\n");
		return false;
	}
	maxRange = atof ((char *)parameter.GetValue("LaserSensorMaximumRange").c_str());
	PrintMessage ("<KITECH_VFHObstacleAvoidanceComp Parameter> LaserSensorMaximumRange : %.3lf\n", maxRange);

	if (parameter.FindName ("LaserSensorCount") == false) {
		PrintMessage ("ERROR -> Can not found LaserSensorCount parameter\n");
		return false;
	}
	sensorCount = atoi ((char *)parameter.GetValue("LaserSensorCount").c_str());
	PrintMessage ("<KITECH_VFHObstacleAvoidanceComp Parameter> LaserSensorCount : %d\n", sensorCount);

	if (parameter.FindName ("LaserSensorPositionX") == false) {
		PrintMessage ("ERROR -> Can not found LaserSensorPositionX parameter\n");
		return false;
	}
	sensorPosition.x = atof ((char *)parameter.GetValue("LaserSensorPositionX").c_str());
	PrintMessage ("<KITECH_VFHObstacleAvoidanceComp Parameter> LaserSensorPositionX : %.3lf\n", sensorPosition.x);

	if (parameter.FindName ("LaserSensorPositionY") == false) {
		PrintMessage ("ERROR -> Can not found LaserSensorPositionY parameter\n");
		return false;
	}
	sensorPosition.y = atof ((char *)parameter.GetValue("LaserSensorPositionY").c_str());
	PrintMessage ("<KITECH_VFHObstacleAvoidanceComp Parameter> LaserSensorPositionY : %.3lf\n", sensorPosition.y);

	if (parameter.FindName ("LaserSensorPositionTheta") == false) {
		PrintMessage ("ERROR -> Can not found LaserSensorPositionTheta parameter\n");
		return false;
	}
	sensorPosition.theta = DEG2RAD(atof ((char *)parameter.GetValue("LaserSensorPositionTheta").c_str()));
	PrintMessage ("<KITECH_VFHObstacleAvoidanceComp Parameter> LaserSensorPositionTheta : %.3lf\n", RAD2DEG(sensorPosition.theta));

	return true;
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
	return new KITECH_VFHObstacleAvoidanceComp();
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
	return new KITECH_VFHObstacleAvoidanceComp();
}

void releaseComponent(Component *com)
{
	delete com;
}
#endif
#endif

