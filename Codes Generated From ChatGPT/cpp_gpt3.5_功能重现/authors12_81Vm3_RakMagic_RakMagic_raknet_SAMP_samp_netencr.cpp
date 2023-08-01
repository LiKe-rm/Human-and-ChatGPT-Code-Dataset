#include <iostream>
#include <cstring>

using namespace std;

const int MAX_BUF_SIZE = 1024;
const unsigned char sampEncrTable[] = { 0x8D, 0xD3, 0x56, 0xC8, 0x11, 0x7E, 0xB2, 0x6F, 0x34, 0x8B, 0x9A, 0x05, 0xE0, 0xB4, 0x1E, 0x98 };
const unsigned char sampDecrTable[] = { 0xA8, 0x0B, 0xED, 0x54, 0x3C, 0x7A, 0x91, 0x1D, 0x20, 0x2F, 0xB8, 0x9E, 0x1F, 0xD7, 0x42, 0x6C };

// 将内存内容转储成十六进制字符串
void DumpMem(const void* ptr, int len)
{
    const unsigned char* p = (const unsigned char*)ptr;
    for (int i = 0; i < len; i++)
    {
        cout << hex << (int)p[i] << " ";
    }
    cout << endl;
}

// 加密数据
void EncryptData(unsigned char* buf, int size)
{
    for (int i = 0; i < size; i++)
    {
        buf[i] ^= sampEncrTable[i % sizeof(sampEncrTable)];
    }
}

// 解密数据
void DecryptData(unsigned char* buf, int size)
{
    for (int i = 0; i < size; i++)
    {
        buf[i] ^= sampDecrTable[i % sizeof(sampDecrTable)];
    }
}

int main()
{
    // 假设有一段数据需要加密
    unsigned char buf[MAX_BUF_SIZE] = "Hello, World!";
    int size = strlen((const char*)buf);

    // 输出原始数据
    cout << "Original Data: ";
    DumpMem(buf, size);

    // 加密数据
    EncryptData(buf, size);

    // 输出加密后的数据
    cout << "Encrypted Data: ";
    DumpMem(buf, size);

    // 解密数据
    DecryptData(buf, size);

    // 输出解密后的数据
    cout << "Decrypted Data: ";
    DumpMem(buf, size);

    return 0;
}
