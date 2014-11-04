#ifndef _CMD5CRYPTOR_H_
#define _CMD5CRYPTOR_H_

class CMD5Contex
{
public:

#ifndef uint8
#define uint8  unsigned char
#endif
#ifndef uint32
#define uint32 unsigned long int
#endif
#ifndef byte
#define byte unsigned char
#endif

public:
    uint32 total[2];
    uint32 state[4];
    uint8 buffer[64];
};

class CMD5Cryptor
{
public:
	static void md5_starts( CMD5Contex *ctx );
	static void md5_update( CMD5Contex *ctx, uint8 *input, uint32 length );
	static void md5_finish( CMD5Contex *ctx, uint8 digest[16] );

private:
	static void md5_process( CMD5Contex *ctx, uint8 data[64] );
};

#endif

