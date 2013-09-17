/*************************************************************

file: KITECH_VisibilityGraphPathPlanningComp.cpp
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
#include "PathPlanningServiceProvided.h"
#include "KITECH_VisibilityGraphPathPlanningComp.h"


struct sNode;

struct sRoute {
	double distance;
	sNode *connectedNode;
};

struct sNode {
	int x, y;
	int timeElasped;
	sNode *cameFrom;
	vector<sRoute> route;

	sNode (int _x, int _y) : x(_x), y(_y), timeElasped(0), cameFrom(NULL) { }
};

vector<sNode> convexNode;

//
// constructor declaration
//
KITECH_VisibilityGraphPathPlanningComp::KITECH_VisibilityGraphPathPlanningComp()
{
	error = 0;
	portSetup();
}

//
// constructor declaration (with name)
//
KITECH_VisibilityGraphPathPlanningComp::KITECH_VisibilityGraphPathPlanningComp(const std::string &name):Component(name)
{
	error = 0;
	portSetup();
}

//
// destructor declaration
//

KITECH_VisibilityGraphPathPlanningComp::~KITECH_VisibilityGraphPathPlanningComp()
{
}

void KITECH_VisibilityGraphPathPlanningComp::portSetup()
{
	// provided service port setup
	ProvidedServicePort *pa1 = new PathPlanningServiceProvided(this);
	addPort("PathPlanningService",pa1);

	// required service port setup
	ptrGlobalMapService = new GlobalMapServiceRequired();
	addPort ("GlobalMapService", ptrGlobalMapService);
}

// Call back Declaration
ReturnType KITECH_VisibilityGraphPathPlanningComp::onInitialize()
{
	PrintMessage ("KITECH_VisibilityGraphPathPlanningComp::onInitialize()\n");

	parameter.SetProperty(getPropertyMap());

	error = 0;

	return OPROS_SUCCESS;
}

ReturnType KITECH_VisibilityGraphPathPlanningComp::onStart()
{
	// user code here
	return OPROS_SUCCESS;
}
	
ReturnType KITECH_VisibilityGraphPathPlanningComp::onStop()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_VisibilityGraphPathPlanningComp::onReset()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_VisibilityGraphPathPlanningComp::onError()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_VisibilityGraphPathPlanningComp::onRecover()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_VisibilityGraphPathPlanningComp::onDestroy()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_VisibilityGraphPathPlanningComp::onEvent(Event *evt)
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_VisibilityGraphPathPlanningComp::onExecute()
{
	// user code here
	return OPROS_SUCCESS;
}
	
ReturnType KITECH_VisibilityGraphPathPlanningComp::onUpdated()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_VisibilityGraphPathPlanningComp::onPeriodChanged()
{
	// user code here
	return OPROS_SUCCESS;
}

bool KITECH_VisibilityGraphPathPlanningComp::SetParameter(Property parameter)
{
	this->parameter = parameter;
	return true;
}

Property KITECH_VisibilityGraphPathPlanningComp::GetParameter()
{
	error = 0;
	return parameter;
}

int KITECH_VisibilityGraphPathPlanningComp::GetError()
{
	return error;
}

/*
	<환경 조건>
	1. Tetra 로봇 플렛폼
	2. Intel Core2Duo 2.1GHz
	3. 950 x 850 크기의 map

	<실험>
	1. FindPath() 수행 속도 측정
		1156ms ~ 1172ms
*/
vector<ObjectLocation> KITECH_VisibilityGraphPathPlanningComp::FindPath(ObjectLocation startPosition, ObjectLocation endPosition)
{
	deque<ObjectLocation> path;
	vector<ObjectLocation> path2;

	ObjectLocation sp(startPosition);
	ObjectLocation ep(endPosition);

	convexNode.clear ();
	path.clear ();
	path2.clear ();
	
	error = 0;

	if (ptrGlobalMapService == NULL) {
		error = -1;
		return path2;
	}

	bool isIn = ptrGlobalMapService->IsIn (sp.x, sp.y);
	if (isIn) {
		unsigned char pixel = ptrGlobalMapService->GetPixel(sp.x, sp.y);
		if (10 <= pixel) {
			if (!FindNearestPoint(&sp)) goto EXIT_FAIL;
		}
	}
	
	isIn = ptrGlobalMapService->IsIn (ep.x, ep.y);
	if (isIn) {
		unsigned char pixel = ptrGlobalMapService->GetPixel(ep.x, ep.y);
		if (10 <= pixel) {
			if (!FindNearestPoint(&ep)) goto EXIT_FAIL;
		}
	}

	FindAllCorner (sp, ep);
	if (2 <= convexNode.size ()) {
		if (0 < FindAllPossibleLink ()) {
			if (SpreadToGoal (ep)) {
				TraceShortestPath (&path);
				// 끝점의 방향을 설정한다.
				path.at(0).theta = ep.theta;
				reverse (path.begin (), path.end ());

				int size = (int)path.size ();
				for (int i = 0; i < size; i++) {
					path2.push_back (*path.begin ());
					path.pop_front ();
				}

				return path2;
			}
		}
	}

EXIT_FAIL:
	path2.clear ();
	error = -1;
	return path2;
}

