/*************************************************************

file: KITECH_MonteCarloLocalizationComp.cpp
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

#include "OprosMath.h"
#include "OprosPrintMessage.h"
#include "LocalizationServiceProvided.h"
#include "KITECH_MonteCarloLocalizationComp.h"


static const double epsilon = 1e-6;

//
// constructor declaration
//
KITECH_MonteCarloLocalizationComp::KITECH_MonteCarloLocalizationComp()
{
	error = 0;
	maxParticles = 300;
	portSetup();
}

//
// constructor declaration (with name)
//
KITECH_MonteCarloLocalizationComp::KITECH_MonteCarloLocalizationComp(const std::string &name):Component(name)
{
	error = 0;
	maxParticles = 300;
	portSetup();
}

//
// destructor declaration
//
KITECH_MonteCarloLocalizationComp::~KITECH_MonteCarloLocalizationComp()
{

}

void KITECH_MonteCarloLocalizationComp::portSetup()
{
	// provided service port setup
	ProvidedServicePort *pa1 = new LocalizationServiceProvided(this);
	addPort("LocalizationService",pa1);

	// required service port setup
	ptrGlobalMapService = new GlobalMapServiceRequired();
	addPort ("GlobalMapService", ptrGlobalMapService);

	ptrLaserScannerService = new LaserScannerServiceRequired();
	addPort("LaserScannerService", ptrLaserScannerService);
	
	ptrWheelControllerService = new WheelControllerServiceRequired();
	addPort("WheelControllerService", ptrWheelControllerService);
}

// Call back Declaration
ReturnType KITECH_MonteCarloLocalizationComp::onInitialize()
{
	PrintMessage ("KITECH_MonteCarloLocalizationComp::onInitialize()\n");

	parameter.SetProperty(getPropertyMap());
	if (!LoadProperty ()) {
		return OPROS_FIND_PROPERTY_ERROR;
	}

	error = 0;

	return OPROS_SUCCESS;
}

ReturnType KITECH_MonteCarloLocalizationComp::onStart()
{
	// user code here
	return OPROS_SUCCESS;
}
	
ReturnType KITECH_MonteCarloLocalizationComp::onStop()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_MonteCarloLocalizationComp::onReset()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_MonteCarloLocalizationComp::onError()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_MonteCarloLocalizationComp::onRecover()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_MonteCarloLocalizationComp::onDestroy()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_MonteCarloLocalizationComp::onEvent(Event *evt)
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_MonteCarloLocalizationComp::onExecute()
{
	// user code here
	return OPROS_SUCCESS;
}
	
ReturnType KITECH_MonteCarloLocalizationComp::onUpdated()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_MonteCarloLocalizationComp::onPeriodChanged()
{
	// user code here
	return OPROS_SUCCESS;
}

bool KITECH_MonteCarloLocalizationComp::SetParameter(Property parameter)
{
	this->parameter = parameter;
	return true;
}

Property KITECH_MonteCarloLocalizationComp::GetParameter()
{
	return parameter;
}

int KITECH_MonteCarloLocalizationComp::GetError()
{
	return error;
}

void KITECH_MonteCarloLocalizationComp::SetPosition(ObjectLocation position)
{
	currentPosition = position;
	positionPrev = position;

	particles.clear ();
	particles.reserve (maxParticles);

	for (int i = 0; i < maxParticles; ++i) {
		VirtualRobot vr;
		vr.prob = 1. / maxParticles;
		vr.pos = position;

		particles.push_back (vr);
	}
}

ObjectLocation KITECH_MonteCarloLocalizationComp::Localize()
{
	ObjectLocation position;
	if (ptrWheelControllerService) {
		position = ptrWheelControllerService->GetPosition();
		Predict(position);
	}

	vector<double> laserData;
	if (ptrLaserScannerService) {
		laserData = ptrLaserScannerService->GetLaserScannerData();
		if (ptrLaserScannerService->GetError () == 0) {
			Update(laserData);
		}
	}

	return currentPosition;
}

/*
bool KITECH_MonteCarloLocalizationComp::Predict(double deltaForward,double deltaAngle)
{
	if ((-epsilon < deltaForward && deltaForward < epsilon) &&
		(-epsilon < deltaAngle   &&   deltaAngle < epsilon) ) return false;

	double stdevDistance = sqrt(varianceDistance);
	double stdevDirection = sqrt(varianceDirection);

	// 로봇의 이동량(전진량, 회전량) 만큼 각각의 파티클을 움직인다.
	// 이 때, 이동량에 비례하는 오차(Gaussian random 으로 생성)가 추가된다.
	for (int i = 0, n = particles.size(); i < n; ++i) {
		VirtualRobot &vr = particles[i];
		double th = vr.pos.theta + deltaAngle / 2.;

		double dx = deltaForward * cos(th);
		double dy = deltaForward * sin(th);
		double dth = deltaAngle;
		double vdx = dx * stdevDistance * GaussRand ();
		double vdy = dy * stdevDistance * GaussRand ();
		double vdth = dth * stdevDirection * GaussRand ();

		vr.pos += ObjectLocation(dx + vdx, dy + vdy, dth + vdth);
	}

	StocasticPosition ();

	return true;
}
*/

