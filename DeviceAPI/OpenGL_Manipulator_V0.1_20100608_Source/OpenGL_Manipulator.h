#pragma once

#include "Manipulator.h"

/*	이 컴포넌트를 동작시키기 위해서는 ManipulatorComp 표준 프로파일 이외에 아래와 같은 정보가 추가되어야 한다.
	<property name="JointCount" type="int">8</property>
    
    <property name="JointType0" type="int">1</property>
    <property name="JointAxis0" type="int">2</property>
    <property name="X0" type="double">0.0</property>
    <property name="Y0" type="double">0.0</property>
    <property name="Z0" type="double">0.3</property>
    <property name="Phi0" type="double">0.0</property>
    <property name="Theta0" type="double">0.0</property>
    <property name="Psi0" type="double">0.0</property>

    <property name="JointType1" type="int">1</property>
    <property name="JointAxis1" type="int">1</property>
    <property name="X1" type="double">0.0</property>
    <property name="Y1" type="double">0.0</property>
    <property name="Z1" type="double">0.3</property>
    <property name="Phi1" type="double">0.0</property>
    <property name="Theta1" type="double">0.0</property>
    <property name="Psi1" type="double">0.0</property>

    <property name="JointType2" type="int">1</property>
    <property name="JointAxis2" type="int">0</property>
    <property name="X2" type="double">0.0</property>
    <property name="Y2" type="double">0.0</property>
    <property name="Z2" type="double">0.3</property>
    <property name="Phi2" type="double">0.0</property>
    <property name="Theta2" type="double">0.0</property>
    <property name="Psi2" type="double">0.0</property>

    <property name="JointType3" type="int">1</property>
    <property name="JointAxis3" type="int">1</property>
    <property name="X3" type="double">0.0</property>
    <property name="Y3" type="double">0.0</property>
    <property name="Z3" type="double">0.3</property>
    <property name="Phi3" type="double">0.0</property>
    <property name="Theta3" type="double">0.0</property>
    <property name="Psi3" type="double">0.0</property>

    <property name="JointType4" type="int">1</property>
    <property name="JointAxis4" type="int">0</property>
    <property name="X4" type="double">0.0</property>
    <property name="Y4" type="double">0.0</property>
    <property name="Z4" type="double">0.3</property>
    <property name="Phi4" type="double">0.0</property>
    <property name="Theta4" type="double">0.0</property>
    <property name="Psi4" type="double">0.0</property>

    <property name="JointType5" type="int">1</property>
    <property name="JointAxis5" type="int">1</property>
    <property name="X5" type="double">0.0</property>
    <property name="Y5" type="double">0.0</property>
    <property name="Z5" type="double">0.3</property>
    <property name="Phi5" type="double">0.0</property>
    <property name="Theta5" type="double">0.0</property>
    <property name="Psi5" type="double">0.0</property>

    <property name="JointType6" type="int">1</property>
    <property name="JointAxis6" type="int">0</property>
    <property name="X6" type="double">0.0</property>
    <property name="Y6" type="double">0.0</property>
    <property name="Z6" type="double">0.3</property>
    <property name="Phi6" type="double">0.0</property>
    <property name="Theta6" type="double">0.0</property>
    <property name="Psi6" type="double">0.0</property>

    <property name="JointType7" type="int">1</property>
    <property name="JointAxis7" type="int">1</property>
    <property name="X7" type="double">0.0</property>
    <property name="Y7" type="double">0.0</property>
    <property name="Z7" type="double">0.3</property>
    <property name="Phi7" type="double">0.0</property>
    <property name="Theta7" type="double">0.0</property>
    <property name="Psi7" type="double">0.0</property>
*/

class OpenGL_Manipulator : public Manipulator
{
public:
	OpenGL_Manipulator(void);
	virtual ~OpenGL_Manipulator(void);

public:
	int Initialize(Property parameter);
	int Finalize(void);
	int Enable(void);
	int Disable(void);
	int SetParameter(Property parameter);
	int GetParameter(Property &parameter);

	int StartHoming(void);
	int Stop(void);
	int EmergencyStop(void);
	int SetPower(vector<double> power, vector<unsigned long> time);
	int GetPower(vector<double> &power);
	int SetVelocity(vector<double> velocity, vector<unsigned long> time);
	int GetVelocity(vector<double> &velocity);
	int SetPosition(vector<double> position, vector<unsigned long> time);
	int GetPosition(vector<double> &position);

private:
#if defined(WIN32)
	HMODULE hOprosAPI;
#else
	void *hOprosAPI;
#endif
	Property parameter;
	vector<ManipulatorProfile> manipulatorProfile;
	int jointCount;
};
