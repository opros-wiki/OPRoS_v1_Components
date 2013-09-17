#pragma once

#include "I2C.h"
#include "UART.h"
#include "OprosLock.h"

#if defined(WIN32)
#include <Windows.h>
#else
#include <dlfcn.h>
#endif

class Devantech_USBtoI2C : public I2C
{
public:
	Devantech_USBtoI2C(void);
	virtual ~Devantech_USBtoI2C(void);

public:
	int Initialize(Property parameter);
	int Finalize(void);
	int Enable(void);
	int Disable(void);
	int SetParameter(Property parameter);
	int GetParameter(Property &parameter);
	int Lock(void);
	int Unlock(void);
	int Write(long address, unsigned char *data, int size);
	int Read(long address, unsigned char *data, int size);

private:
	Property parameter;

	UART *_uart;
	OprosLock _lock;

#if defined(WIN32)
	HMODULE hOprosAPI;
#else
	void *hOprosAPI;
#endif
	int InitializeUART(Property parameter);

	int _addressMode;

	int GetFirmwareVersion(void);

	int WriteUSBtoI2C(unsigned char addr, unsigned char *data, int size);
	int WriteUSBtoI2C(unsigned short addr, unsigned char *data, int size);
	int ReadUSBtoI2C(unsigned char addr, unsigned char *data, int size);
	int ReadUSBtoI2C(unsigned short addr, unsigned char *data, int size);
};