bool KITECH_MonteCarloLocalizationComp::Predict(ObjectLocation position)
{
	ObjectLocation delta = diff(position, positionPrev);
	double ang = DeltaRad (delta.Atan(), positionPrev.theta);
	double sgn = (-M_PI/2 < ang && ang < M_PI/2) ? 1. : -1.;

	double deltaForward = sgn*delta.Length ();
	double deltaAngle = delta.theta;

	if ((-epsilon < deltaForward && deltaForward < epsilon) &&
		(-epsilon < deltaAngle   &&   deltaAngle < epsilon) ) return false;

	double stdevDistance = sqrt(varianceDistance);
	double stdevDirection = sqrt(varianceDirection);

	// 로봇의 이동량(전진량, 회전량) 만큼 각각의 파티클을 움직인다.
	// 이 때, 이동량에 비례하는 오차(Gaussian random 으로 생성)가 추가된다.
	for (int i = 0, n = particles.size(); i < n; ++i) {
		VirtualRobot &vr = particles[i];
		double th = vr.pos.theta + deltaAngle / 2.;

		double dx = deltaForward * cos(th);
		double dy = deltaForward * sin(th);
		double dth = deltaAngle;
		double vdx = dx * stdevDistance * GaussRand ();
		double vdy = dy * stdevDistance * GaussRand ();
		double vdth = dth * stdevDirection * GaussRand ();

		vr.pos += ObjectLocation(dx + vdx, dy + vdy, dth + vdth);
	}

	StocasticPosition ();

	positionPrev = position;

	return false;
}

bool KITECH_MonteCarloLocalizationComp::Update(std::vector<double> sensorValue)
{
	double *laserData = new double [sensorValue.size()+5];
	double sum_prob = 0.;

	memcpy (laserData, &sensorValue[0], sizeof (double) * sensorValue.size());

	for (int i = 0, n = particles.size(); i < n; ++i) {
		VirtualRobot &vr = particles[i];
		double prob = (epsilon < vr.prob) ? GetProbability (vr, laserData) : epsilon;

		vr.prob *= prob;
		sum_prob += vr.prob;
	}

	if (epsilon < sum_prob) {
		for (int i = 0, n = particles.size(); i < n; ++i) {
			particles[i].prob /= sum_prob;
		}
	}
	else {
		for (int i = 0, n = particles.size(); i < n; ++i) {
			particles[i].prob = 1./n;
		}
	}
	Resampling ();

	if (particles.size () <= 0) {
		RandomizeAt (currentPosition.x, currentPosition.y, 2.5);
	}

	delete [] laserData;	

	return false;
}

double KITECH_MonteCarloLocalizationComp::GetProbability (VirtualRobot &vr, double laserData[])
{
	if (ptrGlobalMapService == NULL) {
		return epsilon;
	}

	ObjectLocation sensorPos(sensorPosition);
	sensorPos.Transform(vr.pos);

	if (!ptrGlobalMapService->IsIn (sensorPos.x, sensorPos.y)) {
		return epsilon;
	}

	double resolution = (endAngle - startAngle) / (sensorCount - 1);

	double vr_prob = epsilon;
	for (int i = 0; i < sensorCount; ++i) {
		double &v = laserData[i];
		if (minRange < v && v < maxRange) {
			ObjectLocation ep (v, sensorPos.theta + startAngle + i * resolution);	
			ep.Translate (sensorPos.x, sensorPos.y);

			if (ptrGlobalMapService->IsIn (ep.x, ep.y)) {
				unsigned char prob = ptrGlobalMapService->GetPixel (ep.x, ep.y);
				vr_prob += prob/255.;
			}
		}
	}
	return vr_prob/sensorCount;
}

