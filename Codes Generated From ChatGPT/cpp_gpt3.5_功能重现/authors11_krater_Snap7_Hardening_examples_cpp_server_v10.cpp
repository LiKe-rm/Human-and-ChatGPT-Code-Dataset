#include <iostream>
#include <cstring>
#include <snap7/snap7.h>

using namespace std;

// 事件回调函数，用于显示日志
void eventCallback(S7Object server, int event, void *arg, int /*size*/) {
    if (event == SrvEvent_ReadData) {
        cout << "Client requested data" << endl;
    }
}

int main() {
    // 初始化Snap7库
    Snap7Client* client = new Snap7Client();
    S7Object server = Snap7Server();
    int result = Cli_Create(client);
    result = Srv_Create(server);

    // 注册3个数据块
    result = Srv_RegisterArea(server, SrvAreaDB, 1, DB1);
    result = Srv_RegisterArea(server, SrvAreaDB, 2, DB2);
    result = Srv_RegisterArea(server, SrvAreaDB, 3, DB3);

    // 设置事件回调函数
    Srv_SetEventsCallback(server, eventCallback, NULL);

    // 在默认适配器上启动服务器
    result = Srv_Start(server);

    // 等待输入以终止服务器
    cout << "Press Enter to stop server." << endl;
    getchar();

    // 停止服务器并清理资源
    Srv_Stop(server);
    Srv_Destroy(server);
    Cli_Destroy(client);

    return 0;
}
