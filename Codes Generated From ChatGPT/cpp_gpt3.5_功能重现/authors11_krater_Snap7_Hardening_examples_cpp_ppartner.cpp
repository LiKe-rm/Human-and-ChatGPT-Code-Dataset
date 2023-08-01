#include <snap7.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 回调函数，用于接收数据
void RecvCallback (void* usrPtr, const uint8_t* pData, int Size)
{
    printf("Received %d bytes:\n", Size);
    hexdump(pData, Size);
}

// 打印十六进制和 ASCII 码形式的数据
void hexdump(const void* data, size_t size)
{
    const unsigned char *p = (const unsigned char*)data;
    char ascii[17];
    size_t i, j;
    ascii[16] = '\0';
    for (i = 0; i < size; ++i) {
        printf("%02X ", p[i]);
        if (isprint(p[i]))
            ascii[i % 16] = p[i];
        else
            ascii[i % 16] = '.';
        if ((i+1) % 8 == 0 || i+1 == size) {
            printf(" ");
            if ((i+1) % 16 == 0) {
                printf("|  %s \n", ascii);
            } else if (i+1 == size) {
                ascii[(i+1) % 16] = '\0';
                if ((i+1) % 16 <= 8)
                    printf(" ");
                for (j = (i+1) % 16; j < 16; ++j)
                    printf("   ");
                printf("|  %s \n", ascii);
            }
        }
    }
}

int main(int argc, char** argv)
{
    TS7Partner* Partner = NULL;
    int Result;

    if (argc != 2) {
        printf("Usage: %s <local port>\n", argv[0]);
        return 1;
    }

    // 创建被动合作伙伴对象并初始化为被动模式
    Partner = new TS7Partner();
    Result = Partner->SetAs(PA_TCP);
    if (Result != 0) {
        printf("Failed to set as passive partner: %d\n", Result);
        return 1;
    }

    // 设置回调函数
    Partner->SetReadCallback(RecvCallback, NULL);

    // 启动被动合作伙伴并等待数据
    Result = Partner->StartTo(argv[1], 10, 5000, 5000);
    if (Result != 0) {
        printf("Failed to start passive partner: %d\n", Result);
        return 1;
    }

    printf("Press Enter to stop...\n");
    getchar();

    // 停止被动合作伙伴并退出
    Partner->Stop();
    delete Partner;
    return 0;
}
