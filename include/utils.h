#ifndef __EC_UTILS_H__
#define __EC_UTILS_H__

#include "config_platform.h"

namespace EasyCoding {
	int      snprintf(char* buf, size_t size, const char* fmt,...);
	int      snprintf(wchar_t* buf, size_t size, const wchar_t* fmt,...);
	char*    strncpy(char* dest, const char* src, size_t size);
	wchar_t* strncpy(wchar_t* dest, const wchar_t* src, size_t size);
	char*    getmodulename(HMODULE module, const char* filename,char* fullpath);
	char*    getmodulename(const char* filename, char* fullpath);
	char*    getmodulepath(HMODULE module, char* pathname);
	char*    getmodulepath(char* pathname);
	/*
	 * translate UNICODE and ascii
	 * packaging WideCharToMultiByte() in windows
	 */
	const char*  translate_to_char(const wchar_t* src, char* dest, int size);
	/*
	 * translate ascii to UNICODE
	 * packaging MultiByteToWideChar() in windows
	 */
	const wchar_t*  translate_to_unicode(const char* src, wchar_t* dest, int size);
}

#endif
