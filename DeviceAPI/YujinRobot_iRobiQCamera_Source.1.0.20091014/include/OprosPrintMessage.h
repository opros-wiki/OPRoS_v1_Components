#ifndef	_OPROS_PRINT_MESSAGE_H_
#define	_OPROS_PRINT_MESSAGE_H_

#pragma warning(disable : 4996)

#include <stdarg.h>
#include <iostream>

#define	_OPROS_DEBUG_

namespace OPRoS
{


void PrintMessage(const char *format, ...)
#if defined(_OPROS_DEBUG_)
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

};

#endif	//	_OPROS_PRINT_MESSAGE_H_