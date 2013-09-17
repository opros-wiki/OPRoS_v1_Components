#pragma once

#include "Kinematics.h"
#include <vector>

using namespace std;


class JointEx : public JointBasis {
public:
	// ���α׷� ���� �� ���Ǵ� ������
	dVector a;		// ȸ�� ���� ���ӵ�
	dVector p;		// ���� ��ǥ�迡�� ȸ�� ���� ��ġ

	JointEx () : a(3), p(3) { }
};

class JointInfo
{
public:
	JointInfo(void);
	virtual ~JointInfo(void);

	dVector GetDesired () { return _desired; }	// �������� ��ġ�� ��ȯ�Ѵ�.
	vector<JointEx *> &GetJointList () { return _jointList; }	// ����Ʈ ������ ����ִ� ����� ���´�. (�׸��� ���� ���)

// ����Ʈ ��� ���� �ϳ��� ����Ʈ�� ���Ѵ�.
	void AttachJoint (int type, int axis, double x, double y, double z, double phi, double theta, double psi, double radius);

private:
	dVector Error ();
	dMatrix Jacobian ();

	vector<JointEx *> _jointList;
	dVector _desired;
	dVector _current;
};
