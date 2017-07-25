#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/aes.h>


/* AES Encrypt Process */
int encrypt_block(unsigned char* cipherText, unsigned char* plainText, unsigned char* key)
{
	AES_KEY encKey;

	if (AES_set_encrypt_key(key, 128, &encKey) < 0)
		return -1;
	AES_encrypt(plainText, cipherText, &encKey);
	return 0;
}


/* AES Decrypt Process */
int decrypt_block(unsigned char* cipherText, unsigned char* plainText, unsigned char* key)
{
	AES_KEY decKey;

	if (AES_set_decrypt_key(key, 128, &decKey) < 0)
		return -1;
	AES_decrypt(cipherText, plainText, &decKey);
	return 0;
}


int main()
{
	unsigned char *cipherText = (unsigned char*)malloc(sizeof(unsigned char) * 1024);
	unsigned char *plainText = (unsigned char*)malloc(sizeof(unsigned char) * 1024);
	char *key = "ABCsdf2asdf", *key2 = "12345678901";
	int ret = 0;

	strcpy((char*)plainText, "This is Test Cipher...!");

	printf("plainText = %s\nlengths = %zu\n", plainText, strlen(plainText));
	ret = encrypt_block(cipherText, plainText, (unsigned char*)key);
	if( ret < 0 )
	{
		printf("encrypt_block is fail\n");
		return -1;
	}
	printf("cipher= %s\nlengths = %zu\n", cipherText, strlen(cipherText));

	ret = decrypt_block(cipherText, plainText, (unsigned char*)key);
	if( ret < 0 )
	{
		printf("decrypt_block is fail\n");
		return -1;
	}

	return 0;
}