void KITECH_MonteCarloLocalizationComp::Resampling ()
{
	vector<VirtualRobot> new_particles;
	new_particles.reserve ((int)(maxParticles * 1.2));

	double sensorVariance = 0.02;
	double stdev = sqrt (sensorVariance) / 5.;

	for (int i = 0, n = particles.size(); i < n; ++i) {
		VirtualRobot &vr = particles[i];
		for (int j = 0, new_n = INTEGER(maxParticles * vr.prob); j < new_n; ++j) {
			VirtualRobot new_vr = vr;
			new_vr.pos.x  += stdev * GaussRand ();
			new_vr.pos.y  += stdev * GaussRand ();
			new_vr.pos.theta += stdev * GaussRand ();

			new_particles.push_back (new_vr);
		}
	}
	particles.swap (new_particles);
}

void KITECH_MonteCarloLocalizationComp::StocasticPosition ()
{
	if (particles.size () <= 0) return;

	ObjectLocation posAvg(0, 0, 0);
	{
		int countPlus = 0, countMinus = 0;
		ObjectLocation posPlus(0, 0, 0), posMinus(0, 0, 0);

		for (int i = 0, n = particles.size (); i < n; ++i) {
			VirtualRobot &vr = particles[i];
			vr.pos.theta = DeltaRad(vr.pos.theta, 0.);
			if (0. <= vr.pos.theta) countPlus  += 1, posPlus  += vr.pos;
			else                 countMinus += 1, posMinus += vr.pos;
		}
		posAvg.x  = (posPlus.x + posMinus.x) / (countPlus + countMinus);
		posAvg.y  = (posPlus.y + posMinus.y) / (countPlus + countMinus);
		if (0 < countPlus && 0 < countMinus) {
			double dth = DeltaRad (posPlus.theta / countPlus, posMinus.theta / countMinus);
			posAvg.theta = posMinus.theta / countMinus + dth*countPlus / (countPlus + countMinus);
		}
		else if (0 < countPlus) {
			posAvg.theta = posPlus.theta / countPlus;
		}
		else {
			posAvg.theta = posMinus.theta / countMinus;
		}
	}
	currentPosition = posAvg;

	ObjectLocation varSum (0, 0, 0);
	{
		for (int i = 0, n = particles.size (); i < n; ++i) {
			VirtualRobot &vr = particles[i];
			ObjectLocation d = diff (vr.pos, posAvg);
			varSum.x  += d.x * d.x;
			varSum.y  += d.y * d.y;
			varSum.theta += d.theta * d.theta;
		}
		varSum *= (1. / particles.size ());
	}
	variance = varSum;
}

void KITECH_MonteCarloLocalizationComp::RandomizeAt (double x, double y, double radius)
{
	particles.clear ();
	particles.reserve (maxParticles);

	for (int i=0; i < maxParticles; ++i) {
		double r = radius * (rand() % 1000) / 1000.;
		double th = DEG2RAD(rand() % 360);

		VirtualRobot vr;
		vr.pos.x = x + r*cos(th);
		vr.pos.y = y + r*sin(th);
		vr.pos.theta = th;
		vr.prob = 1. / maxParticles;

		particles.push_back (vr);
	}
	variance = ObjectLocation (radius*radius, radius*radius, DEG2RAD(360*360));
}

