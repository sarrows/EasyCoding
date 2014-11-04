
#include "any_type.h"
#include "xos.h"

#pragma warning(disable : 4996)

namespace EasyCoding {

#define DEALLOCATE_STR_PTR do { \
	if(vt_ == STR_T) deallocate(v_.pstr_); \
	if(vt_ == WSTR_T) deallocate(v_.pwstr_); \
} while (0)


	inline
		AnyType::AnyType(const char c)
	{
		vt_       = NULL_T;
		v_.pstr_  = 0;
		v_.pwstr_ = 0;
		*this = c;
	}
	inline
		AnyType::AnyType(const wchar_t c)
	{
		vt_       = NULL_T;
		v_.pstr_  = 0;
		v_.pwstr_ = 0;
		*this = c;
	}
	inline AnyType::AnyType(const bool b)
	{
		vt_       = NULL_T;
		v_.pstr_  = 0;
		v_.pwstr_ = 0;
		*this = b;
	}
	inline
		AnyType::AnyType(const double d)
	{
		vt_       = NULL_T;
		v_.pstr_  = 0;
		v_.pwstr_ = 0;
		*this = d;
	}
	inline
		AnyType::AnyType(const int n)
	{
		vt_       = NULL_T;
		v_.pstr_  = 0;
		v_.pwstr_ = 0;
		*this = n;
	}
	inline
		AnyType::AnyType(const uint32 n)
	{
		vt_       = NULL_T;
		v_.pstr_  = 0;
		v_.pwstr_ = 0;
		*this = n;
	}
	inline
		AnyType::AnyType(const long n)
	{
		vt_       = NULL_T;
		v_.pstr_  = 0;
		v_.pwstr_ = 0;
		*this = n;
	}
	inline
		AnyType::AnyType(const ulong n)
	{
		vt_       = NULL_T;
		v_.pstr_  = 0;
		v_.pwstr_ = 0;
		*this = n;
	}
	inline
		AnyType::AnyType(const uint64 n)
	{
		vt_       = NULL_T;
		v_.pstr_  = 0;
		v_.pwstr_ = 0;
		*this = n;
	}
	inline
		AnyType::AnyType(const time_t t)
	{
		vt_       = NULL_T;
		v_.pstr_  = 0;
		v_.pwstr_ = 0;
		*this = t;
	}
	inline
		AnyType::AnyType(const char * p)
	{
		vt_       = NULL_T;
		v_.pstr_  = 0;
		v_.pwstr_ = 0;
		*this = p;
	}
	inline
		AnyType::AnyType(const wchar_t * p)
	{
		vt_       = NULL_T;
		v_.pstr_  = 0;
		v_.pwstr_ = 0;
		*this = p;
	}
	/*********************************************
	*拷贝构造函数
	********************************************/
	inline
		AnyType::AnyType(const AnyType& obj)
	{
		vt_       = NULL_T;
		v_.pstr_  = 0;
		v_.pwstr_ = 0;
		*this = obj;
	}
	/*********************************************
	*赋值操作符
	********************************************/
	inline AnyType & 
		AnyType::operator = (const AnyType & obj)
	{
		DEALLOCATE_STR_PTR;
		vt_ = obj.vt_;
		switch(vt_) {
		case CHAR_T:
			v_.chval_ = obj.v_.chval_;
			break;
		case WCHAR_T:
			v_.wchval_ = obj.v_.wchval_;
			break;
		case BOOL_T:
			v_.b_ = obj.v_.b_;
			break;
		case INT_T:
			v_.nval_ = obj.v_.nval_;
			break;
		case UINT_T:
			v_.uval_ = obj.v_.uval_;
			break;
		case LONG_T:
			v_.lval_ = obj.v_.lval_;
			break;
		case ULONG_T:
			v_.ulval_ = obj.v_.ulval_;
			break;
		case ULONGLONG_T:
			v_.uval64_ = obj.v_.uval64_;
			break;
		case DOUBLE_T:
			v_.dbval_ = obj.v_.dbval_;
			preci_ = obj.preci_;
			break;
		case DATE_T:
			v_.date_ = obj.v_.date_;
			break;
		case STR_T:
			v_.pstr_ = (char*)allocator(strlen(obj.v_.pstr_)+1);
			strcpy (v_.pstr_, obj.v_.pstr_);
			break;
		case WSTR_T:
			v_.pwstr_ = (wchar_t*)allocator((wcslen(obj.v_.pwstr_)+1) * sizeof(wchar_t));
			wcscpy (v_.pwstr_, obj.v_.pwstr_);
			break;
		default:
			break;
		}
		return *this;
	}
	/*字符赋值*/
	inline AnyType &
		AnyType::operator = (const char c)
	{
		DEALLOCATE_STR_PTR;
		vt_ = CHAR_T;
		v_.chval_ = c;
		return * this;
	}
	inline AnyType &
		AnyType::operator = (const wchar_t c)
	{
		DEALLOCATE_STR_PTR;
		vt_ = WCHAR_T;
		v_.wchval_ = c;
		return * this;
	}
	inline AnyType&
		AnyType::operator = (const bool b)
	{
		DEALLOCATE_STR_PTR;
		vt_ = BOOL_T;
		v_.b_ = b;
		return *this;
	}
	/*整形赋值*/
	inline AnyType&
		AnyType::operator = (const int n)
	{
		DEALLOCATE_STR_PTR;
		vt_ = INT_T;
		v_.nval_ = n;
		return *this;
	}
	inline AnyType&
		AnyType::operator = (const uint32 n)
	{
		DEALLOCATE_STR_PTR;
		vt_ = UINT_T;
		v_.uval_ = n;
		return *this;
	}
	inline AnyType &
		AnyType::operator = (const long l)
	{
		DEALLOCATE_STR_PTR;
		vt_ = LONG_T;
		v_.lval_ = l;
		return *this;
	}
	inline AnyType &
		AnyType::operator = (const ulong l)
	{
		DEALLOCATE_STR_PTR;
		vt_ = ULONG_T;
		v_.ulval_ = l;
		return *this;
	}
	inline AnyType &
		AnyType::operator = (const uint64 l)
	{
		DEALLOCATE_STR_PTR;
		vt_ = ULONGLONG_T;
		v_.uval64_= l;
		return *this;
	}
	/*double 赋值*/
	inline AnyType &
		AnyType::operator = (const double db)
	{
		DEALLOCATE_STR_PTR;
		vt_ = DOUBLE_T;
		v_.dbval_ = db;
		preci_ = 2;
		return *this;
	}
	inline AnyType &
		AnyType::operator = (const time_t t)
	{
		DEALLOCATE_STR_PTR;
		vt_      = DATE_T;
		v_.date_ = t;
		return *this;
	}
	/*字符串赋值*/
	inline AnyType &
		AnyType::operator = (const char * p)
	{
		DEALLOCATE_STR_PTR;
		vt_ = STR_T;
		if (p) {
			v_.pstr_ = (char*)allocator(strlen(p)+1);
			strcpy (v_.pstr_, p);
		} else {
			v_.pstr_= NULL;
		}
		return *this;
	}
	inline AnyType &
		AnyType::operator = (const wchar_t * p)
	{
		DEALLOCATE_STR_PTR;
		vt_      = WSTR_T;
		if (p) {
			v_.pwstr_ = (wchar_t*)allocator(wcslen(p)+1);
			wcscpy (v_.pwstr_, p);
		} else {
			v_.pwstr_ = NULL;
		}
		return *this;
	}

	inline std::string AnyType::to_string()
	{
		char* val = 0;
		int size = 1024; // 1024 is enough for the longest converted string (double)
		if (STR_T==vt_ && v_.pstr_) {
			size = strlen(v_.pstr_) + 1;
		} else if (WSTR_T==vt_ && v_.pwstr_) {
			size = (wcslen(v_.pwstr_) + 1) * sizeof(wchar_t);
		}
		val = (char*)allocator(size);

		switch(vt_) {
		case STR_T:
			if(v_.pstr_)
				XOS::snprintf(val, size, "%s", v_.pstr_);
			break;
		case WSTR_T:
			if(v_.pwstr_)
				XOS::translate_to_char(v_.pwstr_, val, size);
			break;
		case DOUBLE_T:
			XOS::snprintf(val, size,  "%f", v_.dbval_);
			break;
		case CHAR_T:
			XOS::snprintf(val, size, "%c", v_.chval_);
			break;
		case INT_T:
			XOS::snprintf(val, size, "%d", v_.nval_);
			break;
		case LONG_T:
			XOS::snprintf(val, size, "%d", v_.lval_);
			break;
		case UINT_T:
			XOS::snprintf(val, size, "%u", v_.uval_);
			break;
		case ULONG_T:
			XOS::snprintf(val, size, "%lu", v_.ulval_);
			break;
		case ULONGLONG_T:
			XOS::snprintf(val, size, "%llu", v_.uval64_);
			break;
		case DATE_T:
			{
				char *wday[]={"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
				struct tm *p = gmtime(&(v_.date_));
				XOS::snprintf(val, size, "%4d-%02d-%02d %s %02d:%02d:%02d",
					1900+p->tm_year, 1+p->tm_mon, p->tm_mday, wday[p->tm_wday], p->tm_hour, p->tm_min, p->tm_sec);
			}
			break;
		default:
			XOS::snprintf(val, size, "%d", v_.nval_);
			break;
		}
		std::string str(val);
		deallocate(val);
		return str;
	}

	inline std::wstring AnyType::to_wstring()
	{
		wchar_t* val = 0;
		int size = 1024 * sizeof(wchar_t);
		if (STR_T==vt_ && v_.pstr_) {
			size = strlen(v_.pstr_) + 1;
		} else if (WSTR_T==vt_ && v_.pwstr_) {
			size = wcslen(v_.pwstr_) + 1;
		}
		size *=  sizeof(wchar_t);
		val = (wchar_t*)allocator(size);

		switch(vt_) {
		case STR_T:
			if(v_.pstr_)
				XOS::translate_to_unicode(v_.pstr_, val, size);
			break;
		case WSTR_T:
			if(v_.pwstr_)
				XOS::snprintf(val, size, L"%s", v_.pwstr_);
			break;
		case DOUBLE_T:
			XOS::snprintf(val, size,  L"%f", v_.dbval_);
			break;
		case CHAR_T:
			XOS::snprintf(val, size, L"%c", v_.chval_);
			break;
		case INT_T:
			XOS::snprintf(val, size, L"%d", v_.nval_);
			break;
		case LONG_T:
			XOS::snprintf(val, size, L"%d", v_.lval_);
			break;
		case UINT_T:
			XOS::snprintf(val, size, L"%u", v_.uval_);
			break;
		case ULONG_T:
			XOS::snprintf(val, size, L"%lu", v_.ulval_);
			break;
		case ULONGLONG_T:
			XOS::snprintf(val, size, L"%llu", v_.uval64_);
			break;
		case DATE_T:
			{
				char *wday[]={"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
				struct tm *p = gmtime(&(v_.date_));
				XOS::snprintf(val, size, L"%4d-%02d-%02d %s %02d:%02d:%02d",
					1900+p->tm_year, 1+p->tm_mon, p->tm_mday, wday[p->tm_wday], p->tm_hour, p->tm_min, p->tm_sec);
			}
			break;
		default:
			XOS::snprintf(val, size, L"%d", v_.nval_);
			break;
		}
		std::wstring str(val);
		deallocate(val);
		return str;
	}

	inline std::string AnyType::to_utf8string()
	{
		std::string strTmp = to_string();
		int len = MultiByteToWideChar(CP_THREAD_ACP, 0, (LPCTSTR)strTmp.c_str(), -1, NULL, 0);
		unsigned short * wszUtf8 = new unsigned short[len+1];
		memset(wszUtf8, 0, len * 2 + 2);
		MultiByteToWideChar(CP_THREAD_ACP, 0, (LPCTSTR)strTmp.c_str(), -1, (LPWSTR)wszUtf8, len);
		len = WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)wszUtf8, -1, NULL, 0, NULL, NULL);
		char *szUtf8 = new char[len + 1];
		memset(szUtf8, 0, len + 1);
		WideCharToMultiByte (CP_UTF8, 0, (LPWSTR)wszUtf8, -1, szUtf8, len, NULL,NULL);
		strTmp = szUtf8;
		delete[] szUtf8;
		delete[] wszUtf8;
		return strTmp;
	}

	inline std::string AnyType::stirng_from_utf8string(const char* pszUtf8)
	{
		int len = MultiByteToWideChar(CP_UTF8, 0, (LPCTSTR)pszUtf8, -1, NULL, 0); 
		unsigned short * wszGBK = new unsigned short[len+1]; 
		memset(wszGBK, 0, len * 2 + 2); 
		MultiByteToWideChar(CP_UTF8, 0, (LPCTSTR)pszUtf8, -1, (LPWSTR)wszGBK, len); 
		len = WideCharToMultiByte(CP_THREAD_ACP, 0, (LPWSTR)wszGBK, -1, NULL, 0, NULL, NULL); 
		char *szGBK = new char[len + 1]; 
		memset(szGBK, 0, len + 1); 
		WideCharToMultiByte (CP_THREAD_ACP, 0, (LPWSTR)wszGBK, -1, szGBK, len, NULL,NULL); 
		std::string strGBK = szGBK; 
		delete[] szGBK; 
		delete[] wszGBK;
		return strGBK;
	}

	/*返回字符*/
	inline
		AnyType::operator char (void) const
	{
		return v_.chval_;
	}
	/*返回字符*/
	inline
		AnyType::operator wchar_t (void) const
	{
		return v_.wchval_;
	}
	/*返回bool*/
	inline AnyType::operator bool(void) const
	{
		return v_.b_;
	}
	/*返回INT型*/
	inline
		AnyType::operator int (void) const
	{
		return v_.nval_;
	}
	inline
		AnyType::operator uint (void) const
	{
		return v_.uval_;
	}
	/*返回LONG型*/
	inline
		AnyType::operator long (void) const
	{
		return v_.lval_;
	}
	inline
		AnyType::operator ulong (void) const
	{
		return v_.ulval_;
	}
	inline
		AnyType::operator uint64 (void) const
	{
		return v_.uval64_;
	}
	/*返回double*/
	inline
		AnyType::operator double (void) const
	{
		return v_.dbval_;
	}
	inline
		AnyType::operator time_t (void) const
	{
		return v_.date_;
	}
	inline
		AnyType::operator const char* (void) const
	{
		return v_.pstr_;
	}
	inline
		AnyType::operator const wchar_t* (void) const
	{
		return v_.pwstr_;
	}
	/*比较函数*/
	inline bool
		AnyType::operator == (const AnyType & obj)
	{
		if(this->vt_ == obj.vt_) {
			switch (this->vt_) {
			case STR_T:
				return operator == (obj.v_.pstr_);
				break;
			case WSTR_T:
				return operator == (obj.v_.pwstr_);
				break;
			case CHAR_T:
				return operator == (obj.v_.chval_);
			case WCHAR_T:
				return operator == (obj.v_.wchval_);
			case BOOL_T:
				return operator == (obj.v_.b_);
			case INT_T:
				return operator == (obj.v_.nval_);
			case UINT_T:
				return operator == (obj.v_.uval_);
			case LONG_T:
				return operator == (obj.v_.lval_);
			case ULONG_T:
				return operator == (obj.v_.ulval_);
			case ULONGLONG_T:
				return operator == (obj.v_.uval64_);
			case DOUBLE_T:
				return operator == (obj.v_.dbval_);
			case DATE_T:
				return operator == (obj.v_.date_);
			default:
				return false;
			}
		}
		return false;	
	}
	inline bool
		AnyType::operator == (const char c)
	{
		return (this->v_.chval_ == c);
	}
	inline bool
		AnyType::operator == (const wchar_t c)
	{
		return (this->v_.wchval_ == c);
	}
	inline bool
		AnyType::operator == (const bool b)
	{
		return (this->v_.b_ == b);
	}
	inline bool
		AnyType::operator == (const int n)
	{
		return (this->v_.nval_ == n);
	}
	inline bool
		AnyType::operator == (const uint n)
	{
		return (this->v_.uval_ == n);
	}
	inline bool
		AnyType::operator == (const long l)
	{
		return (this->v_.lval_ == l);
	}
	inline bool
		AnyType::operator == (const ulong l)
	{
		return (this->v_.ulval_ == l);
	}
	inline bool
		AnyType::operator == (const uint64 l)
	{
		return (this->v_.uval64_ == l);
	}
	inline bool
		AnyType::operator == (const double d)
	{
		return (this->v_.dbval_ == d);
	}
	inline bool
		AnyType::operator == (const time_t t)
	{
		return (this->v_.date_ == t);
	}
	inline bool
		AnyType::operator == (const char* p)
	{
		int i = 0;
		for (i = 0;
			this->v_.pstr_[i] != '\0' && p[i] != '\0';
			i++) {
				if (this->v_.pstr_[i] != p[i])
					return false;
		}
		if (this->v_.pstr_[i] == '\0' && p[i] == '\0')
			return true;
		return false;
	}
	inline bool
		AnyType::operator == (const wchar_t* p)
	{
		int i = 0;
		for (i = 0;
			this->v_.pwstr_[i] != L'\0' && p[i] != L'\0';
			i++) {
				if (this->v_.pwstr_[i] != p[i])
					return false;
		}
		if (this->v_.pwstr_[i] == L'\0' && p[i] == L'\0')
			return true;
		return false;
	}

}