bool KITECH_VisibilityGraphPathPlanningComp::FindNearestPoint (ObjectLocation *point)
{
	int i, j;

	if (ptrGlobalMapService == NULL) {
		error = -1;
		return false;
	}

	double cellWidth = ptrGlobalMapService->GetMapCellWidth();

	for (i = 0; i < 100; i++) {
		for (j = 0; j < 16; j++) {
			double r  = i * cellWidth;
			double th = DEG2RAD (rand ());
			double dx = r * cos (th);
			double dy = r * sin (th);
			
			bool isIn = ptrGlobalMapService->IsIn(point->x + dx, point->y + dy);
			if (isIn) {
				unsigned char pixel = ptrGlobalMapService->GetPixel(point->x + dx, point->y + dy);
				if (pixel < 1) {
					point->x += dx;
					point->y += dy;
					return true;
				}
			}
		}
	}
	return false;
}

void KITECH_VisibilityGraphPathPlanningComp::FindAllCorner (const ObjectLocation &sp, const ObjectLocation &ep)
{
	if (ptrGlobalMapService == NULL) {
		error = -1;
		return;
	}

	int sx = ptrGlobalMapService->M2CUx(sp.x);
	int sy = ptrGlobalMapService->M2CUy(sp.y);
	int ex = ptrGlobalMapService->M2CUx(ep.x);
	int ey = ptrGlobalMapService->M2CUy(ep.y);

	sNode startNode (sx, sy);
	convexNode.push_back (sNode (sx, sy));
	convexNode.push_back (sNode (ex, ey));

	int rx, ry;
	int width = ptrGlobalMapService->GetMapWidth();
	int height = ptrGlobalMapService->GetMapHeight();
	unsigned char obstaclePixelValue = 10;
	for (ry = 1; ry < height-2; ry++) {
		for (rx = 1; rx < width-2; rx++) {
			unsigned char pixel00 = ptrGlobalMapService->GetPixelCell(rx  , ry);
			unsigned char pixel10 = ptrGlobalMapService->GetPixelCell(rx+1, ry);
			unsigned char pixel01 = ptrGlobalMapService->GetPixelCell(rx  , ry+1);
			unsigned char pixel11 = ptrGlobalMapService->GetPixelCell(rx+1, ry+1);
			if (
				!(obstaclePixelValue <= pixel00) && 
				!(obstaclePixelValue <= pixel10) && 
				!(obstaclePixelValue <= pixel01) && 
				(obstaclePixelValue <= pixel11)) {
					convexNode.push_back (sNode (rx, ry));
			}
			else if (
				!(obstaclePixelValue <= pixel00) && 
				!(obstaclePixelValue <= pixel10) && 
				(obstaclePixelValue <= pixel01) && 
				!(obstaclePixelValue <= pixel11)) {
					convexNode.push_back (sNode (rx+1, ry));
			}
			else if (
				!(obstaclePixelValue <= pixel00) && 
				(obstaclePixelValue <= pixel10) && 
				!(obstaclePixelValue <= pixel01) && 
				!(obstaclePixelValue <= pixel11)) {
					convexNode.push_back (sNode (rx, ry+1));
			}
			else if (
				(obstaclePixelValue <= pixel00) && 
				!(obstaclePixelValue <= pixel10) && 
				!(obstaclePixelValue <= pixel01) && 
				!(obstaclePixelValue <= pixel11)) {
					convexNode.push_back (sNode (rx+1, ry+1));
			}
		}
	}
}

