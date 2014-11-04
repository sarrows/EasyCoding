/*TEA 16*/

#ifndef _QCRYPTER_H_
#define _QCRYPTER_H_

#include "MD5Cryptor.h"

class CQCryptor
{
public:
	CQCryptor();
	~CQCryptor();
	
	static int  encrypt(unsigned char * in,       // ���봮
                        int             in_len,   // ���봮����
                        unsigned char * key,      // ��Կ
                        unsigned char * out,      // ���������
                        int *           out_len); // �����������󳤶�

	static int  decrypt(unsigned char * in,       // ���봮
                        int             in_len,   // ���봮����
                        unsigned char * key,      // ��Կ
                        unsigned char * out,      // ���������
                        int *           out_len); // �����������󳤶�

private:
	static void tea_encipher(unsigned long * const       v,
                             const unsigned long * const k,
                             unsigned long * const       w);

	static void tea_decipher(unsigned long * const       v,
                             const unsigned long * const k,
                             unsigned long * const       w);
};


#endif

