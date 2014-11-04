#ifndef __ANY_TYPE_H
#define __ANY_TYPE_H

#include "config_platform.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <string>

namespace EasyCoding {

	/********************************************************************
	* file: Any_type.h
	* by:   liguoqiang
	* desc: 实现类型无关性，可以用AnyType代替所有类型
	* 目前常用类型包括:整形,字符串,日期,double,float,char等
	*******************************************************************/
	class ECExport AnyType
	{
	private:
		/*采用联合类型存放各种数据类型*/
		union {
			bool b_;
			char   chval_;
			wchar_t wchval_;
			int    nval_;
			uint32 uval_;
			uint64 uval64_;
			long   lval_;
			ulong  ulval_;
			double dbval_;
			time_t date_;
			char * pstr_;
			wchar_t * pwstr_;
		} v_;

	public:
		/*枚举类型表示数据类型*/	
		enum {
			NULL_T = -1,
			CHAR_T = 0,
			WCHAR_T,
			BOOL_T,
			INT_T,
			UINT_T,
			LONG_T,
			ULONG_T,
			ULONGLONG_T,
			DOUBLE_T,
			DATE_T,
			STR_T,
			WSTR_T} vt_;

	public:
		AnyType ()
		{
			vt_ = NULL_T;
			v_.uval64_ = 0; // 之所以设置 uval64_ 为0，因为它最长
		}
		/*构造函数*/
		explicit AnyType(const char c);
		explicit AnyType(const wchar_t c);
		explicit AnyType(const bool b);
		explicit AnyType(const int n);
		explicit AnyType(const uint32 u);
		explicit AnyType(const long l);
		explicit AnyType(const ulong l);
		explicit AnyType(const uint64 l);
		explicit AnyType(const double d);
		explicit AnyType(const time_t t);
		explicit AnyType(const char * p);
		explicit AnyType(const wchar_t * p);
		explicit AnyType(const AnyType& obj);
		/*析构函数*/
		~AnyType() { if (vt_ == STR_T) deallocate(v_.pstr_);}

		AnyType & operator = (const AnyType & obj);
		AnyType & operator = (const char ch);
		AnyType & operator = (const wchar_t ch);
		AnyType & operator = (const bool b);
		AnyType & operator = (const int n);
		AnyType & operator = (const uint32 n);
		AnyType & operator = (const long l);
		AnyType & operator = (const ulong n);
		AnyType & operator = (const uint64 n);
		AnyType & operator = (const double d);
		AnyType & operator = (const time_t t);
		AnyType & operator = (const char * p);
		AnyType & operator = (const wchar_t * p);

		operator char (void) const;
		operator wchar_t (void) const;
		operator bool(void) const;
		operator int(void) const;
		operator uint32(void) const;
		operator long (void) const;
		operator ulong(void) const;
		operator uint64(void) const;
		operator double (void) const;
		operator time_t (void) const;
		operator const char* (void) const;
		operator const wchar_t* (void) const;

		void precision(int preci) { preci_ = preci; } //设置DOUBLE的精度
		int  precision() const { return preci_; }
		std::string to_string();
		std::wstring to_wstring();
		std::string to_utf8string();
		static std::string stirng_from_utf8string(const char* pszUtf8);

		bool operator == (const AnyType& obj); //比较函数
		bool operator == (const char c);
		bool operator == (const wchar_t c);
		bool operator == (const bool b);
		bool operator == (const int n);
		bool operator == (const uint32 n);
		bool operator == (const long l);
		bool operator == (const ulong n);
		bool operator == (const uint64 n);
		bool operator == (const double d);
		bool operator == (const time_t t);
		bool operator == (const char* p);
		bool operator == (const wchar_t* p);

	private:
		void* allocator(size_t size)
		{
			char * p = 0;
			if (size > 0) p = new char[size];
			return (void*)p;
		}
		void  deallocate(void* p)
		{
			if (p) delete [] (char*)p;
		}

	private:
		int preci_;       //DOUBLE的精度值
	};
}

#endif
