#pragma once
#include "PDControl.h"

class PDControlWithGravity : public PDControl
{
public:
	PDControlWithGravity(double gravity[3], double dt = 0.01, double fsi = .0, double fvi = .0);
	virtual ~PDControlWithGravity(void);

public:
	virtual vector<double> RunController(void);
};
