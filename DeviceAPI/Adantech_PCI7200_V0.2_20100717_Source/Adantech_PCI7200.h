#pragma once

#include "DigitalIO.h"

class Adantech_PCI7200 : public DigitalIO
{
public:
	Adantech_PCI7200(void);
	virtual ~Adantech_PCI7200(void);

public:
	int Initialize(Property parameter);
	int Finalize(void);
	int Enable(void);
	int Disable(void);
	int SetParameter(Property parameter);
	int GetParameter(Property &parameter);
	int SetDigitalOutputData(vector<bool> digitalOutputData);
	int GetDigitalInputData(vector<bool> &digitalInputData);

private:
	Property parameter;

	short _handle;
	int _channel;
	int _inputPortCount;
	int _outputPortCount;
	
	int Adantech_PCI7200_WritePort(unsigned long data);
	int Adantech_PCI7200_ReadPort(unsigned long *data);
	void PCI7200_PrintErrorMessage(short errorCode);
};
