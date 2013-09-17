#ifndef	_OPROS_LOCK_H_
#define	_OPROS_LOCK_H_

#include <windows.h>

class OprosLock
{
public:
	OprosLock(void)
	{
		InitializeCriticalSection(&cs);
	}
	
	~OprosLock(void)
	{
		DeleteCriticalSection(&cs);
	}

private:
	CRITICAL_SECTION cs;

public:
	void lock(void)
	{
		EnterCriticalSection(&cs);
	}

	void unlock(void)
	{
		LeaveCriticalSection(&cs);
	}
};

#endif	//	_OPROS_LOCK_H_