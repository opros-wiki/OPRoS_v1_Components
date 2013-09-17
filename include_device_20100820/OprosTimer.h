#ifndef _OPROS_TIMER_H_
#define	_OPROS_TIMER_H_

#if defined(_OPROS_LINUX_)
#include <signal.h>
#include <sys/time.h>

#elif defined(WIN32)
#include <windows.h>

#endif



#if defined(_OPROS_LINUX_)
#define	OprosSleep(X)	usleep(X * 1000)
#elif defined(WIN32)
#define	OprosSleep(X)	Sleep(X)
#endif


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
#elif defined(WIN32)
	unsigned long m_startTime;
	unsigned long m_presentTime;

	LARGE_INTEGER m_freq;
	LARGE_INTEGER m_startFreqTime;
	LARGE_INTEGER m_endFreqTime;
	LARGE_INTEGER m_runFreqTime;

#endif

public:
	void StartTimeTick(void)
	{
#if defined(_OPROS_LINUX_)
		gettimeofday(&m_startTime, NULL);
#elif defined(WIN32)
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
#elif defined(WIN32)
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
#elif defined(WIN32)
		QueryPerformanceFrequency(&m_freq);
		QueryPerformanceCounter(&m_startFreqTime);

		m_runFreqTime = m_startFreqTime;
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
#elif defined(WIN32)
		double freqTime;

		QueryPerformanceCounter(&m_endFreqTime);

		freqTime = (double)(m_endFreqTime.QuadPart - m_runFreqTime.QuadPart) / m_freq.QuadPart * 1000.0;
		m_runFreqTime = m_endFreqTime;

		return (unsigned long)(freqTime * 1000.0);
#endif

	return 0;
	}
};

#endif	//	_OPROS_TIMER_H_