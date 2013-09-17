/*****************************************************************************
 IXXAT Automation GmbH
******************************************************************************

 File    : STDTYPE.H
 Summary : Common constants, basic data types and useful macros.

 Date    : 2001-05-24
 Author  : Hartmut Heim

 Compiler: MSVC

 Remarks : This file is shared between user and kernel mode components.
           Request a kernel mode developer before changing the contents
           of this file.

******************************************************************************
 all rights reserved
*****************************************************************************/

#ifndef _STDTYPE_H_
#define _STDTYPE_H_

/*****************************************************************************
 * compiler specific declarations
 ****************************************************************************/

#ifdef _MSC_VER
#define MICROSOFT_C _MSC_VER
#endif

/*****************************************************************************
 * common constants
 ****************************************************************************/

#ifndef IN
#define IN  // in parameters
#endif

#ifndef OUT
#define OUT // out parameters
#endif

#ifndef TRUE
#define TRUE  1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef NULL
#ifdef __cplusplus
#define NULL   0
#else
#define NULL   ((void*)0)
#endif
#endif

#ifndef EXTERN_C
#ifdef __cplusplus
#define EXTERN_C extern "C"
#else
#define EXTERN_C extern
#endif
#endif


/*****************************************************************************
 * basic data types
 ****************************************************************************/

#ifndef VOID
#define VOID             void
#endif

typedef VOID*            PVOID;
typedef PVOID*           PPVOID;

typedef void             (_cdecl *PVFV)(void);
typedef void             (_cdecl *PCDECLVFV)(void);
typedef void             (_stdcall *PSCALLVFV)(void);


//
// handle to an object
//

#ifdef STRICT
typedef void*            HANDLE;
#else
typedef PVOID            HANDLE;
#endif
typedef HANDLE*          PHANDLE;


//
// boolean types
//

#if !defined(__cplusplus)
typedef int              bool;
#endif

typedef int              BOOL;
typedef BOOL*            PBOOL;

typedef char             BOOL8;
typedef BOOL8*           PBOOL8;

typedef short            BOOL16;
typedef BOOL16*          PBOOL16;

typedef int              BOOL32;
typedef BOOL32*          PBOOL32;


//
// generic numeric types
//

typedef int              INT;
typedef INT*             PINT;

typedef unsigned int     UINT;
typedef UINT*            PUINT;

typedef unsigned int     size_t;

//
// 8-bit signed types
//

typedef char             CHAR;
typedef CHAR*            PCHAR;

typedef signed char      INT8;
typedef INT8*            PINT8;

//
// 8-bit unsigned types
//

typedef unsigned char    UCHAR;
typedef UCHAR*           PUCHAR;

typedef unsigned char    UINT8;
typedef UINT8*           PUINT8;

typedef unsigned char    BYTE;
typedef BYTE*            PBYTE;

//
// 16-bit signed types
//

typedef short            SHORT;
typedef SHORT*           PSHORT;

typedef signed short     INT16;
typedef INT16*           PINT16;

//
// 16-bit unsigned types
//

#if !defined(_WCHAR_T_DEFINED) && !defined(_NATIVE_WCHAR_T_DEFINED)
typedef unsigned short   wchar_t;
#define _WCHAR_T_DEFINED
#endif

typedef wchar_t          WCHAR;
typedef WCHAR           *PWCHAR;


typedef unsigned short   USHORT;
typedef USHORT*          PUSHORT;

typedef unsigned short   UINT16;
typedef UINT16*          PUINT16;

typedef unsigned short   WORD;
typedef WORD*            PWORD;

//
// 32-bit signed types
//

typedef long             LONG;
typedef LONG*            PLONG;

#ifndef _BASETSD_H_
typedef signed int       INT32;
typedef INT32*           PINT32;
#endif

//
// 32-bit unsigned types
//

typedef unsigned long    ULONG;
typedef ULONG*           PULONG;

#ifndef _BASETSD_H_
typedef unsigned long    UINT32;
typedef UINT32*          PUINT32;
#endif

typedef unsigned long    DWORD;
typedef DWORD*           PDWORD;

//
// 64-bit signed types
//

typedef signed __int64   INT64;
typedef INT64*           PINT64;

typedef __int64          LONGLONG;
typedef LONGLONG*        PLONGLONG;

//
// 64-bit unsigned types
//

typedef unsigned __int64 UINT64;
typedef UINT64*          PUINT64;

typedef unsigned __int64 ULONGLONG;
typedef ULONGLONG*       PULONGLONG;

typedef unsigned __int64 QWORD;
typedef QWORD*           PQWORD;

//
// 32-bit floating point types
//

typedef float            FLOAT;
typedef FLOAT*           PFLOAT;

