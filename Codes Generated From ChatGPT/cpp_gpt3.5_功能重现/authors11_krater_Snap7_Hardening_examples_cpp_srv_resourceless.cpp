#include <iostream>
#include <snap7/s7.h>

// 回调函数，用于读写数据
int S7API my_readwrite_callback(void *usrPtr, int opCode, int *pDataLen, unsigned char *pData)
{
    // 打印区域、起始地址和数据大小
    std::cout << "Callback: opCode=" << opCode << ", pDataLen=" << *pDataLen << std::endl;
    // 读取或写入指定的数据
    // 这里可以根据 opCode 和 usrPtr 进行不同的操作，比如读取或写入 PLC 的数据
    // 这里只是简单地将数据打印出来
    hexdump(pData, *pDataLen);
    return 0;
}

// 打印数据的十六进制和 ASCII 格式
void hexdump(const unsigned char *buf, int len)
{
    std::cout << "Hexdump:" << std::endl;
    int i, j;
    for (i = 0; i < len; i += 16)
    {
        std::printf("%04X: ", i);
        for (j = 0; j < 16; j++)
        {
            if (i + j < len)
                std::printf("%02X ", buf[i + j]);
            else
                std::printf("   ");
        }
        std::printf(" ");
        for (j = 0; j < 16; j++)
        {
            if (i + j < len)
                std::printf("%c", isprint(buf[i + j]) ? buf[i + j] : '.');
            else
                std::printf(" ");
        }
        std::printf("\n");
    }
}

int main()
{
    // 创建一个 TS7Server 对象
    TS7Server *Server = new TS7Server();
    
    // 设置读写回调函数
    Server->SetReadCallback(my_readwrite_callback, nullptr);
    Server->SetWriteCallback(my_readwrite_callback, nullptr);
    
    // 设置事件回调函数
    Server->SetEventCallback([](void *usrPtr, const TS7ServerEvent *Event) {
        // 打印事件类型和数据
        std::cout << "Event: Code=" << Event->Code << ", Param=" << Event->Param << std::endl;
    }, nullptr);
    
    // 启动服务器
    if (Server->Start() != 0)
    {
        std::cerr << "Error: " << Server->ErrorText() << std::endl;
        delete Server;
        return 1;
    }
    
    // 等待键盘输入结束程序
    std::cout << "Server started. Press any key to stop." << std::endl;
    std::cin.get();
    
    // 停止并删除服务器对象
    Server->Stop();
    delete Server;
    
    return 0;
}
