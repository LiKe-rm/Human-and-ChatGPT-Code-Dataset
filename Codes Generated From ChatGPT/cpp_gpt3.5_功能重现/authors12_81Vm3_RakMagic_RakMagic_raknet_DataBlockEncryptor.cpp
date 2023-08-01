#include <iostream>
#include <cstring>
#include <openssl/aes.h>
#include <ctime>

using namespace std;

// ���ܺ���
void encrypt(unsigned char *input, int input_len, unsigned char *output, unsigned char *key, bool chain = false) {
    // ������Ҫ�����ֽ���
    int padding = AES_BLOCK_SIZE - (input_len % AES_BLOCK_SIZE);
    if (padding == 0) {
        padding = AES_BLOCK_SIZE;
    }

    // ��������ֽ�
    srand((unsigned int)time(NULL));
    unsigned char rand_byte = rand() % 256;

    // ������ֽ������뵽����ֽڵĸ�4λ
    rand_byte = rand_byte & 0xF0;
    rand_byte = rand_byte | (unsigned char)padding;

    // ������ֽ���ӵ�������ݵ�ͷ��
    output[0] = rand_byte;

    // �������ֽ�
    for (int i = 1; i <= padding; i++) {
        output[i] = rand() % 256;
    }

    // ִ�� AES ����
    AES_KEY aes_key;
    AES_set_encrypt_key(key, 128, &aes_key);
    if (chain) {
        for (int i = input_len - AES_BLOCK_SIZE; i >= 0; i -= AES_BLOCK_SIZE) {
            AES_encrypt(&input[i], &output[i + padding + 1], &aes_key);
        }
    } else {
        for (int i = 0; i < input_len; i += AES_BLOCK_SIZE) {
            AES_encrypt(&input[i], &output[i + padding + 1], &aes_key);
        }
    }
}

// ���ܺ���
bool decrypt(unsigned char *input, int input_len, unsigned char *output, unsigned char *key) {
    // ִ�� AES ����
    int padding = input[0] & 0xF;
    AES_KEY aes_key;
    AES_set_decrypt_key(key, 128, &aes_key);
    for (int i = 1; i < input_len; i += AES_BLOCK_SIZE) {
        AES_decrypt(&input[i], &output[i - 1], &aes_key);
    }

    // ͨ������������ܲ����Լ�����ֽ����Ƶ�����������ĳ���
    int data_len = input_len - padding - 1;

    // ����Ƿ�������ݱ����ĵ����
    for (int i = 0; i < padding; i++) {
        if (input[data_len + i + 1] != input[1 + i]) {
            return false;
        }
    }

    return true;
}

int main() {
    // ��������
    unsigned char input[] = "Hello, world!";
    unsigned char key[] = "0123456789abcdef";
    unsigned char encrypted[1024];
    unsigned char decrypted[1024];

    // ����
    encrypt(input, strlen((char *)input), encrypted, key);

    // ����
    bool success = decrypt(encrypted, sizeof(encrypted), decrypted, key);
    if (success) {
        cout << "Decrypted message: " << decrypted << endl;
    } else {
        cout << "Decryption failed." << endl;
    }

    return 0;
}
