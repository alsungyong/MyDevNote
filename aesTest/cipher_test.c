#include <stdio.h>
#include "cipher_test.h"

int encrypt_block(unsigned char* cipherText, unsigned char* plainText, unsigned int plainTextLen, unsigned char* key);
int decrypt_block(unsigned char* plainText, unsigned char* cipherText, unsigned int cipherTextLen, unsigned char* key);


int main(void) 
{
	unsigned char* cipherText = (unsigned char*)malloc(sizeof(unsigned char) * 1024);
	unsigned char* plainText = (unsigned char*)malloc(sizeof(unsigned char) * 1024);
	char* key = "ABCsdf2asdf", *key2 = "12345678901";
	int length = 0;

	strcpy((char*)plainText, "This is Test Cipher...!");

	printf("plainText = %s\nlengths = %zu\n", plainText, strlen(plainText));
	length = encrypt_block(cipherText, plainText, strlen((char*)plainText),(unsigned char*)key);
	printf("After Encrypt : %s, %d\n", cipherText, length);
	printf("=======================================\n");
	printf("=======================================\n");
	length = decrypt_block(plainText, cipherText, strlen((char*)cipherText), (unsigned char*)key);
	//length = decrypt_block(plainText, cipherText, strlen((char*)cipherText), (unsigned char*)key2);
	plainText[length] = '\0';
	printf("After Decrypt : %s\nlengths = %zu\n", plainText, strlen(plainText));

	return 0;
}


/*	AES Encrypt Process	*/
int encrypt_block(unsigned char* cipherText, unsigned char* plainText, unsigned int plainTextLen, unsigned char* key)
{
	EVP_CIPHER_CTX *ctx = (EVP_CIPHER_CTX*)malloc(sizeof(EVP_CIPHER_CTX));
	int addLen = 0, orgLen = 0;
	unsigned long err = 0;

	ERR_load_crypto_strings();
	EVP_CIPHER_CTX_init(ctx);

	if(EVP_EncryptInit(ctx, EVP_aes_128_cbc(), key, NULL) != 1) {
		err = ERR_get_error();
		printf("ERR : EVP_Encrypt() - %s\n", ERR_error_string(err, NULL));
		return -1;
	}

	if(EVP_EncryptUpdate(ctx, cipherText, &orgLen, plainText, plainTextLen) != 1) {
		err = ERR_get_error();
		printf("ERR : EVP_EncryptUpdate() - %s\n", ERR_error_string(err, NULL));
		return -1;
	}


	if (EVP_EncryptFinal(ctx, cipherText + orgLen, &addLen) != 1) {
		err = ERR_get_error();
		printf("ERR: EVP_EncryptFinal() - %s\n", ERR_error_string (err, NULL));
		return -1;
	}

	EVP_CIPHER_CTX_cleanup(ctx);
	ERR_free_strings();
	return addLen + orgLen;
}

/*	AES Decrypt Process	*/
int decrypt_block(unsigned char* plainText, unsigned char* cipherText, unsigned int cipherTextLen, unsigned char* key)
{
	EVP_CIPHER_CTX *ctx = (EVP_CIPHER_CTX*)malloc(sizeof(EVP_CIPHER_CTX));
	unsigned long err = 0;
	int toLen = 0, outLen = 0;
	int ret = 0;

	ERR_load_crypto_strings();
	EVP_CIPHER_CTX_init(ctx);

	if (EVP_DecryptInit(ctx, EVP_aes_128_cbc(), key, NULL) != 1) {
		err = ERR_get_error();
		printf("ERR: EVP_DecryptInit() - %s\n", ERR_error_string (err, NULL));
		return -1;
	}

	if (EVP_DecryptUpdate(ctx, plainText, &toLen, cipherText, cipherTextLen) != 1) {
		err = ERR_get_error();  
		printf("ERR: EVP_DecryptUpdate() - %s\n", ERR_error_string (err, NULL));
		return -1;
	}

	if (EVP_DecryptFinal(ctx, &plainText[toLen], &outLen) != 1) {
		err = ERR_get_error();
		printf("ERR: EVP_DecryptFinal() - %s\n", ERR_error_string (err, NULL));
		return -1;
	}

	EVP_CIPHER_CTX_cleanup(ctx);
	ERR_free_strings();

	ret = toLen + outLen;
	return ret;
}
