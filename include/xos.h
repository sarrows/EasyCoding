#ifndef __UTILS_H__
#define __UTILS_H__

#include "config_platform.h"

namespace XOS {
	ECExport int      snprintf(char* buf, size_t size, const char* fmt,...);
	ECExport int      snprintf(wchar_t* buf, size_t size, const wchar_t* fmt,...);
	ECExport char*    strncpy(char* dest, const char* src, size_t size);
	ECExport wchar_t* strncpy(wchar_t* dest, const wchar_t* src, size_t size);
	ECExport char*    getmodulename(HMODULE module, const char* filename,char* fullpath);
	ECExport char*    getmodulename(const char* filename, char* fullpath);
	ECExport char*    getmodulepath(HMODULE module, char* pathname);
	ECExport char*    getmodulepath(char* pathname);
	/*
	 * translate UNICODE and ascii
	 * packaging WideCharToMultiByte() in windows
	 */
	ECExport const char*  translate_to_char(const wchar_t* src, char* dest, int size);
	/*
	 * translate ascii to UNICODE
	 * packaging MultiByteToWideChar() in windows
	 */
	ECExport const wchar_t*  translate_to_unicode(const char* src, wchar_t* dest, int size);
	ECExport int UTF8_to_GB2312(const char* utf8, char* gb2312, int size);
	ECExport int GB2312_to_UTF8(const char* gb2312, char* utf8, int size);

	typedef CRITICAL_SECTION thread_mutex_t; //win32锁类型
	typedef HANDLE sem_t;                    //信号灯变量
	typedef HANDLE event_t;                  //信号灯变量
	/*实现事件*/
	class ECExport XosEvent
	{
	public:
		static int  init(event_t *evt, bool manual, bool initial_state);
		static void destroy(event_t* evt);
		static bool wait(event_t* evt, timeval* tv);
		static bool trywait(event_t* evt);
		static void set(event_t* evt);
		static void reset(event_t* evt);
	};
	/*实现通用锁*/
	class ECExport XosMutex
	{
	public:
		static void init(thread_mutex_t* mt);
		static void destroy(thread_mutex_t* mt);
		static void lock(thread_mutex_t* mt);
		static void unlock(thread_mutex_t* mt);
		static bool trylock(thread_mutex_t* mt);
	};
	/*通用信号量*/
	class ECExport XosSemaphore
	{
	public:
		static int  init(sem_t* sem, int shared, unsigned int val);
		static bool wait(sem_t* sem, timeval* tv);
		static bool trywait(sem_t* sem);
		static void post(sem_t* sem);
		static void destroy(sem_t *sem);
	};
}

#endif
