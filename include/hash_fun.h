#ifndef __HASH_FUNCTION_INCLUDE
#define __HASH_FUNCTION_INCLUDE

/*****************************************************
 * author: 李国强
 * date: 2006-1-10
 * desc: 实现HASH表常用的HASH函数,
 * 	HASH函数的返回值是HASH表中的被除数
 ****************************************************/

#include <string> 
/*****************************************************
 *默认的模板类,当类型为用户自定义类型时,调用KEY的仿函数
 ****************************************************/
template<typename Key> struct HashFunc
{
	size_t operator()(const Key & key) const
	{
		return key();
	}
};

/****************************************************
 * 字符串函数,根据字符串生成KEY
 * 本函数为内联函数,要求字符串前5个字符相等
 ***************************************************/
inline size_t hash_string_key (const char * s)
{
	size_t sum = 0;
	for (int i = 0; i < 5 && *s; i++, s++) {
		sum = sum * (*s < 10 ? 10 : 100);
		sum += *s;
	}
	return sum;
}
/****************************************************
 * 偏特化模板,实现标准类型的模板定义
 * 首先是字符串
 ***************************************************/
template<> struct HashFunc<char*> { size_t operator()(char * p) const {return hash_string_key(p);} };
template<> struct HashFunc<const char*> { size_t operator()(const char * p) const {return hash_string_key(p);}};
template<> struct HashFunc<unsigned char*> { size_t operator()(char * p) const {return hash_string_key(p);} };
template<> struct HashFunc<const unsigned char*> { size_t operator()(const char * p) const {return hash_string_key(p);}};
template<> struct HashFunc<char> { size_t operator()(char ch) const {return ch;} };
template<> struct HashFunc<unsigned char> { size_t operator()(unsigned char ch) const {return ch;} };
template<> struct HashFunc<short> { size_t operator()(short n) const {return n;} };
template<> struct HashFunc<unsigned short> { size_t operator()(unsigned short n) const {return n;} };
template<> struct HashFunc<int> { size_t operator()(int n) const {return n;} };
template<> struct HashFunc<unsigned int> { size_t operator()(unsigned int n) const {return n;} };
template<> struct HashFunc<long> { size_t operator()(long n) const {return n;} };
template<> struct HashFunc<unsigned long> { size_t operator()(unsigned long n) const {return n;} };
template<> struct HashFunc<std::string>
{
    size_t operator()(std::string s) const
    {
        return s.length();
    }
};

#endif