//
// 64-bit floating point types
//

typedef double           DOUBLE;
typedef DOUBLE*          PDOUBLE;

//
// 80-bit floating point types
//

typedef long double      EXTENDED;
typedef EXTENDED*        PEXTENDED;

//
// pointer value types
//
// The SPTRVAL is guaranteed to be the same size as a pointer.
// It's size change with pointer size (32/64). It should be
// used anywhere that a pointer is cast to an integer type.
// UPTRVAL is the unsigned variation.
//

#if defined(_WIN64)
typedef signed   __int64 SPTRVAL, *PSPTRVAL;
typedef unsigned __int64 UPTRVAL, *PUPTRVAL;
#else
typedef signed int       SPTRVAL, *PSPTRVAL;
typedef unsigned int     UPTRVAL, *PUPTRVAL;
#endif


//
// Status values are 32 bit values layed out as follows:
//
//  3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
// +---+-+-------------------------+-------------------------------+
// |Sev|C|       Facility          |               Code            |
// +---+-+-------------------------+-------------------------------+
//
// where
//
//     Sev - is the severity code
//
//         00 - Success
//         01 - Informational
//         10 - Warning
//         11 - Error
//
//     C - is the Customer code flag
//
//     Facility - is the facility code
//
//     Code - is the facility's status code
//
// HRESULT and NTSTATUS are exchangeable
//
typedef LONG             ERESULT;
typedef ERESULT*         PERESULT;

#ifndef HRESULT
#define HRESULT          LONG
#endif

#ifndef NTSTATUS
#define NTSTATUS         LONG
#endif


//
// 128-bit globally unique IDs
//

#ifndef GUID_DEFINED
#define GUID_DEFINED

typedef struct _GUID
{
  DWORD Data1;
  WORD  Data2;
  WORD  Data3;
  BYTE  Data4[8];
} GUID;

#endif // GUID_DEFINED

typedef GUID*            PGUID;
typedef const GUID*      PCGUID;

typedef GUID             CLSID;
typedef CLSID*           PCLSID;
typedef const CLSID*     PCCLSID;

#ifndef _REFGUID_DEFINED
#define _REFGUID_DEFINED
#ifdef __cplusplus
#define REFGUID const GUID &
#else
#define REFGUID const GUID *
#endif
#endif


/*****************************************************************************
 * macros
 ****************************************************************************/

//------------------------------------------------------------------------
// Macro:
//  MAKEWORD
//
// Description:
//  This macro creates a 16-bit value by concatenating the specified
//  8-bit values. 
//
// Arguments:
//  l -> Specifies the low-order byte of the new value. 
//  h -> Specifies the high-order byte of the new value. 
//
// Results:
//  Returns the new 16-bit value.
//------------------------------------------------------------------------
#ifndef MAKEWORD
#define MAKEWORD(l,h) ((WORD)(((BYTE)(l))|(((WORD)((BYTE)(h)))<<8)))
#endif

//------------------------------------------------------------------------
// Macro:
//  MAKELONG
//
// Description:
//  This macro creates a 32-bit value by concatenating the specified
//  16-bit values. 
//
// Arguments:
//  l -> Specifies the low-order word of the new value. 
//  h -> Specifies the high-order word of the new value. 
//
// Results:
//  Returns the new 32-bit value.
//------------------------------------------------------------------------
#ifndef MAKELONG
#define MAKELONG(l,h) ((LONG)(((WORD)(l))|(((DWORD)((WORD)(h)))<<16)))
#endif

//------------------------------------------------------------------------
// Macro:
//  FIELDOFFSET
//
// Description:
//  This macro calculates the offset of a member variable within the
//  specified data structure.
//
// Arguments:
//  type  -> type of the data structure
//  field -> name of the member variable
//
// Results:
//  Returns the offset of the member variable within the specified
//  data structure.
//------------------------------------------------------------------------
#ifndef FIELDOFFSET
#define FIELDOFFSET(type,field) ((UPTRVAL)(&((type*)0)->field))
#endif

//------------------------------------------------------------------------
// Macro:
//  HOSTOBJECT
//
// Description:
//  This macro retrieve a reference to the host object.
//
// Arguments:
//  t -> Type of the host object
//  m -> Member variable which represents the inner object
//
// Results:
//  Reference to the host object.
//------------------------------------------------------------------------
#ifdef __cplusplus
#ifndef HOSTOBJECT
#define HOSTOBJECT(t,m) ((t&) *((PCHAR) this - (UPTRVAL)(&((t*)0)->m)))
#endif
#endif