bool KITECH_MonteCarloLocalizationComp::LoadProperty ()
{
	if (parameter.FindName ("MaximumParticleSize") == false) {
		PrintMessage ("ERROR -> Can not found MaximumParticleSize parameter\n");
		return false;
	}
	maxParticles = atoi ((char *)parameter.GetValue("MaximumParticleSize").c_str());
	PrintMessage ("<MonteCarloLocalizationComp Parameter> MaximumParticleSize : %d\n", maxParticles);

	if (parameter.FindName ("MobileVarianceDistance") == false) {
		PrintMessage ("ERROR -> Can not found MobileVarianceDistance parameter\n");
		return false;
	}
	varianceDistance = atof ((char *)parameter.GetValue("MobileVarianceDistance").c_str());
	PrintMessage ("<MonteCarloLocalizationComp Parameter> MobileVarianceDistance : %.3lf\n", varianceDistance);

	if (parameter.FindName ("MobileVarianceDirection") == false) {
		PrintMessage ("ERROR -> Can not found MobileVarianceDirection parameter\n");
		return false;
	}
	varianceDirection = atof ((char *)parameter.GetValue("MobileVarianceDirection").c_str());
	PrintMessage ("<MonteCarloLocalizationComp Parameter> MobileVarianceDirection : %.3lf\n", varianceDirection);

	if (parameter.FindName ("LaserSensorStartAngle") == false) {
		PrintMessage ("ERROR -> Can not found LaserSensorStartAngle parameter\n");
		return false;
	}
	startAngle = DEG2RAD(atof ((char *)parameter.GetValue("LaserSensorStartAngle").c_str()));
	PrintMessage ("<MonteCarloLocalizationComp Parameter> LaserSensorStartAngle : %.3lf\n", RAD2DEG(startAngle));

	if (parameter.FindName ("LaserSensorEndAngle") == false) {
		PrintMessage ("ERROR -> Can not found LaserSensorEndAngle parameter\n");
		return false;
	}
	endAngle = DEG2RAD(atof ((char *)parameter.GetValue("LaserSensorEndAngle").c_str()));
	PrintMessage ("<MonteCarloLocalizationComp Parameter> LaserSensorEndAngle : %.3lf\n", RAD2DEG(endAngle));

	if (parameter.FindName ("LaserSensorMinimumRange") == false) {
		PrintMessage ("ERROR -> Can not found LaserSensorMinimumRange parameter\n");
		return false;
	}
	minRange = atof ((char *)parameter.GetValue("LaserSensorMinimumRange").c_str());
	PrintMessage ("<MonteCarloLocalizationComp Parameter> LaserSensorMinimumRange : %.3lf\n", minRange);

	if (parameter.FindName ("LaserSensorMaximumRange") == false) {
		PrintMessage ("ERROR -> Can not found LaserSensorMaximumRange parameter\n");
		return false;
	}
	maxRange = atof ((char *)parameter.GetValue("LaserSensorMaximumRange").c_str());
	PrintMessage ("<MonteCarloLocalizationComp Parameter> LaserSensorMaximumRange : %.3lf\n", maxRange);

	if (parameter.FindName ("LaserSensorCount") == false) {
		PrintMessage ("ERROR -> Can not found LaserSensorCount parameter\n");
		return false;
	}
	sensorCount = atoi ((char *)parameter.GetValue("LaserSensorCount").c_str());
	PrintMessage ("<MonteCarloLocalizationComp Parameter> LaserSensorCount : %d\n", sensorCount);

	if (parameter.FindName ("LaserSensorVariance") == false) {
		PrintMessage ("ERROR -> Can not found LaserSensorVariance parameter\n");
		return false;
	}
	sensorVariance = atof ((char *)parameter.GetValue("LaserSensorVariance").c_str());
	PrintMessage ("<MonteCarloLocalizationComp Parameter> LaserSensorVariance : %.3lf\n", sensorVariance);

	if (parameter.FindName ("LaserSensorPositionX") == false) {
		PrintMessage ("ERROR -> Can not found LaserSensorPositionX parameter\n");
		return false;
	}
	sensorPosition.x = atof ((char *)parameter.GetValue("LaserSensorPositionX").c_str());
	PrintMessage ("<MonteCarloLocalizationComp Parameter> LaserSensorPositionX : %.3lf\n", sensorPosition.x);

	if (parameter.FindName ("LaserSensorPositionY") == false) {
		PrintMessage ("ERROR -> Can not found LaserSensorPositionY parameter\n");
		return false;
	}
	sensorPosition.y = atof ((char *)parameter.GetValue("LaserSensorPositionY").c_str());
	PrintMessage ("<MonteCarloLocalizationComp Parameter> LaserSensorPositionY : %.3lf\n", sensorPosition.y);

	if (parameter.FindName ("LaserSensorPositionTheta") == false) {
		PrintMessage ("ERROR -> Can not found LaserSensorPositionTheta parameter\n");
		return false;
	}
	sensorPosition.theta = DEG2RAD(atof ((char *)parameter.GetValue("LaserSensorPositionTheta").c_str()));
	PrintMessage ("<MonteCarloLocalizationComp Parameter> LaserSensorPositionTheta : %.3lf\n", RAD2DEG(sensorPosition.theta));

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
	return new KITECH_MonteCarloLocalizationComp();
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
	return new KITECH_MonteCarloLocalizationComp();
}

void releaseComponent(Component *com)
{
	delete com;
}
#endif
#endif

