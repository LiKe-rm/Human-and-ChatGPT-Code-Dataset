#include <iostream>
#include <string>
#include <cstring>

// 控制消息类型定义
enum CtrlMsgType {
    NETWORK_REPORT = 1,
    SHUTDOWN = 2,
};

// 网络报告消息结构体定义
struct ctrlmsg_system_netreport_t {
    int type;
    int net_id;
    int data_rate;
};

// 控制消息结构体定义
struct CtrlMessage {
    int type;
    union {
        ctrlmsg_system_netreport_t net_report;
    };
};

// 函数声明
void ctrlsys_handle_message(CtrlMessage* msg);
void ctrlsys_netreport(ctrlmsg_system_netreport_t* msg, int net_id, int data_rate);

int main() {
    CtrlMessage msg;

    // 构建网络报告消息
    ctrlsys_netreport(&msg.net_report, 1, 100);
    // 处理消息
    ctrlsys_handle_message(&msg);

    // 构建关机消息
    msg.type = SHUTDOWN;
    // 处理消息
    ctrlsys_handle_message(&msg);

    return 0;
}

void ctrlsys_handle_message(CtrlMessage* msg) {
    if (msg == nullptr) {
        std::cerr << "Error: Invalid message pointer." << std::endl;
        return;
    }

    switch (msg->type) {
        case NETWORK_REPORT: {
            std::cout << "Network report:" << std::endl;
            std::cout << "  Network ID: " << msg->net_report.net_id << std::endl;
            std::cout << "  Data rate: " << msg->net_report.data_rate << " Kbps" << std::endl;
            break;
        }
        case SHUTDOWN: {
            std::cout << "Shutting down the system." << std::endl;
            // 在这里执行关机操作
            break;
        }
        default: {
            std::cerr << "Error: Unknown message type." << std::endl;
            break;
        }
    }
}

void ctrlsys_netreport(ctrlmsg_system_netreport_t* msg, int net_id, int data_rate) {
    if (msg == nullptr) {
        std::cerr << "Error: Invalid message pointer." << std::endl;
        return;
    }

    msg->type = NETWORK_REPORT;
    msg->net_id = net_id;
    msg->data_rate = data_rate;
}
