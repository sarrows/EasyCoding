
#include "config_platform.h"
#include "utils.h"

PUSH_DISABLE_WARNING(4996)

int EasyCoding::snprintf(char* buf, size_t size, const char* fmt,...)
{
	int result;
	va_list ap;
	va_start (ap, fmt);
		result = _vsnprintf(buf, size, fmt, ap);
	va_end (ap);
	return result;
}

int EasyCoding::snprintf(wchar_t* buf, size_t size, const wchar_t* fmt,...)
{
	int result;
	va_list ap;
	va_start (ap, fmt);
	result = _vsnwprintf(buf, size, fmt, ap);
	va_end (ap);
	return result;
}

char* EasyCoding::strncpy(char* dest, const char* src, size_t size)
{
	char* tmp = dest;
	while(size-- && (*dest++ = *src++) != '\0');
	return tmp;
}

wchar_t* EasyCoding::strncpy(wchar_t* dest, const wchar_t* src, size_t size)
{
	wchar_t* tmp = dest;
	while(size-- && (*dest++ = *src++) != wchar_t('\0'));
	return tmp;
}

char* EasyCoding::getmodulename(HMODULE module,
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

char* EasyCoding::getmodulename(const char* filename, char* fullpath)
{
	return getmodulename(0, filename, fullpath);
}

char* EasyCoding::getmodulepath(HMODULE module, char* pathname)
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

char* EasyCoding::getmodulepath(char* pathname)
{
	return getmodulepath(0, pathname);
}

/*
 * translate UNICODE and ascii
 * packaging WideCharToMultiByte() in windows
 */
const char* EasyCoding::translate_to_char(const wchar_t* src, char* dest, int size)
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
const wchar_t* EasyCoding::translate_to_unicode(const char* src, wchar_t* dest, int size)
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

POP_WARNING()
