/*************************************************************

file: KITECH_AStarPathPlanningComp.cpp
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

#include "PathPlanningServiceProvided.h"
#include "KITECH_AStarPathPlanningComp.h"

//
// constructor declaration
//
KITECH_AStarPathPlanningComp::KITECH_AStarPathPlanningComp()
{
	scalefactor = 25;
	portSetup();
}

//
// constructor declaration (with name)
//
KITECH_AStarPathPlanningComp::KITECH_AStarPathPlanningComp(const std::string &name):Component(name)
{
	scalefactor = 25;
	portSetup();
}

//
// destructor declaration
//
KITECH_AStarPathPlanningComp::~KITECH_AStarPathPlanningComp()
{
	
}

void KITECH_AStarPathPlanningComp::portSetup()
{
	// provided service port setup
	ProvidedServicePort *pa1 = new PathPlanningServiceProvided(this);
	addPort("PathPlanningService",pa1);

	// required service port setup
	ptrGlobalMapService = new GlobalMapServiceRequired();
	addPort ("GlobalMapService", ptrGlobalMapService);
}

// Call back Declaration
ReturnType KITECH_AStarPathPlanningComp::onInitialize()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_AStarPathPlanningComp::onStart()
{
	// user code here
	return OPROS_SUCCESS;
}
	
ReturnType KITECH_AStarPathPlanningComp::onStop()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_AStarPathPlanningComp::onReset()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_AStarPathPlanningComp::onError()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_AStarPathPlanningComp::onRecover()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_AStarPathPlanningComp::onDestroy()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_AStarPathPlanningComp::onEvent(Event *evt)
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_AStarPathPlanningComp::onExecute()
{
	// user code here
	return OPROS_SUCCESS;
}
	
ReturnType KITECH_AStarPathPlanningComp::onUpdated()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_AStarPathPlanningComp::onPeriodChanged()
{
	// user code here
	return OPROS_SUCCESS;
}

bool KITECH_AStarPathPlanningComp::SetParameter(Property parameter)
{
	this->parameter = parameter;
	return true;
}

Property KITECH_AStarPathPlanningComp::GetParameter()
{
	return parameter;
}

int KITECH_AStarPathPlanningComp::GetError()
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
		0ms ~ 16ms
*/
vector<ObjectLocation> KITECH_AStarPathPlanningComp::FindPath(ObjectLocation startPosition,ObjectLocation endPosition)
{
	vector<ObjectLocation> path;
	node nbest;
	node temp;
	point start, goal;

	path.clear ();
	if (ptrGlobalMapService == NULL) {
		//error = 1;	
		return path;
	}

	ObjectLocation sp(startPosition);
	ObjectLocation ep(endPosition);
	bool isIn = ptrGlobalMapService->IsIn (sp.x, sp.y);
	if (isIn) {
		unsigned char pixel = ptrGlobalMapService->GetPixel(sp.x, sp.y);
		if (10 <= pixel) {
			if (!FindNearestPoint(&sp)) {
				//error = 1;
				return path;
			}
		}
	}

	isIn = ptrGlobalMapService->IsIn (ep.x, ep.y);
	if (isIn) {
		unsigned char pixel = ptrGlobalMapService->GetPixel(ep.x, ep.y);
		if (10 <= pixel) {
			if (!FindNearestPoint(&ep)) {
				//error = 1;
				return path;
			}
		}
	}

	openList.clear();
	closeList.clear();

	start.x = ptrGlobalMapService->M2CUx(sp.x);
	start.y = ptrGlobalMapService->M2CUy(sp.y);
	goal.x = ptrGlobalMapService->M2CUx(ep.x);
	goal.y = ptrGlobalMapService->M2CUy(ep.y);

	
	int mapWidth = ptrGlobalMapService->GetMapWidth();
	int mapHeight = ptrGlobalMapService->GetMapHeight();

	if (start.x < (0+scalefactor) || (mapWidth-scalefactor) <= start.x || start.y < (0+scalefactor) || (mapHeight-scalefactor) <= start.y ||
		goal.x < (0+scalefactor) || (mapWidth-scalefactor) <= goal.x || goal.y < (0+scalefactor) || (mapHeight-scalefactor) <= goal.y) {
		//error = 1;
		return path;
	}

	node snode;
	{
		snode.back = start;
		snode.itself = start;
		snode.g = 0;
		snode.h = CalcDistance (start, goal);
		snode.f = snode.g + snode.h;
		openList.push (&snode);
	}

	do {
		openList.pop(&nbest);
		closeList.push(&nbest);

		if( abs (goal.x-nbest.itself.x) < scalefactor
			&& abs (goal.y-nbest.itself.y) < scalefactor) {
				temp.itself = goal;
				temp.g = nbest.g + CalcDistance(temp.itself, nbest.itself);
				temp.h = CalcDistance(temp.itself, goal);
				temp.f = temp.g + temp.h;
				temp.back = nbest.itself;
				closeList.push (&temp);
				break;
		}

		for(int y = nbest.itself.y-scalefactor; y <= nbest.itself.y+scalefactor; y += scalefactor) {
			for(int x = nbest.itself.x-scalefactor; x <= nbest.itself.x+scalefactor; x += scalefactor) {
				if (x < 0 || mapWidth < x || y < 0 || mapHeight < y) continue;

				if (ptrGlobalMapService->GetPixelCell(x, y) == 0) {
					temp.itself.x = x;
					temp.itself.y = y;

					if(!closeList.find (&temp)) {
						if(!openList.find(&temp)) {
							temp.g = nbest.g + CalcDistance (temp.itself, nbest.itself);
							temp.h = CalcDistance (temp.itself, goal);
							temp.f = temp.g + temp.h;
							temp.back = nbest.itself;
							openList.push (&temp);
						}
						else if((nbest.g + CalcDistance(nbest.itself, temp.itself)) < temp.g) {
							temp.g = nbest.g + CalcDistance(temp.itself, nbest.itself);
							temp.h = CalcDistance(temp.itself, goal);
							temp.f = temp.g + temp.h;
							temp.back = nbest.itself;
							openList.modifyNodeData (&temp);
						}
						else {
						}
					}
				}
			}
		}
	} while(openList.size());

	stack extractPath;
	ExtractPath(&extractPath);

	//path.clear ();
	while(extractPath.size ()) {
		node data;
		ObjectLocation _tmpoint;
		extractPath.pop(&data);
		_tmpoint.x = ptrGlobalMapService->CU2Mx (data.itself.x);
		_tmpoint.y = ptrGlobalMapService->CU2My (data.itself.y);
		path.push_back (_tmpoint);
	}

	return path;
}

