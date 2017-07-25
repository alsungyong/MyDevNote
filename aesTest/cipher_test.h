/* ----------------------------------cipher.h---------------------------------- */

#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/ssl.h>


int encrypt_block(unsigned char* cipherText, unsigned char* plainText, 
		unsigned int plainTextLen, unsigned char* key);
int decrypt_block(unsigned char* plainText, unsigned char* cipherText, 
		unsigned int cipherTextLen, unsigned char* key);