//------------------------------------------------------------------------
// Macro:
//  OUTEROBJECT
//
// Description:
//  This macro retrieve a pointer to the outer object.
//
// Arguments:
//  i -> Pointer to the inner object
//  m -> Member variable which represents the inner object
//  t -> Type of the outer object
//
// Results:
//  Pointer to the outer object.
//------------------------------------------------------------------------
#ifndef OUTEROBJECT
#define OUTEROBJECT(i,m,t) ((t*) ((PCHAR)(i) - (UPTRVAL)(&((t*)0)->m)))
#endif

//------------------------------------------------------------------------
// Macro:
//  ARRAYSIZE, NUMELEM
//
// Description:
//  This macro retreives the number of elements within the specified array.
//
// Arguments:
//  array -> array for which to retrieve the number of elements
//
// Results:
//  Returns the number of elements within the specified array.
//------------------------------------------------------------------------
#ifndef ARRAYSIZE
#define ARRAYSIZE(array) (sizeof(array)/sizeof((array)[0]))
#endif

#ifndef NUMELEM
#define NUMELEM(array) (sizeof(array) / sizeof(array[0]))
#endif

//------------------------------------------------------------------------
// Macro:
//  min
//
// Description:
//  This macro retreives the smaller of two values.
//
// Arguments:
//  a -> value 1 to be compared
//  b -> value 2 to be compared
//
// Results:
//  Returns the smaller of the two arguments.
//------------------------------------------------------------------------
#ifndef min
#define min(a,b) (((a) < (b)) ? (a) : (b))
#endif

//------------------------------------------------------------------------
// Macro:
//  max
//
// Description:
//  This macro retreives the larger of two values.
//
// Arguments:
//  a -> value 1 to be compared
//  b -> value 2 to be compared
//
// Results:
//  Returns the larger of the two arguments.
//------------------------------------------------------------------------
#ifndef max
#define max(a,b) (((a) > (b)) ? (a) : (b))
#endif

//------------------------------------------------------------------------
// Macro:
//  LONIBBLE
//
// Description:
//  This macro retreives the lower 4 bits of the given 8-bit value.
//
// Arguments:
//  b -> 8-bit value
//
// Results:
//  Low-order nibble (bit 0..3) of the specified value.
//------------------------------------------------------------------------
#ifndef LONIBBLE
#define LONIBBLE(b) ( (BYTE) (b) & 0x0F )
#endif

//------------------------------------------------------------------------
// Macro:
//  HINIBBLE
//
// Description:
//  This macro retreives the upper 4 bits of the given 8-bit value.
//
// Arguments:
//  b -> 8-bit value
//
// Results:
//  High-order nibble (bit 4..7) of the specified value.
//------------------------------------------------------------------------
#ifndef HINIBBLE
#define HINIBBLE(b) ( (BYTE) (b) >> 4 )
#endif

//------------------------------------------------------------------------
// Macro:
//  LOBYTE
//
// Description:
//  This macro retreives the lower 8 bits of the given 16-bit value.
//
// Arguments:
//  w -> 16-bit value
//
// Results:
//  Low-order byte (bit 0..7) of the specified value.
//------------------------------------------------------------------------
#ifndef LOBYTE
#define LOBYTE(w) ( (BYTE) (w) )
#endif

//------------------------------------------------------------------------
// Macro:
//  HIBYTE
//
// Description:
//  This macro retreives the upper 8 bits of the given 16-bit value.
//
// Arguments:
//  w -> 16-bit value
//
// Results:
//  High-order byte (bit 8..15) of the specified value.
//------------------------------------------------------------------------
#ifndef HIBYTE
#define HIBYTE(w) ( (BYTE) ((WORD)(w) >> 8) )
#endif

//------------------------------------------------------------------------
// Macro:
//  LOWORD
//
// Description:
//  This macro retreives the lower 16 bits of the given 32-bit value.
//
// Arguments:
//  l -> 32-bit value
//
// Results:
//  Low-order word (bit 0..15) of the specified value.
//------------------------------------------------------------------------
#ifndef LOWORD
#define LOWORD(l) ( (WORD) (l) )
#endif

//------------------------------------------------------------------------
// Macro:
//  HIWORD
//
// Description:
//  This macro retreives the upper 16 bits of the given 32-bit value.
//
// Arguments:
//  l -> 32-bit value
//
// Results:
//  High-order word (bit 8..15) of the specified value.
//------------------------------------------------------------------------
#ifndef HIWORD
#define HIWORD(l) ( (WORD) ((DWORD)(l) >> 16) )
#endif

//------------------------------------------------------------------------
// Macro:
//  SETPVAR
//
// Description:
//  This macro stores a value in the specified variable.
//
// Arguments:
//  p -> points to the variable
//  v -> value to store in the variable
//
// Results:
//  none
//------------------------------------------------------------------------
#ifndef SETPVAR
#define SETPVAR(p,v) ( (p) ? (*(p) = (v)) : 0 )
#endif

