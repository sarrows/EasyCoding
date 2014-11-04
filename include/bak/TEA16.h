/*TEA 16*/

#ifndef _QCRYPTER_H_
#define _QCRYPTER_H_

#include "MD5Cryptor.h"

class CQCryptor
{
public:
	CQCryptor();
	~CQCryptor();
	
	static int  encrypt(unsigned char * in,       // 输入串
                        int             in_len,   // 输入串长度
                        unsigned char * key,      // 密钥
                        unsigned char * out,      // 输出缓冲区
                        int *           out_len); // 输出缓冲区最大长度

	static int  decrypt(unsigned char * in,       // 输入串
                        int             in_len,   // 输入串长度
                        unsigned char * key,      // 密钥
                        unsigned char * out,      // 输出缓冲区
                        int *           out_len); // 输出缓冲区最大长度

private:
	static void tea_encipher(unsigned long * const       v,
                             const unsigned long * const k,
                             unsigned long * const       w);

	static void tea_decipher(unsigned long * const       v,
                             const unsigned long * const k,
                             unsigned long * const       w);
};


#endif

