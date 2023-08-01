#include "snap7.h"
#include <iostream>

// 定义变量和数据块
uint8_t db1_data[100];
uint8_t db2_data[200];
uint8_t db3_data[300];

void EventCallBack(uint16_t Event, uint16_t Reserved, void* UserData)
{
    std::cout << "Event: " << Event << std::endl;
}

int ReadEventCallBack(uint32_t UserData, uint8_t* pBuffer, int Size)
{
    // 填充数据块
    switch (UserData) {
        case 1:
            memcpy(pBuffer, db1_data, Size);
            break;
        case 2:
            memcpy(pBuffer, db2_data, Size);
            break;
        case 3:
            memcpy(pBuffer, db3_data, Size);
            break;
        default:
            return -1;
    }
    return 0;
}

int main()
{
    // 创建服务器对象
    TS7Server server = TS7Server();

    // 注册三个数据块
    server.RegisterArea(S7AreaDB, 1, db1_data, sizeof(db1_data));
    server.RegisterArea(S7AreaDB, 2, db2_data, sizeof(db2_data));
    server.RegisterArea(S7AreaDB, 3, db3_data, sizeof(db3_data));

    // 设置回调函数和事件掩码
    server.SetEventsMask(S7ServerMaskAll);
    server.SetEventCallback(EventCallBack, NULL);
    server.SetReadEventCallback(ReadEventCallBack, NULL);

    // 启动服务器并等待用户输入
    server.Start();
    std::cout << "Server started. Press any key to stop." << std::endl;
    getchar();
    server.Stop();

    return 0;
}