//------------------------------------------------------------------------
// Macro:
//  XCHG
//
// Description:
//  This macro exchange two variables.
//
// Arguments:
//  type -> data type of the variables
//  a    -> variable 1
//  b    -> variable 2
//
// Results:
//  none
//------------------------------------------------------------------------
#ifndef XCHG
#define XCHG(type,a,b) {type x=(type)(a);(type)(a)=(type)(b);(type)(b)=x;}
#endif

//------------------------------------------------------------------------
// Macro:
//  XCHG8, XCHG16, XCHG32, XCHG64
//
// Description:
//  This macros exchange two variables of type BYTE, WORD or DWORD.
//
// Arguments:
//  a -> variable 1
//  b -> variable 2
//
// Results:
//  none
//------------------------------------------------------------------------
#ifndef XCHG8
#define XCHG8(a,b) {BYTE x=(BYTE)(a);(BYTE)(a)=(BYTE)(b);(BYTE)(b)=x;}
#endif
#ifndef XCHG16
#define XCHG16(a,b) {WORD x=(WORD)(a);(WORD)(a)=(WORD)(b);(WORD)(b)=x;}
#endif
#ifndef XCHG32
#define XCHG32(a,b) {DWORD x=(DWORD)(a);(DWORD)(a)=(DWORD)(b);(DWORD)(b)=x;}
#endif
#ifndef XCHG64
#define XCHG64(a,b) {QWORD x=(QWORD)(a);(QWORD)(a)=(QWORD)(b);(QWORD)(b)=x;}
#endif

//------------------------------------------------------------------------
// Macro:
//  ROUND_UP
//
// Description:
//  This macro returns a number rounded up to the nearest multiple
//  of the specified base value.
//
// Arguments:
//  v -> value to round up
//  b -> unsigned base value
//
// Results:
//  Rounded value.
//------------------------------------------------------------------------
#ifndef ROUND_UP
#define ROUND_UP(v,b) ( ((v) + (b) - 1) &~ ((b) - 1) )
#endif

//------------------------------------------------------------------------
// Macro:
//  RNDUP8, RNDUP16, RNDUP32, RNDUP64
//
// Description:
//  This macro returns a BYTE, WORD, DWORD or QWORD number rounded up
//  to the nearest multiple of the specified base value.
//
// Arguments:
//  v -> value to round up
//  b -> unsigned base value
//
// Results:
//  Rounded value.
//------------------------------------------------------------------------
#ifndef RNDUP8
#define RNDUP8(v,b) ( ((BYTE)(v) + (b) - 1) &~ ((b) - 1) )
#endif
#ifndef RNDUP16
#define RNDUP16(v,b) ( ((WORD)(v) + (b) - 1) &~ ((b) - 1) )
#endif
#ifndef RNDUP32
#define RNDUP32(v,b) ( ((DWORD)(v) + (b) - 1) &~ ((b) - 1) )
#endif
#ifndef RNDUP64
#define RNDUP64(v,b) ( ((QWORD)(v) + (b) - 1) &~ ((b) - 1) )
#endif

//------------------------------------------------------------------------
// Macro:
//  ROUND_DN
//
// Description:
//  This macro returns a number rounded down to the nearest
//  multiple of the specified base value.
//
// Arguments:
//  v -> value to round down
//  b -> unsigned base value
//
// Results:
//  Rounded value.
//------------------------------------------------------------------------
#ifndef ROUND_DN
#define ROUND_DN(v,b) ( (v) &~ ((b) - 1) )
#endif

//------------------------------------------------------------------------
// Macro:
//  RNDDN8, RNDDN16, RNDDN32, RNDDN64
//
// Description:
//  This macro returns a BYTE, WORD DWORD or QWORD number rounded
//  down to the nearest multiple of the specified base value.
//
// Arguments:
//  v -> value to round down
//  b -> unsigned base value
//
// Results:
//  Rounded value.
//------------------------------------------------------------------------
#ifndef RNDDN8
#define RNDDN8(v,b) ( (BYTE)(v) &~ ((b) - 1) )
#endif
#ifndef RNDDN16
#define RNDDN16(v,b) ( (WORD)(v) &~ ((b) - 1) )
#endif
#ifndef RNDDN32
#define RNDDN32(v,b) ( (DWORD)(v) &~ ((b) - 1) )
#endif
#ifndef RNDDN64
#define RNDDN64(v,b) ( (QWORD)(v) &~ ((b) - 1) )
#endif

#endif //_STDTYPE_H_

