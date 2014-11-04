#ifndef __EXCEPTION_INCLUDE__
#define __EXCEPTION_INCLUDE__

#include "config_platform.h"
#include "xos.h"

#pragma warning(disable : 4996)

#ifndef EXCP_DESC_LEN
#define EXCP_DESC_LEN (512)
#endif

class ECExport Exception
{
public:
	//construct function
	//only support int and const char
	//if want to input wchar you need to use write_error_w()
	Exception(int err) : errcode_(err){}
	/*
	 * construct function only support ascii error message.
	 */
	Exception(int err, const char* fmt,...) : errcode_(err)
	{
		va_list cp;
		va_start(cp, fmt);
		vsnprintf(desc_, EXCP_DESC_LEN, fmt, cp);
		va_end(cp);
	}
	Exception(int err, const wchar_t* fmt,...) : errcode_(err)
	{
		wchar_t buf[EXCP_DESC_LEN];
		va_list cp;
		va_start(cp, fmt);
#ifdef MY_WIN32
		_vsnwprintf(buf, EXCP_DESC_LEN, fmt, cp);
#else
		vswprintf(buf, EXCP_DESC_LEN, fmt, cp);
#endif
		va_end(cp);
		XOS::translate_to_char(buf, desc_, sizeof(desc_));
	}
	virtual ~Exception() throw() {}
	int errcode() const { return errcode_;}         //·µ»Ø´íÎóÂë
	const char* what() const throw()
	{
		return desc_;
	}
	const wchar_t* what_w() const throw()
	{
		static wchar_t buf[EXCP_DESC_LEN];
		XOS::translate_to_unicode(desc_, buf, EXCP_DESC_LEN);
		return buf;
	}
protected:
	int errcode_;
	char desc_[EXCP_DESC_LEN];
};

#endif
