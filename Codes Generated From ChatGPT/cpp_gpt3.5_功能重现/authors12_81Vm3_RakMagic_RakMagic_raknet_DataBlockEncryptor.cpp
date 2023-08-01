#include <iostream>
#include <cstring>
#include <openssl/aes.h>
#include <ctime>

using namespace std;

// 加密函数
void encrypt(unsigned char *input, int input_len, unsigned char *output, unsigned char *key, bool chain = false) {
    // 计算需要填充的字节数
    int padding = AES_BLOCK_SIZE - (input_len % AES_BLOCK_SIZE);
    if (padding == 0) {
        padding = AES_BLOCK_SIZE;
    }

    // 生成随机字节
    srand((unsigned int)time(NULL));
    unsigned char rand_byte = rand() % 256;

    // 将填充字节数编码到随机字节的高4位
    rand_byte = rand_byte & 0xF0;
    rand_byte = rand_byte | (unsigned char)padding;

    // 将随机字节添加到输出数据的头部
    output[0] = rand_byte;

    // 添加填充字节
    for (int i = 1; i <= padding; i++) {
        output[i] = rand() % 256;
    }

    // 执行 AES 加密
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

// 解密函数
bool decrypt(unsigned char *input, int input_len, unsigned char *output, unsigned char *key) {
    // 执行 AES 解密
    int padding = input[0] & 0xF;
    AES_KEY aes_key;
    AES_set_decrypt_key(key, 128, &aes_key);
    for (int i = 1; i < input_len; i += AES_BLOCK_SIZE) {
        AES_decrypt(&input[i], &output[i - 1], &aes_key);
    }

    // 通过反向的链加密操作以及填充字节数推导出数据区域的长度
    int data_len = input_len - padding - 1;

    // 检查是否存在数据被更改的情况
    for (int i = 0; i < padding; i++) {
        if (input[data_len + i + 1] != input[1 + i]) {
            return false;
        }
    }

    return true;
}

int main() {
    // 测试数据
    unsigned char input[] = "Hello, world!";
    unsigned char key[] = "0123456789abcdef";
    unsigned char encrypted[1024];
    unsigned char decrypted[1024];

    // 加密
    encrypt(input, strlen((char *)input), encrypted, key);

    // 解密
    bool success = decrypt(encrypted, sizeof(encrypted), decrypted, key);
    if (success) {
        cout << "Decrypted message: " << decrypted << endl;
    } else {
        cout << "Decryption failed." << endl;
    }

    return 0;
}
