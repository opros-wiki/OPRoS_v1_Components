#ifndef _OPROS_TIMER_H_
#define	_OPROS_TIMER_H_

#if defined(_OPROS_LINUX_)
#include <signal.h>
#include <sys/time.h>

#else
#include <windows.h>

#endif

extern void OprosSleep(unsigned long mSleep);
void OprosSleep(unsigned long mSleep)
{
#if defined(_OPROS_LINUX_)
	usleep(mSleep * 1000);
#else
	Sleep(mSleep);
#endif
}

class OprosTimer
{
public:
	OprosTimer(void) {}
	virtual ~OprosTimer(void) {}

private:
#if defined(_OPROS_LINUX_)
	 struct timeval m_startTime;
	 struct timeval m_presentTime;

	 struct timeval m_startMicroTime;
	 struct timeval m_presentMicroTime;
#else
	unsigned long m_startTime;
	unsigned long m_presentTime;

#endif

public:
	void StartTimeTick(void)
	{
#if defined(_OPROS_LINUX_)
		gettimeofday(&m_startTime, NULL);
#else	//	Windows
		m_startTime = GetTickCount();
		m_presentTime = 0;
#endif
	}

	unsigned long GetTimeTick(void)
	{
#if defined(_OPROS_LINUX_)
		unsigned long start_time;
		unsigned long end_time;
		gettimeofday(&m_presentTime, NULL);
	
		start_time = (m_startTime.tv_usec/1000) + (m_startTime.tv_sec*1000);
		end_time =(m_presentTime.tv_usec/1000) + (m_presentTime.tv_sec*1000);

		return (unsigned long)(end_time - start_time);
#else	//	Windows
		unsigned long lTmp = GetTickCount();
		m_presentTime += (lTmp - m_startTime);
		m_startTime = lTmp;

		return m_presentTime;
#endif

		return 0;
	}

	void StartTimeTickMicro(void)
	{
#if defined(_OPROS_LINUX_)
		gettimeofday(&m_startMicroTime, NULL);
#else	//	Windows
#endif
	}

	unsigned long GetTimeTickMicro(void)
	{
#if defined(_OPROS_LINUX_)
		unsigned long start_time;
		unsigned long end_time;
		gettimeofday(&m_presentMicroTime, NULL);
	
		start_time = (m_startMicroTime.tv_usec) + (m_startMicroTime.tv_sec*1000000);
		end_time =(m_presentMicroTime.tv_usec) + (m_presentMicroTime.tv_sec*1000000);

		return (unsigned long)(end_time - start_time);
#else	//	Windows
#endif

	return 0;
	}
};

#endif	//	_OPROS_TIMER_H_
