
#include "config_platform.h"
#include "xos.h"

PUSH_DISABLE_WARNING(4996)

int XOS::snprintf(char* buf, size_t size, const char* fmt,...)
{
	int result;
	va_list ap;
	va_start (ap, fmt);
		result = _vsnprintf(buf, size, fmt, ap);
	va_end (ap);
	return result;
}

int XOS::snprintf(wchar_t* buf, size_t size, const wchar_t* fmt,...)
{
	int result;
	va_list ap;
	va_start (ap, fmt);
	result = _vsnwprintf(buf, size, fmt, ap);
	va_end (ap);
	return result;
}

char* XOS::strncpy(char* dest, const char* src, size_t size)
{
	char* tmp = dest;
	while(size-- && (*dest++ = *src++) != '\0');
	return tmp;
}

wchar_t* XOS::strncpy(wchar_t* dest, const wchar_t* src, size_t size)
{
	wchar_t* tmp = dest;
	while(size-- && (*dest++ = *src++) != wchar_t('\0'));
	return tmp;
}

char* XOS::getmodulename(HMODULE module,
			const char* filename,
			char* fullpath)
{
	char path[MAX_PATH];
	GetModuleFileNameA(module, path, MAX_PATH);

	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];
	_splitpath( path, drive, dir, fname, ext );
	sprintf(fullpath,
			"%s%s%s",
			drive,
			dir,
			filename);
	return fullpath;

}

char* XOS::getmodulename(const char* filename, char* fullpath)
{
	return getmodulename(0, filename, fullpath);
}

char* XOS::getmodulepath(HMODULE module, char* pathname)
{
	char path[MAX_PATH];
	GetModuleFileNameA(module, path, MAX_PATH);

	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];
	_splitpath(path, drive, dir, fname, ext );
	sprintf(pathname, "%s%s", drive, dir);
	return pathname;
}

char* XOS::getmodulepath(char* pathname)
{
	return getmodulepath(0, pathname);
}

/*
 * translate UNICODE and ascii
 * packaging WideCharToMultiByte() in windows
 */
const char* XOS::translate_to_char(const wchar_t* src, char* dest, int size)
{
	WideCharToMultiByte(
			CP_ACP,
			0,
			src,
			-1,
			dest,
			size,
			NULL,
			NULL);
	return dest;
}

/*
 * translate ascii to UNICODE
 * packaging MultiByteToWideChar() in windows
 */
const wchar_t* XOS::translate_to_unicode(const char* src, wchar_t* dest, int size)
{
	MultiByteToWideChar(
			CP_ACP,
			0,
			src,
			-1,
			dest,
			size);
	return dest;
}

//UTF-8到GB2312的转换
int XOS::UTF8_to_GB2312(const char* utf8, char* gb2312, int size)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len+1];
	memset(wstr, 0, len+1);
	MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wstr, len);
	len = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
	if (size > len && gb2312) {
		memset(gb2312, 0, len+1);
		WideCharToMultiByte(CP_ACP, 0, wstr, -1, gb2312, len, NULL, NULL);
	}
	if(wstr) delete[] wstr;
	return len+1;
}

//GB2312到UTF-8的转换
int XOS::GB2312_to_UTF8(const char* gb2312, char* utf8, int size)
{
	int len = MultiByteToWideChar(CP_ACP, 0, gb2312, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len+1];
	memset(wstr, 0, len+1);
	MultiByteToWideChar(CP_ACP, 0, gb2312, -1, wstr, len);
	len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
	if (size > len && utf8) {
		memset(utf8, 0, len+1);
		WideCharToMultiByte(CP_UTF8, 0, wstr, -1, utf8, len, NULL, NULL);
	}
	if(wstr) delete[] wstr;
	return len+1;
}

/***************************************************
 * 事件机制,事件初始化
 ***************************************************/
int XOS::XosEvent::init(event_t *evt, bool manual, bool initial_state)
{
	if ( NULL == ((*evt) = CreateEvent(NULL, manual, initial_state, NULL)))
		return -1;
	return 0;
}
/**************************************
 * 等待
 *************************************/
bool XOS::XosEvent::wait (event_t *evt, timeval * tv)
{
	return WAIT_OBJECT_0==WaitForSingleObject (*evt,
		(tv == NULL ? INFINITE : (tv->tv_sec * 1000 + tv->tv_usec)));
}
/****************************************
 * 设置事件
 *************************************/
void XOS::XosEvent::set (event_t *evt)
{
	SetEvent(*evt);
}
/****************************************
 * 重置事件
 *************************************/
void XOS::XosEvent::reset (event_t *evt)
{
	ResetEvent(*evt);
}
/***************************
 * 删除事件变量
 **************************/
void XOS::XosEvent::destroy(event_t *evt)
{
	CloseHandle(*evt);
}

/***************************************************
 * 线程间锁机制,锁初始化
 ***************************************************/
void XOS::XosMutex::init(thread_mutex_t * mt)
{
	InitializeCriticalSection(mt);
}

/***************************
 * 释放锁变量
 **************************/
void XOS::XosMutex::destroy(thread_mutex_t *mt)
{
	DeleteCriticalSection(mt);
}

/***************************
 * 加锁
 **************************/
void XOS::XosMutex::lock(thread_mutex_t * mt)
{
	EnterCriticalSection(mt);
}

/***************************
 * 释放锁
 **************************/
void XOS::XosMutex::unlock(thread_mutex_t* mt)
{
	LeaveCriticalSection(mt);
}

/**********************************
 * 尝试锁
 **********************************/
bool XOS::XosMutex::trylock(thread_mutex_t* mt)
{
	return FALSE!=TryEnterCriticalSection(mt);
}

/*******************************************************
 * 信号灯
 ******************************************************/
int XOS::XosSemaphore::init(sem_t * sem, int shared, unsigned int val)
{
	(*sem) = CreateSemaphore(NULL, 0, (long)val, NULL);
	return (*sem) ? 0 : -1;
}

/**************************************
 * 等待
 *************************************/
bool XOS::XosSemaphore::wait(sem_t *sem, timeval * tv)
{
	DWORD tm = (tv == NULL ? INFINITE : (tv->tv_sec * 1000 + tv->tv_usec));
	return (WAIT_OBJECT_0 == WaitForSingleObject (*sem, tm));
}

/****************************************
 * 释放信号灯
 *************************************/
void XOS::XosSemaphore::post (sem_t * sem)
{
	ReleaseSemaphore(*sem, 1, NULL);
}
/**************************************
 * 删除信号灯变量
 *************************************/
void XOS::XosSemaphore::destroy(sem_t *sem)
{
	CloseHandle(*sem);
}

POP_WARNING()
