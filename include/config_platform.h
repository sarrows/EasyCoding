#ifndef __CONFIG_PLATFORM__
#define __CONFIG_PLATFORM__

#ifdef _WIN32_WINNT
#undef _WIN32_WINNT
#define WIN32_LEAN_AND_MEAN
#define _WIN32_WINNT 0x0400
#endif

#include <winsock2.h>
#include <time.h>
#include <stdlib.h>
#include <shellapi.h>
#include <wtypes.h>
#include <stdio.h>
#include <tchar.h>

typedef unsigned int  size_t;
typedef unsigned int  uint;
typedef unsigned long ulong;
typedef unsigned char uchar;
typedef short word16;
typedef unsigned short ushort;
typedef unsigned int uint32;
typedef unsigned __int64 uint64;
typedef __int64 int64;

#ifndef MAX_PATH
#define MAX_PATH 255
#endif

#ifndef NULL
#define NULL (0)
#endif

#ifdef WIN32
#define MY_WIN32
#endif

#define size_npos ((uint)-1)

// ±‡“ÎæØ∏Êœ‡πÿ

#ifndef PUSH_DISABLE_WARNING
#define PUSH_DISABLE_WARNING(n) __pragma(warning(push)) \
	__pragma(warning(disable:n))
#endif

#ifndef POP_WARNING
#define POP_WARNING() __pragma(warning(pop))
#endif

#ifndef ALLOW_THIS_IN_INITIALIZER_LIST
#define ALLOW_THIS_IN_INITIALIZER_LIST(code) \
	PUSH_DISABLE_WARNING(4355) \
	code \
	POP_WARNING()
#endif


#  if defined (EC_EXPORT)
#    define ECExport __declspec (dllexport)
//#    pragma warning(disable:4275)
//#    pragma warning(disable:4251)
#  else
#    define ECExport __declspec (dllimport)
#  endif

#endif // __CONFIG_PLATFORM_INCLUDE__
