/*************************************************************

 file: OpenGL_Manipulator.cpp
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
#include "stdafx.h"
#include "OpenGL_Manipulator.h"

#include "OprosPrintMessage.h"
#include "ManipulatorDlg.h"

typedef	struct _JOINT_INFO_ {
	int jointType;
	int jointAxis;
	double x;
	double y;
	double z;
	double phi;
	double theta;
	double psi;
} JOINT_INFO;

ManipulatorDlg *manipulatorDlg = NULL;

vector<JOINT_INFO> jointInfo;

UINT OpenGL_ManipulatorDlgThreadProc(LPVOID pParam);

 OpenGL_Manipulator::OpenGL_Manipulator(void)
{
	hOprosAPI = NULL;
}

OpenGL_Manipulator::~OpenGL_Manipulator(void)
{
	Finalize();
}

int OpenGL_Manipulator::Initialize(Property parameter)
{
	if(SetParameter(parameter) != API_SUCCESS) {
		PrintMessage("ERROR : OpenGL_Manipulator::Initialize() -> Can't setup a parameter\n");
		return API_ERROR;
	}

	return API_SUCCESS;
}

int OpenGL_Manipulator::Finalize(void)
{
	Disable();
	
	return API_SUCCESS;
}

int OpenGL_Manipulator::Enable(void)
{
	if(manipulatorDlg != NULL) {
		delete manipulatorDlg;
		manipulatorDlg = NULL;
	}

	AfxBeginThread(OpenGL_ManipulatorDlgThreadProc, this);
	Sleep(100);

	return API_SUCCESS;
}

int OpenGL_Manipulator::Disable(void)
{
	int ret = API_SUCCESS;

	if(manipulatorDlg != NULL) {
		::PostMessage(manipulatorDlg->m_hWnd, 0, 0, 0);
	}
	
	return ret;
}

int OpenGL_Manipulator::SetParameter(Property parameter)
{
	if(parameter.FindName("Size") == false)				return API_ERROR;
	int size = atoi(parameter.GetValue("Size").c_str());

	char name[128];
	ManipulatorProfile tempProfile;
	manipulatorProfile.clear();
	for(int i = 0; i < size; i++) {
		sprintf(name, "PowerUnit%d", i);
		if(parameter.FindName(string(name)) == false)			goto OPEN_GL_MAINPULATOR_SET_PARAMETER_ERROR;
		tempProfile.powerUnit = atoi(parameter.GetValue(name).c_str());

		sprintf(name, "MaximumPower%d", i);
		if(parameter.FindName(string(name)) == false)			goto OPEN_GL_MAINPULATOR_SET_PARAMETER_ERROR;
		tempProfile.maximumPower = atof(parameter.GetValue(name).c_str());

		sprintf(name, "MaximumVelocity%d", i);
		if(parameter.FindName(string(name)) == false)			goto OPEN_GL_MAINPULATOR_SET_PARAMETER_ERROR;
		tempProfile.maximumVelocity = atof(parameter.GetValue(name).c_str());

		sprintf(name, "Acceleration%d", i);
		if(parameter.FindName(string(name)) == false)			goto OPEN_GL_MAINPULATOR_SET_PARAMETER_ERROR;
		tempProfile.acceleration = atof(parameter.GetValue(name).c_str());

		sprintf(name, "MinimumPositionLimit%d", i);
		if(parameter.FindName(string(name)) == false)			goto OPEN_GL_MAINPULATOR_SET_PARAMETER_ERROR;
		tempProfile.minimumPositionLimit = atof(parameter.GetValue(name).c_str());

		sprintf(name, "MaximumPositionLimit%d", i);
		if(parameter.FindName(string(name)) == false)			goto OPEN_GL_MAINPULATOR_SET_PARAMETER_ERROR;
		tempProfile.maximumPositionLimit = atof(parameter.GetValue(name).c_str());

		manipulatorProfile.push_back(tempProfile);
	}

	//	For OpenGL
	if(parameter.FindName("JointCount") == false)				return API_ERROR;
	jointCount = atoi(parameter.GetValue("JointCount").c_str());

	if(jointCount <= 0) 	return API_ERROR;

	
	JOINT_INFO tmpJointInfo;
	jointInfo.clear();
	for(int i = 0; i < jointCount; i++) {
		sprintf(name, "JointType%d", i);
		if(parameter.FindName(name) == false)		goto OPEN_GL_MAINPULATOR_SET_PARAMETER_ERROR;
		else										tmpJointInfo.jointType = atoi(parameter.GetValue(name).c_str());

		sprintf(name, "JointAxis%d", i);
		if(parameter.FindName(name) == false)		goto OPEN_GL_MAINPULATOR_SET_PARAMETER_ERROR;
		else										tmpJointInfo.jointAxis = atoi(parameter.GetValue(name).c_str());

		sprintf(name, "X%d", i);
		if(parameter.FindName(name) == false)		goto OPEN_GL_MAINPULATOR_SET_PARAMETER_ERROR;
		else										tmpJointInfo.x = atof(parameter.GetValue(name).c_str());

		sprintf(name, "Y%d", i);
		if(parameter.FindName(name) == false)		goto OPEN_GL_MAINPULATOR_SET_PARAMETER_ERROR;
		else										tmpJointInfo.y = atof(parameter.GetValue(name).c_str());

		sprintf(name, "Z%d", i);
		if(parameter.FindName(name) == false)		goto OPEN_GL_MAINPULATOR_SET_PARAMETER_ERROR;
		else										tmpJointInfo.z = atof(parameter.GetValue(name).c_str());

		sprintf(name, "Phi%d", i);
		if(parameter.FindName(name) == false)		goto OPEN_GL_MAINPULATOR_SET_PARAMETER_ERROR;
		else										tmpJointInfo.phi = atof(parameter.GetValue(name).c_str());

		sprintf(name, "Theta%d", i);
		if(parameter.FindName(name) == false)		goto OPEN_GL_MAINPULATOR_SET_PARAMETER_ERROR;
		else										tmpJointInfo.theta = atof(parameter.GetValue(name).c_str());

		sprintf(name, "Psi%d", i);
		if(parameter.FindName(name) == false)		goto OPEN_GL_MAINPULATOR_SET_PARAMETER_ERROR;
		else										tmpJointInfo.psi = atof(parameter.GetValue(name).c_str());
		
		jointInfo.push_back(tmpJointInfo);
	}
	
	this->parameter = parameter;
	return API_SUCCESS;

OPEN_GL_MAINPULATOR_SET_PARAMETER_ERROR :
	manipulatorProfile.clear();
	jointInfo.clear();
	return API_ERROR;
}

int OpenGL_Manipulator::GetParameter(Property &parameter)
{
	parameter = this->parameter;

	return API_SUCCESS;
}

int OpenGL_Manipulator::StartHoming(void)
{
	return API_SUCCESS;
}

int OpenGL_Manipulator::Stop(void)
{
	return API_SUCCESS;
}

int OpenGL_Manipulator::EmergencyStop(void)
{
	return API_SUCCESS;
}

int OpenGL_Manipulator::SetPower(vector<double> power, vector<unsigned long> time)
{
	return API_NOT_SUPPORTED;
}

int OpenGL_Manipulator::GetPower(vector<double> &power)
{
	return API_NOT_SUPPORTED;
}

int OpenGL_Manipulator::SetVelocity(vector<double> velocity, vector<unsigned long> time)
{
	return API_NOT_SUPPORTED;
}

int OpenGL_Manipulator::GetVelocity(vector<double> &velocity)
{
	return API_NOT_SUPPORTED;
}

int OpenGL_Manipulator::SetPosition(vector<double> position, vector<unsigned long> time)
{
	if(manipulatorDlg == NULL) {
		return API_ERROR;
	}

	if(jointCount != (int)position.size() || manipulatorProfile.size() != position.size()) {
		return API_ERROR;
	}

	for(size_t i = 0; i < manipulatorProfile.size(); i++) {
		if(position[i] > manipulatorProfile[i].maximumPositionLimit || position[i] < manipulatorProfile[i].minimumPositionLimit) {
			return API_ERROR;
		}
	}
	
	if(manipulatorDlg->SetPosition(position) == false) {
		return API_ERROR;
	}

	return API_SUCCESS;
}

int OpenGL_Manipulator::GetPosition(vector<double> &position)
{
	if(manipulatorDlg == NULL) {
		return API_ERROR;
	}

	position = manipulatorDlg->GetPosition();

	return API_SUCCESS;
}

#if defined(WIN32)
extern "C"
{
__declspec(dllexport) OprosApi *GetAPI();
}

OprosApi *GetAPI()
{
	return new OpenGL_Manipulator();
}

UINT OpenGL_ManipulatorDlgThreadProc(LPVOID pParam)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());	

	ManipulatorDlg dlg(::AfxGetMainWnd());

	manipulatorDlg = &dlg;

	for(size_t i = 0; i < jointInfo.size(); i++) {
		dlg.AttachJoint(jointInfo[i].jointType, jointInfo[i].jointAxis, jointInfo[i].x, jointInfo[i].y, jointInfo[i].z, jointInfo[i].phi, jointInfo[i].theta, jointInfo[i].psi);
	}

	dlg.DoModal();
	
	manipulatorDlg = NULL;

	return 0;   // thread completed successfully
}

#endif

