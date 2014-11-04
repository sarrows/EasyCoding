#include "StdAfx.h"

#include <winsock2.h>

#include "QCryptor.h"

/*
 * TEA algorithm
 */
void CQCryptor::tea_encipher(unsigned long       * const v,
                             const unsigned long * const k,
                             unsigned long       * const w)
{
	register unsigned long y = ntohl(v[0]);
	register unsigned long z = ntohl(v[1]);
	register unsigned long a = ntohl(k[0]);
	register unsigned long b = ntohl(k[1]);
	register unsigned long c = ntohl(k[2]);
	register unsigned long d = ntohl(k[3]);
	register unsigned long n = 16; 
	register unsigned long sum = 0;
	register unsigned long delta = 0x9E3779B9;/*  0x9E3779B9 - 0x100000000 = -0x61C88647 */
	
	while (n-- > 0) {
		sum += delta;
		y += ((z << 4) + a) ^ (z + sum) ^ ((z >> 5) + b);
		z += ((y << 4) + c) ^ (y + sum) ^ ((y >> 5) + d);
	}
	
	w[0] = htonl(y);
	w[1] = htonl(z);
	
	return ;
}

void CQCryptor::tea_decipher(unsigned long       * const v,
                             const unsigned long * const k,
                             unsigned long       * const w)
{
	register unsigned long y = ntohl(v[0]);
	register unsigned long z = ntohl(v[1]);
	register unsigned long a = ntohl(k[0]);
	register unsigned long b = ntohl(k[1]);
	register unsigned long c = ntohl(k[2]);
	register unsigned long d = ntohl(k[3]);
	register unsigned long n = 16;
	register unsigned long sum = 0xE3779B90;  // why this ? must be related with n value
	register unsigned long delta = 0x9E3779B9;
	
	/* sum = delta<<5, in general sum = delta * n */
	while (n-- > 0) {
		z -= ((y << 4) + c) ^ (y + sum) ^ ((y >> 5) + d);
		y -= ((z << 4) + a) ^ (z + sum) ^ ((z >> 5) + b);
		sum -= delta;
	}
	
	w[0] = htonl(y);
	w[1] = htonl(z);
	
	return;
}



/*
 * QQ data encrypt routine.
 */


int CQCryptor::encrypt(unsigned char * in,
                       int             in_len,
                       unsigned char * key,
                       unsigned char * out,
                       int           * out_len)
{
	unsigned char plain1[8];
	unsigned char plain2[8];
	int n = 0;
	unsigned char *crypted1 = NULL;
	unsigned char *crypted2 = NULL;
	int padding = 0;
	int i = 0;
	int count = 0;
	unsigned char *p = NULL;
	
	/*header padding*/
	n = (in_len + 0x0a)%8;
	
	if(n) {
		n = 8 - n;
	}
	
	memset(plain1,0, sizeof(plain1));
	memset(plain2,0, sizeof(plain2));
	
	/* byte 0 */
	plain1[0] = ( rand()&0xf8 )|n;
	
	memset(plain1 + 1,rand()&0xff,n++);
	
	crypted1 = crypted2 = out;
	
	padding = 1;
	
	while(padding <= 2) {
		if(n<8){
			plain1[n++] = rand() & 0xff;
			padding++;
		}
		if(n == 8) {
			/*encrypting use TEA 16*/
			for(i=0;i<8;i++){
				plain1[i]^=plain2[i];
			}
			
			tea_encipher((unsigned long *)plain1,(unsigned long *)key,(unsigned long *)crypted1);
			for(i=0;i<8;i++){
				crypted1[i]^=plain2[i];
			}
			
			memcpy(plain2,plain1,8);
			crypted2 = crypted1;
			crypted1 += 8;   
			count += 8;    
			n = 0;
		}
	}
	
	
	p = in;
	
	while(in_len>0) {
		
		if(n < 8) {
			plain1[n++] = *(p++);
			in_len--;
		}
		if(n == 8) {
			
			for(i=0;i<8;i++){
				plain1[i] ^= crypted2[i];
			}
			
			tea_encipher((unsigned long *)plain1,(unsigned long*)key,(unsigned long*)crypted1);
			for(i=0;i<8;i++){
				crypted1[i] ^= plain2[i];
			}
			
			memcpy(plain2,plain1,8);
			crypted2 = crypted1;
			crypted1 += 8;
			count += 8; 
			n = 0;
		}
	}
	
	
	padding = 1;
	
	while(padding <= 7) { 
		
		if(n < 8) {
			plain1[n++] = 0x00;
			padding++;
		}
		
		if(n==8) {
			for(i=0;i<8;i++){
				plain1[i] ^= crypted2[i];
			}
			
			tea_encipher((unsigned long *)plain1,(unsigned long*)key,(unsigned long*)crypted1);
			for(i=0;i<8;i++){
				crypted1[i] ^= plain2[i];
			}
			
			memcpy(plain2,plain1,8);
			crypted2 = crypted1;
			crypted1 += 8;
			count+=8; 
			n = 0;
		}
	}
	
	
	*out_len = count;
	
	return 0;
}



