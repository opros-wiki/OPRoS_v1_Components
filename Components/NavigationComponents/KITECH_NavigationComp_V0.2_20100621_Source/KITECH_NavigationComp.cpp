/*************************************************************

file: KITECH_NavigationComp.cpp
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

#ifdef	WIN32
#include "Dialog/stdafx.h"
#endif

#include "KITECH_NavigationComp.h"
#include "NavigationServiceProvided.h"
#include "OprosMath.h"
#include "OprosPrintMessage.h"
#include "OprosTimer.h"


#ifdef USE_GUI
KITECH_NavigationComp *naviComp;
#endif

#ifdef	WIN32
UINT NavigationDlgThreadProc(LPVOID pParam);
#endif

enum eNavigationState {
	NS_IDLE = 0,
	NS_NAVIGATION_TO = 11,
	NS_MOVE_TO = 21,
	NS_MOVE_DELTA = 31,
	NS_TURN = 41,
	NS_STOP = 100,
};


//
// constructor declaration
//
KITECH_NavigationComp::KITECH_NavigationComp()
{
	error = 0;
#ifdef USE_GUI
	naviComp = this;
	navigationDlg = NULL;
#endif
	portSetup();
}

//
// constructor declaration (with name)
//
KITECH_NavigationComp::KITECH_NavigationComp(const std::string &name):Component(name)
{
	error = 0;
#ifdef USE_GUI
	naviComp = this;
	navigationDlg = NULL;
#endif
	portSetup();
}

//
// destructor declaration
//
KITECH_NavigationComp::~KITECH_NavigationComp()
{

}

void KITECH_NavigationComp::portSetup()
{
	// provided service port setup
	ProvidedServicePort *pa1 = new NavigationServiceProvided(this);
	addPort("NavigationService",pa1);

	// required service port setup
	ptrGlobalMapService = new GlobalMapServiceRequired();
	addPort("GlobalMapService", ptrGlobalMapService);

	ptrPathPlanningService = new PathPlanningServiceRequired();
	addPort("PathPlanningService", ptrPathPlanningService);

	ptrLocalizationService = new LocalizationServiceRequired();
	addPort("LocalizationService", ptrLocalizationService);
	//ptrLocalizationService = NULL;

	ptrObstacleAvoidanceService = new ObstacleAvoidanceServiceRequired();
	addPort("ObstacleAvoidanceService", ptrObstacleAvoidanceService);
	//ptrObstacleAvoidanceService = NULL;

	ptrLaserScannerService = new LaserScannerServiceRequired();
	addPort("LaserScannerService", ptrLaserScannerService);
	//ptrLaserScannerService = NULL;
	
	ptrWheelControllerService = new WheelControllerServiceRequired();
	addPort("WheelControllerService", ptrWheelControllerService);
	//ptrWheelControllerService = NULL;
}

// Call back Declaration
ReturnType KITECH_NavigationComp::onInitialize()
{
	PrintMessage ("KITECH_NavigationComp::onInitialize()\n");

	parameter.SetProperty(getPropertyMap());
	if (!LoadProperty()) return OPROS_FIND_PROPERTY_ERROR;

	navigationStep = NS_IDLE;
	currentPosition = ObjectLocation(0, 0, 0);
	targetPosition = ObjectLocation(0, 0, 0);
	subTargetPosition = ObjectLocation(0, 0, 0);
	path.clear();

	error = 0;

	return OPROS_SUCCESS;
}

ReturnType KITECH_NavigationComp::onStart()
{
	PrintMessage ("KITECH_NavigationComp::onStart()\n");

	SetPosition(currentPosition);

	if (ptrWheelControllerService) {
		wheelControllerParameter = ptrWheelControllerService->GetParameter();
		if (ptrWheelControllerService->GetError() == 0) {
			if (wheelControllerParameter.FindName("SafeRadius")) {
				mobilitySafeRadius = atof(wheelControllerParameter.GetValue("SafeRadius").c_str());
			}
		}
	}
	else {
		// 모바일 컴포넌트의 프로파일중 로봇 반경 정보를 못가져오면 전역맵의 장애물 확장시 문제가 발생하므로
		// 기본 값을 임의로 넣음.
		mobilitySafeRadius = 0.4;
	}

	if (ptrLaserScannerService) {
		laserScannerParameter = ptrLaserScannerService->GetParameter();
		if (ptrLaserScannerService->GetError() == 0) {
#ifdef USE_GUI
			if (laserScannerParameter.FindName("X")) {
				laserScannerPos.x = atof(laserScannerParameter.GetValue("X").c_str());
			}
			if (laserScannerParameter.FindName("Y")) {
				laserScannerPos.y = atof(laserScannerParameter.GetValue("Y").c_str());
			}
			if (laserScannerParameter.FindName("Yaw")) {
				laserScannerPos.theta = DEG2RAD(atof(laserScannerParameter.GetValue("Yaw").c_str()));
			}
			if (laserScannerParameter.FindName("StartAngle")) {
				laserScannerStartAngle = DEG2RAD(atof(laserScannerParameter.GetValue("StartAngle").c_str()));
			}
			if (laserScannerParameter.FindName("EndAngle")) {
				laserScannerEndAngle = DEG2RAD(atof(laserScannerParameter.GetValue("EndAngle").c_str()));
			}
#endif
			double startStep, endStep, deltaStep;
			if (laserScannerParameter.FindName("StartStep")) {
				startStep = atoi(laserScannerParameter.GetValue("StartStep").c_str());
			}
			if (laserScannerParameter.FindName("EndStep")) {
				endStep = atoi(laserScannerParameter.GetValue("EndStep").c_str());
			}
			if (laserScannerParameter.FindName("DeltaStep")) {
				deltaStep = atoi(laserScannerParameter.GetValue("DeltaStep").c_str());
			}
			laserScannerCount = (int)((endStep - startStep) / deltaStep) + 1;
			laserData.resize (laserScannerCount);
		}
	}

#ifdef USE_GUI
	if (ptrGlobalMapService) {
		gridBasedGlobalMapParameter = ptrGlobalMapService->GetParameter();
		if (gridBasedGlobalMapParameter.FindName("MapFileName")) {
			mapFile = gridBasedGlobalMapParameter.GetValue("MapFileName");
		}
	}
#endif

#ifdef	WIN32
	AfxBeginThread(NavigationDlgThreadProc, this);
#endif

	return OPROS_SUCCESS;
}
	
ReturnType KITECH_NavigationComp::onStop()
{
#ifdef	WIN32
	if(navigationDlg != NULL) {
		::PostMessage(navigationDlg->m_hWnd, 0, 0, 0);
	}
#endif
	return OPROS_SUCCESS;
}

ReturnType KITECH_NavigationComp::onReset()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_NavigationComp::onError()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_NavigationComp::onRecover()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_NavigationComp::onDestroy()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_NavigationComp::onEvent(Event *evt)
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_NavigationComp::onExecute()
{
	DoTask ();

	return OPROS_SUCCESS;
}
	
ReturnType KITECH_NavigationComp::onUpdated()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_NavigationComp::onPeriodChanged()
{
	// user code here
	return OPROS_SUCCESS;
}

bool KITECH_NavigationComp::SetParameter(Property parameter)
{
	this->parameter = parameter;
	return true;
}

Property KITECH_NavigationComp::GetParameter()
{
	return parameter;
}

int KITECH_NavigationComp::GetError()
{
	return error;
}

void KITECH_NavigationComp::SetPosition(ObjectLocation position)
{
	lock.Lock();

	currentPosition = position;

	if (ptrWheelControllerService) {
		ptrWheelControllerService->SetPosition(currentPosition);
	}

	if (ptrLocalizationService) {
		ptrLocalizationService->SetPosition(currentPosition);
	}

	if (ptrObstacleAvoidanceService) {
		ptrObstacleAvoidanceService->SetPosition(currentPosition);
	}

	lock.Unlock();
}

ObjectLocation KITECH_NavigationComp::GetPosition()
{
	return currentPosition;
}

bool KITECH_NavigationComp::NavigationTo(ObjectLocation targetPosition)
{
	bool ret;

	PrintMessage("KITECH_NavigationComp::NavigationTo(%.3lf, %.3lf, %.3lf)\n", targetPosition.x, targetPosition.y, targetPosition.theta);

	lock.Lock();
	this->targetPosition = targetPosition;

	if (ptrPathPlanningService) {
		path = ptrPathPlanningService->FindPath(currentPosition, targetPosition);
	}
	
	if (1 < path.size()) {
		//path.pop_front();
		path.erase (path.begin());
		subTargetPosition = *path.begin();

		navigationStep = NS_NAVIGATION_TO;
		ret = true;
	}
	else {
		ret = false;
	}

	lock.Unlock();
	return ret;
}

bool KITECH_NavigationComp::Move(double distance)
{
	bool ret = false;

	PrintMessage ("KITECH_NavigationComp::Move(%.3lf)\n", distance);
	if (ptrWheelControllerService) {
		ret = ptrWheelControllerService->MoveWheel(distance);
	}

	return ret;
}

bool KITECH_NavigationComp::Rotate(double degree)
{
	bool ret = false;

	PrintMessage ("KITECH_NavigationComp::Rotate(%.3lf)\n", degree);
	if (ptrWheelControllerService) {
		ret = ptrWheelControllerService->RotateWheel(degree);
	}

	return ret;
}

void KITECH_NavigationComp::AbortNavigation()
{
	PrintMessage ("KITECH_NavigationComp::AbortNavigation()\n");
	navigationStep = NS_STOP;
}

bool KITECH_NavigationComp::IsNavigationOngoing()
{
	return (NS_IDLE < navigationStep ? true : false);
}

/*
	<환경 조건>
	1. Tetra 로봇 플렛폼
	2. Intel Core2Duo 2.1GHz
	3. 950 x 850 크기의 map
	4. 65 point의 레이저 스캐너

	<실험>
	1. DoTask() 수행 속도 측정
		16ms ~ 78ms(정지)
		31ms ~ 110ms(주행)

	2. WheelControllerComp의 GetPosition() 수행 속도 측정
		0ms

	3. WheelControllerComp의 DriveWheel() 수행 속도 측정
		0ms ~ 16ms

	4. GetLaserScannerData() 수행 속도 측정
		0ms ~ 62ms

	5. LocalizationComp의 Predict() 수행 속도 측정
		0ms

	6. LocalizationComp의 Update() 수행 속도 측정
		15ms ~ 32ms

	7. ObstacleAvoidanceComp의 Avoid() 수행 속도 측정
		0ms ~ 16ms
*/
void KITECH_NavigationComp::DoTask ()
{
	lock.Lock ();

	//printf ("KITECH_NavigationComp::DoTask ()\n");

	ObjectLocation wheelPosition;
	if (ptrWheelControllerService) {
		wheelPosition = ptrWheelControllerService->GetPosition();
	}

	if (ptrLaserScannerService) {
		laserData = ptrLaserScannerService->GetLaserScannerData();
	}

	if (ptrLocalizationService) {
		ObjectLocation position = ptrLocalizationService->Localize ();
		if (0 == ptrLocalizationService->GetError ()) {
			currentPosition = position;
		}
		else {
			currentPosition = wheelPosition;
		}
	}
	else {
		currentPosition = wheelPosition;
	}

	switch (navigationStep) {
		case NS_IDLE:
			break;
		case NS_NAVIGATION_TO: {
			WheelControlVelocity velocity = ptrObstacleAvoidanceService->Avoid(currentPosition, subTargetPosition);
			double remainDistance = subTargetPosition.Distance (currentPosition);
			ptrWheelControllerService->DriveWheel(velocity);
			if (remainDistance < mobilitySafeRadius * 1.5) {
				if (1 < path.size()) {
					//path.pop_front();
					path.erase (path.begin());
					subTargetPosition = *path.begin();
				}
				else {
					++navigationStep;
				}
			}
			break;
		}
		case NS_NAVIGATION_TO+1: {
			WheelControlVelocity velocity = ptrObstacleAvoidanceService->Avoid(currentPosition, subTargetPosition);
			double remainDistance = subTargetPosition.Distance (currentPosition);
			ptrWheelControllerService->DriveWheel(velocity);
			if (remainDistance < mobilitySafeRadius * 0.2) {
				navigationStep = NS_TURN;
				PrintMessage("Navigation NS_TURN\n");
			}
			break;
		 }
		case NS_TURN: {
			double remain_angle = DeltaRad(targetPosition.theta, currentPosition.theta);
			remain_angle = bound(2*remain_angle, -DEG2RAD(45), DEG2RAD(45));
			PrintMessage("Navigation NS_TURN %.3lf %.3lf %.3lf\n", RAD2DEG(targetPosition.theta), RAD2DEG(currentPosition.theta), RAD2DEG(remain_angle));
			if (RAD2DEG(fabs(remain_angle)) < 5.) {
				navigationStep = NS_STOP;
				PrintMessage("Navigation NS_STOP\n");
			}
			else {
				WheelControlVelocity velocity;
				velocity.forward = 0.;
				velocity.angular = remain_angle;
				ptrWheelControllerService->DriveWheel(velocity);
			}
			break;
		}
		case NS_STOP:
			ptrWheelControllerService->StopWheel();
			navigationStep = NS_IDLE;
			break;
		default:
			break;
	}

	lock.Unlock ();
}

