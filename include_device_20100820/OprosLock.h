#ifndef	_LOCK_H_
#define	_LOCK_H_

#if defined(WIN32)
#include <windows.h>
#endif


class OprosLock
{
public:
	OprosLock(void)
	{
#if defined(WIN32)
		InitializeCriticalSection(&cs);
#endif
	};
	virtual ~OprosLock(void)
	{
#if defined(WIN32)
		DeleteCriticalSection(&cs);
#endif
	};

private:
#if defined(WIN32)
	CRITICAL_SECTION cs;
#endif

public:
	void Lock(void)
	{
#if defined(WIN32)
		EnterCriticalSection(&cs);
#endif
	};

	void Unlock(void)
	{
#if defined(WIN32)
		LeaveCriticalSection(&cs);
#endif
	};
};


#endif	//	_LOCK_H_