/*
 * 0 = successfully
 * non-zero failed.
 */
int CQCryptor::decrypt(unsigned char * in,
                       int             in_len,
                       unsigned char * key,
                       unsigned char * out,
                       int           * out_len)
{
	unsigned char decrypted[8];
	unsigned char tmp[8];
	unsigned char *crypt1;
	unsigned char *crypt2;
	unsigned char *p = NULL;
	int count = 0;
	int i = 0;
	int n = 0;
	int padding = 0;
	int context_start = 0;
	int error = 0;
	
	
	/*at least 16 bytes and %8 == 0*/
	if( (in_len%8) || (in_len<16)){
		return -1;
	}
	
	/*decrypting header info.*/
	tea_decipher((unsigned long*)in,(unsigned long*)key,(unsigned long*)decrypted);
	
	n = decrypted[0]&0x7;
	
	
	
	/*plain text length.*/
	count = in_len - n - 10;
	
	if( (*out_len) < count || count < 0){
		return -1;
	}
	
	memset(tmp, 0, sizeof(tmp));
	
	crypt2 = tmp;
	
	*out_len = count;
	
	/*real data.*/
	crypt1 = in + 8; 
	/*context is at the second 8 byte*/
	context_start = 8;  
	/*start of paddng stuff*/
	n++; 
	
	padding = 1;     
	
	
	/*2 bytes padding stuff in header*/
	while (padding <= 2) {
		if(n < 8) { 
			n++;
			padding++;
		}
		if(n== 8) {
			crypt2 = in;
			error = 0;
			
			for(i = 0;i<8;i++) {
				if(context_start + i >= in_len){
					n = i;
					error = 1;
					break;
				}
				decrypted[i]^=crypt1[i];
			}
			
			if(error){
				continue;
			}
			
			tea_decipher((unsigned long *)decrypted,(unsigned long*)key,(unsigned long *)decrypted);
			context_start += 8;
			crypt1 += 8;
			n = 0;
		}
	}                   
	
	
	p = out;
	
	while(count!=0) {
		if(n<8){
			*p = crypt2[n]^decrypted[n];
			p++;
			count--;
			n++;
		}
		if(n == 8) {
			crypt2 = crypt1 - 8;
			error = 0;
			for(i = 0;i<8;i++) {
				if(context_start + i >= in_len){
					n = i;
					error = 1;
					break;
				}
				decrypted[i]^=crypt1[i];
			}
			
			if(error){
				continue;
			}
			
			tea_decipher((unsigned long *)decrypted,(unsigned long*)key,(unsigned long *)decrypted);
			context_start += 8;
			crypt1 += 8;
			n = 0;
		}
	}              
	
	
	for(padding=1;padding<8;padding++) {
		if(n<8){
			if(crypt2[n]^decrypted[n]){
				return -1;
			}
			n++;
		}
		if(n == 8) {
			crypt2 = crypt1;
			error = 0;
			for(i = 0;i<8;i++) {
				if(context_start + i >= in_len){
					n = i;
					error = 1;
					break;
				}
				decrypted[i]^=crypt1[i];
			}
			
			if(error){
				continue;
			}
			
			tea_decipher((unsigned long *)decrypted,(unsigned long*)key,(unsigned long *)decrypted);
			context_start += 8;
			crypt1 += 8;
			n = 0;
		}
	} 
	
	return 0;
}