bool KITECH_NavigationComp::LoadProperty ()
{
	if (parameter.FindName ("StartPositionX") == false) {
		PrintMessage ("ERROR -> Can not found StartPositionX parameter\n");
		return false;
	}
	currentPosition.x = atof(parameter.GetValue("StartPositionX").c_str());
	PrintMessage ("<KITECH_NavigationComp Parameter> StartPositionX : %.3lf\n", currentPosition.x);

	if (parameter.FindName ("StartPositionY") == false) {
		PrintMessage ("ERROR -> Can not found StartPositionY parameter\n");
		return false;
	}
	currentPosition.y = atof(parameter.GetValue("StartPositionY").c_str());
	PrintMessage ("<KITECH_NavigationComp Parameter> StartPositionY : %.3lf\n", currentPosition.y);

	if (parameter.FindName ("StartPositionTheta") == false) {
		PrintMessage ("ERROR -> Can not found StartPositionTheta parameter\n");
		return false;
	}
	currentPosition.theta = DEG2RAD(atof(parameter.GetValue("StartPositionTheta").c_str()));
	PrintMessage ("<KITECH_NavigationComp Parameter> StartPositionTheta : %.3lf\n", RAD2DEG(currentPosition.theta));

	return true;
}

#ifdef USE_GUI
vector<ObjectLocation> KITECH_NavigationComp::FindPath(ObjectLocation startPos, ObjectLocation endPos)
{
	if (ptrPathPlanningService) {
		path = ptrPathPlanningService->FindPath(startPos, endPos);
	}
	//PrintMessage ("KITECH_NavigationComp::FindPath (%.3lf %.3lf, %.3lf %.3lf)\n", startPos.x, startPos.y, endPos.x, endPos.y);
	//for (int i = 0; i < (int)path.size (); i++) {
	//	PrintMessage ("%.3lf  %.3lf\n", path[i].x, path[i].y);
	//}
	//PrintMessage ("\n");

	return path;
}
#endif

#ifdef MAKE_COMPONENT_DLL
#ifdef WIN32
extern "C"
{
__declspec(dllexport) Component *getComponent();
__declspec(dllexport) void releaseComponent(Component *pcom);
}
Component *getComponent()
{
	return new KITECH_NavigationComp();
}

void releaseComponent(Component *com)
{
	delete com;
}

UINT NavigationDlgThreadProc(LPVOID pParam)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());	

	KITECH_NavigationComp *pcom = (KITECH_NavigationComp *)pParam;
	CNavigationDlg dlg(::AfxGetMainWnd());

	//dlg.comp = pcom;
	pcom->navigationDlg =  &dlg;

	dlg.DoModal();
	pcom->navigationDlg = NULL;

	return 0;   // thread completed successfully
}


#else
extern "C"
{
	Component *getComponent();
	void releaseComponent(IComponent *com);
}
Component *getComponent()
{
	return new KITECH_NavigationComp();
}

void releaseComponent(Component *com)
{
	delete com;
}
#endif
#endif