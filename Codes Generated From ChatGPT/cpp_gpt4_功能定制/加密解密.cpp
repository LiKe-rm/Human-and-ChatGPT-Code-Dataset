#include <openssl/evp.h>
#include <openssl/rand.h>
#include <string.h>
#include <stdio.h>

int generate_key(const char* password, const unsigned char* salt, int salt_len, int iterations,
    const EVP_CIPHER* cipher, unsigned char* key, unsigned char* iv)
{
    int key_len = EVP_CIPHER_key_length(cipher);
    int iv_len = EVP_CIPHER_iv_length(cipher);
    int ret = PKCS5_PBKDF2_HMAC_SHA1(password, strlen(password), salt, salt_len, iterations, key_len + iv_len, key);
    if (ret != 1) {
        return -1;
    }
    memcpy(iv, key + key_len, iv_len);
    return 0;
}

int encrypt_file(const char* infile, const char* outfile, const char* password)
{
    unsigned char salt[] = "abcdefg";
    int iterations = 10000;

    FILE* fin = fopen(infile, "rb");
    if (!fin) {
        return -1;
    }
    FILE* fout = fopen(outfile, "wb");
    if (!fout) {
        fclose(fin);
        return -1;
    }

    const EVP_CIPHER* cipher = EVP_aes_256_cbc();
    unsigned char key[EVP_MAX_KEY_LENGTH], iv[EVP_MAX_IV_LENGTH];
    if (generate_key(password, salt, sizeof(salt), iterations, cipher, key, iv) != 0) {
        fclose(fin);
        fclose(fout);
        return -1;
    }

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
 	  fclose(fin);
        fclose(fout);
        return -1;
    }

    if (EVP_EncryptInit_ex(ctx, cipher, NULL, key, iv) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        fclose(fin);
        fclose(fout);
        return -1;
    }

    unsigned char inbuf[1024], outbuf[1024 + EVP_MAX_BLOCK_LENGTH];
    int inlen, outlen;
    while ((inlen = fread(inbuf, 1, sizeof(inbuf), fin)) > 0) {
        if (EVP_EncryptUpdate(ctx, outbuf, &outlen, inbuf, inlen) != 1) {
            EVP_CIPHER_CTX_free(ctx);
            fclose(fin);
            fclose(fout);
            return -1;
        }
        fwrite(outbuf, 1, outlen, fout);
    }

    if (EVP_EncryptFinal_ex(ctx, outbuf, &outlen) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        fclose(fin);
        fclose(fout);
        return -1;
    }
    fwrite(outbuf, 1, outlen, fout);

    EVP_CIPHER_CTX_free(ctx);
    fclose(fin);
    fclose(fout);
    return 0;
}

int decrypt_file(const char* infile, const char* outfile, const char* password)
{
    unsigned char salt[] = "abcdefg";
    int iterations = 10000;

    FILE* fin = fopen(infile, "rb");
    if (!fin) {
        return -1;
    }
    FILE* fout = fopen(outfile, "wb");
    if (!fout) {
        fclose(fin);
        return -1;
    }

    const EVP_CIPHER* cipher = EVP_aes_256_cbc();
    unsigned char key[EVP_MAX_KEY_LENGTH], iv[EVP_MAX_IV_LENGTH];
    if (generate_key(password, salt, sizeof(salt), iterations, cipher, key, iv) != 0) {
        fclose(fin);
        fclose(fout);
        return -1;
    }

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        fclose(fin);
        fclose(fout);
        return -1;
    }

    if (EVP_DecryptInit_ex(ctx, cipher, NULL, key, iv) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        fclose(fin);
        fclose(fout);
        return -1;
    }

    unsigned char inbuf[1024 + EVP_MAX_BLOCK_LENGTH], outbuf[1024];
    int inlen, outlen;
    while ((inlen = fread(inbuf, 1, sizeof(inbuf), fin)) > 0) {
        if (EVP_DecryptUpdate(ctx, outbuf, &outlen, inbuf, inlen) != 1) {
            EVP_CIPHER_CTX_free(ctx);
            fclose(fin);
            fclose(fout);
            return -1;
        }
        fwrite(outbuf, 1, outlen, fout);
    }

    if (EVP_DecryptFinal_ex(ctx, outbuf, &outlen) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        fclose(fin);
        fclose(fout);
        return -1;
    }
    fwrite(outbuf, 1, outlen, fout);

    EVP_CIPHER_CTX_free(ctx);
    fclose(fin);
    fclose(fout);
    return 0;
}