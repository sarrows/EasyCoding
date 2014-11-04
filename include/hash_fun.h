#ifndef __HASH_FUNCTION_INCLUDE
#define __HASH_FUNCTION_INCLUDE

/*****************************************************
 * author: ���ǿ
 * date: 2006-1-10
 * desc: ʵ��HASH���õ�HASH����,
 * 	HASH�����ķ���ֵ��HASH���еı�����
 ****************************************************/

#include <string> 
/*****************************************************
 *Ĭ�ϵ�ģ����,������Ϊ�û��Զ�������ʱ,����KEY�ķº���
 ****************************************************/
template<typename Key> struct HashFunc
{
	size_t operator()(const Key & key) const
	{
		return key();
	}
};

/****************************************************
 * �ַ�������,�����ַ�������KEY
 * ������Ϊ��������,Ҫ���ַ���ǰ5���ַ����
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
 * ƫ�ػ�ģ��,ʵ�ֱ�׼���͵�ģ�嶨��
 * �������ַ���
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