double KITECH_AStarPathPlanningComp::CalcDistance(point p1, point p2)
{
	double dx, dy;
	double ret;

	dx=p1.x-p2.x;
	dy=p1.y-p2.y;

	ret=sqrt(dx*dx+dy*dy);

	return ret;
}

void KITECH_AStarPathPlanningComp::ExtractPath(stack *path)
{
	node cur, next;

	path->clear ();
	closeList.pop (&cur);
	path->push (&cur);

	do{
		closeList.pop (&next);
		if((next.itself.x == cur.back.x) && (next.itself.y == cur.back.y)) {
			path->push (&next);
			cur = next;
		}
	}while(closeList.size ());	
}

bool KITECH_AStarPathPlanningComp::FindNearestPoint (ObjectLocation *point)
{
	if (ptrGlobalMapService == NULL) return false;

	int i, j;
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

#ifdef MAKE_COMPONENT_DLL
#ifdef WIN32
extern "C"
{
__declspec(dllexport) Component *getComponent();
__declspec(dllexport) void releaseComponent(Component *pcom);
}

Component *getComponent()
{
	return new KITECH_AStarPathPlanningComp();
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
	return new KITECH_AStarPathPlanningComp();
}

void releaseComponent(Component *com)
{
	delete com;
}
#endif
#endif

