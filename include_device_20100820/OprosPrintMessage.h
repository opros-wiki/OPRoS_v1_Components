#ifndef	_OPROS_PRINT_MESSAGE_H_
#define	_OPROS_PRINT_MESSAGE_H_

#if defined(WIN32)
#pragma warning(disable : 4996)
#endif

#include <stdarg.h>
#include <stdio.h>

inline void PrintMessage(const char *format, ...)
#if defined(_OPROS_DEBUG_) || defined(_DEBUG) || defined(NDEBUG)
{
	int n = 0;
    va_list arg_list;
	char log_text[1024+1];

	va_start (arg_list,format);
	n += vsnprintf (log_text+n, 1024-n, format, arg_list);
	va_end (arg_list);
	log_text[1024] = '\0';

	printf("%s", log_text);
}
#else
{
}
#endif

#endif	//	_OPROS_PRINT_MESSAGE_H_