int KITECH_VisibilityGraphPathPlanningComp::FindAllPossibleLink ()
{
	// 이동가능한 경로 찾음

	if (ptrGlobalMapService == NULL) {
		error = -1;
		return 0;
	}

	int n = 0, nn = 0;
	vector<sNode>::iterator i1, i2;
	for (i1=convexNode.begin (); i1!=convexNode.end()-1; i1++) {
		for (i2=i1+1; i2!=convexNode.end(); i2++) {
			int i1_x = i1->x;
			int i1_y = i1->y;
			int i2_x = i2->x;
			int i2_y = i2->y;
			bool isIntersectCell = ptrGlobalMapService->IsIntersectCell(i1_x, i1_y, i2_x, i2_y, 1);
			if (!isIntersectCell) {
				sRoute r;
				double x1 = ptrGlobalMapService->CU2Mx(i1_x);
				double y1 = ptrGlobalMapService->CU2My(i1_y);
				double x2 = ptrGlobalMapService->CU2Mx(i2_x);
				double y2 = ptrGlobalMapService->CU2My(i2_y);

				r.distance = Distance (x1, y1, x2, y2);

				r.connectedNode = &*i2;
				i1->route.push_back (r);

				r.connectedNode = &*i1;
				i2->route.push_back (r);

				n++;
			}
			else {
				nn++;
			}
		}
	}
	return n;
}

bool KITECH_VisibilityGraphPathPlanningComp::SpreadToGoal (const ObjectLocation &ep)
{
	if (ptrGlobalMapService == NULL) {
		error = -1;
		return false;
	}

	int eX = ptrGlobalMapService->M2CUx(ep.x);
	int eY = ptrGlobalMapService->M2CUy(ep.y);

	int t = 1;
	int find_goal = 0;
	vector<sNode *> m1, m2;
	vector<sNode *>::iterator _mi;
	sNode *i1;
	vector<sRoute>::iterator ir;

	i1 = &convexNode.at (0);
	i1->timeElasped = t;
	m1.push_back (i1);

	while (!m1.empty ()) {
		m2.reserve (100000);

		for (_mi=m1.begin (); _mi!=m1.end(); _mi++) {
			if (t < (*_mi)->timeElasped) {
				// 아직 계산할 시간이 안되었다.
				m2.push_back (*_mi);
			}
			else {
				if ((*_mi)->x==eX && (*_mi)->y==eY) {
					// find goal
					find_goal = 1;
				}

				for (ir=(*_mi)->route.begin(); ir!=(*_mi)->route.end(); ir++) {
					int timeElasped = t + 1 + (int)(ir->distance*40);
					if (ir->connectedNode->timeElasped == 0) {
						ir->connectedNode->timeElasped = timeElasped;
						ir->connectedNode->cameFrom = *_mi;
						m2.push_back (ir->connectedNode);
					}
					else if (ir->connectedNode->timeElasped > timeElasped) {
						ir->connectedNode->timeElasped = timeElasped;
						ir->connectedNode->cameFrom = *_mi;
						//m2.push_back (ir->connectedNode);
					}
				}
			}
		}
		m1.clear ();
		m1.swap (m2);
		t+=1;

		if (find_goal) {
			m1.clear ();
			m2.clear ();
			//log ("find goal");
			return true;
		}
	}
	m1.clear ();
	m2.clear ();
	//log ("find fail");
	return false;
}

void KITECH_VisibilityGraphPathPlanningComp::TraceShortestPath (deque<ObjectLocation> *path)
{
	sNode *cp = &convexNode.at(1);

	if (ptrGlobalMapService == NULL) {
		error = -1;
		return;
	}

	while (cp) {
		double x = ptrGlobalMapService->CU2Mx(cp->x);
		double y = ptrGlobalMapService->CU2My(cp->y);
		ObjectLocation p (x, y, 0);
		path->push_back (p);

		cp = cp->cameFrom;
	}
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
	return new KITECH_VisibilityGraphPathPlanningComp();
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
	return new KITECH_VisibilityGraphPathPlanningComp();
}

void releaseComponent(Component *com)
{
	delete com;
}
#endif
#endif

