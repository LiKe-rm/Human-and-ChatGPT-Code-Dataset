#include <iostream>
#include <string>
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/filters.h>

using namespace std;
using namespace CryptoPP;

// AES128加密
void AES128Encrypt(byte *key, byte *iv, byte *plaintext, size_t plaintextLength, byte *ciphertext)
{
    // TODO: 实现AES128加密
}

// AES128解密
void AES128Decrypt(byte *key, byte *iv, byte *ciphertext, size_t ciphertextLength, byte *plaintext)
{
    // TODO: 实现AES128解密
}

// AES256加密
void AES256Encrypt(byte *key, byte *iv, byte *plaintext, size_t plaintextLength, byte *ciphertext)
{
    // TODO: 实现AES256加密
}

// AES256解密
void AES256Decrypt(byte *key, byte *iv, byte *ciphertext, size_t ciphertextLength, byte *plaintext)
{
    // TODO: 实现AES256解密
}

// CBC加密
void CBCEncrypt(byte *key, byte *iv, byte *plaintext, size_t plaintextLength, byte *ciphertext)
{
    CBC_Mode<AES>::Encryption encryptor(key, AES::DEFAULT_KEYLENGTH, iv);
    ArraySource(plaintext, plaintextLength, true, new StreamTransformationFilter(encryptor, new ArraySink(ciphertext, plaintextLength)));
}

// CBC解密
void CBCDecrypt(byte *key, byte *iv, byte *ciphertext, size_t ciphertextLength, byte *plaintext)
{
    CBC_Mode<AES>::Decryption decryptor(key, AES::DEFAULT_KEYLENGTH, iv);
    ArraySource(ciphertext, ciphertextLength, true, new StreamTransformationFilter(decryptor, new ArraySink(plaintext, ciphertextLength)));
}

// AES128 CBC加密
void AES128CBCEncrypt(byte *key, byte *iv, byte *plaintext, size_t plaintextLength, byte *ciphertext)
{
    // TODO: 实现AES128 CBC加密
}

// AES128 CBC解密
void AES128CBCDecrypt(byte *key, byte *iv, byte *ciphertext, size_t ciphertextLength, byte *plaintext)
{
    // TODO: 实现AES128 CBC解密
}

// AES256 CBC加密
void AES256CBCEncrypt(byte *key, byte *iv, byte *plaintext, size_t plaintextLength, byte *ciphertext)
{
    // TODO: 实现AES256 CBC加密
}

// AES256 CBC解密
void AES256CBCDecrypt(byte *key, byte *iv, byte *ciphertext, size_t ciphertextLength, byte *plaintext)
{
    // TODO: 实现AES256 CBC解密
}

int main()
{
    // TODO: 编写测试代码

    return 0;
}
