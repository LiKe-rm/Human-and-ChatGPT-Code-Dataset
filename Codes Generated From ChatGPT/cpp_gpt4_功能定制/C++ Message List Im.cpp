#include <iostream>
#include <list>
#include <vector>

// 定义连接描述符类
class CDescriptor {
public:
    int fd; // 连接描述符
    // ... 其他成员
};

// 定义消息发送目标节点类
class CMsgListNodeServerNode {
public:
    CDescriptor *descriptor; // 连接描述符指针

    CMsgListNodeServerNode(CDescriptor *desc) : descriptor(desc) {}

    // ... 其他成员函数
};

// 定义消息节点类
class CMsgListNode {
public:
    int serialNumber; // 消息序列号
    std::string messageBody; // 消息体
    std::vector<CMsgListNodeServerNode> serverNodes; // 消息发送目标列表

    CMsgListNode(int sn, const std::string &msg) : serialNumber(sn), messageBody(msg) {}

    // 添加发送目标
    void addTarget(CDescriptor *desc) {
        serverNodes.emplace_back(desc);
    }

    // 移除发送目标
    void removeTarget(CDescriptor *desc) {
        for (auto it = serverNodes.begin(); it != serverNodes.end(); ++it) {
            if (it->descriptor == desc) {
                serverNodes.erase(it);
                break;
            }
        }
    }

    // ... 其他成员函数
};

// 定义消息列表类
class CMsgList {
public:
    std::list<CMsgListNode> msgList; // 消息列表

    // 添加消息节点
    void add(int serialNumber, const std::string &messageBody) {
        msgList.emplace_back(serialNumber, messageBody);
    }

    // 移除消息节点
    void remove(int serialNumber) {
        for (auto it = msgList.begin(); it != msgList.end(); ++it) {
            if (it->serialNumber == serialNumber) {
                msgList.erase(it);
                break;
            }
        }
    }

    // ... 其他成员函数
};

int main() {
    CMsgList msgList;
    CDescriptor descriptor1 {1};
    CDescriptor descriptor2 {2};

    // 添加消息节点
    msgList.add(1, "Hello, World!");
    msgList.add(2, "Hello, C++!");

    // 为消息节点添加发送目标
    auto &msgNode1 = msgList.msgList.front();
    msgNode1.addTarget(&descriptor1);
    msgNode1.addTarget(&descriptor2);

    auto &msgNode2 = msgList.msgList.back();
    msgNode2.addTarget(&descriptor1);

    // 移除消息节点
    msgList.remove(1);

    // ... 其他操作
    return 0;
}
