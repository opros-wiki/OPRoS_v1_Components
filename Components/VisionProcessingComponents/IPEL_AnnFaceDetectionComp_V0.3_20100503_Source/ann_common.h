// ann_common.h
// AnnFaceDetection 공통 헤더파일

#pragma once
#pragma warning(disable : 4996)

#include <windows.h>
#include <math.h>
#include <mm3dnow.h>      //mmx routines
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <float.h>
#include <vector>


using namespace std;

class vec2D;

typedef struct _facerect {
	RECT rect;	  //face rectangle
	unsigned int x;     //[x,y] face center coords
	unsigned int y;
	float diag;	 //diag size

	vec2D* face;	//face data, normalized to 0.0 - 1.0 range
} FACERECT, *PFACERECT;

/*template<typename T> void swap(T& x, T& y)
{
	T tmp = x;
	x = y;
	y = tmp;
}*/


#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


