#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

class SerialProtocol {
private:
    // 协议参数定义
    static const char PROTOCOL_HEADER = 0xAA;  // 协议头
    static const char PROTOCOL_TAIL = 0x55;    // 协议尾
    static const int ADDRESS_LENGTH = 2;       // 地址长度

    // 发送数据 buffer
    std::vector<char> sendBuffer;
    // 接收数据 buffer
    std::vector<char> recvBuffer;

    // 自身地址
    std::vector<char> myAddress;

    // 目标地址
    std::vector<char> destAddress;

    // 记录最近接收到数据的发送端地址
    std::vector<char> lastSenderAddress;

    // 清空接收数据 buffer
    void clearRecvBuffer() {
        std::fill(recvBuffer.begin(), recvBuffer.end(), 0);
    }

public:
    // 构造函数
    SerialProtocol(SerialProtocol* self) {
        sendBuffer.clear();
        recvBuffer.clear();
        myAddress.resize(ADDRESS_LENGTH, 0);
        destAddress.resize(ADDRESS_LENGTH, 0);
        lastSenderAddress.resize(ADDRESS_LENGTH, 0);
        memcpy(&myAddress[0], self, sizeof(self));
    }

    // 析构函数
    ~SerialProtocol() {
        sendBuffer.clear();
        recvBuffer.clear();
    }

    // 解析接收到的数据
    std::vector<char> parseReceivedData() {
        std::vector<char> data;
        // 查找协议头
        std::vector<char>::iterator headerPos = std::find(recvBuffer.begin(), recvBuffer.end(), PROTOCOL_HEADER);
        if (headerPos != recvBuffer.end()) {
            // 查找协议尾
            std::vector<char>::iterator tailPos = std::find(headerPos, recvBuffer.end(), PROTOCOL_TAIL);
            if (tailPos != recvBuffer.end()) {
                // 获取地址信息
                std::vector<char>::iterator addrPos = headerPos + 1;
                std::vector<char> senderAddress(addrPos, addrPos + ADDRESS_LENGTH);
                lastSenderAddress = senderAddress;
                // 获取数据信息
                std::vector<char>::iterator dataPos = addrPos + ADDRESS_LENGTH;
                data.resize(tailPos - dataPos);
                memcpy(&data[0], &dataPos[0], data.size());
                // 清空接收 buffer
                clearRecvBuffer();
            }
        }
        return data;
    }

    // 初始化发送数据
    void initializeSendData(const char* data, int length) {
        sendBuffer.clear();
        sendBuffer.push_back(PROTOCOL_HEADER);
        sendBuffer.insert(sendBuffer.end(), destAddress.begin(), destAddress.end());
        sendBuffer.insert(sendBuffer.end(), myAddress.begin(), myAddress.end());
        sendBuffer.insert(sendBuffer.end(), data, data + length);
        sendBuffer.push_back(PROTOCOL_TAIL);
    }

    // 发送数据
    bool sendData() {
        bool result = false;
        // 发送数据
        // ...
        // 发送成功后清空发送 buffer
        if (result) {
            sendBuffer.clear();
        }
        return result;
    }

    // 设定通信目标的地址
    void setDestinationAddress(const char* address) {
        memcpy(&destAddress[0], address, ADDRESS_LENGTH);
    }

    // 添加自身的地址
    void addMyAddress(const char* address) {
        std::vector<char> addr(ADDRESS_LENGTH, 0);
        memcpy(&addr[0], address, ADDRESS_LENGTH);
        myAddress.insert(myAddress.end(), addr.begin(), addr.end());
    }

    // 获取最近接收到数据的发送端地址
    std::vector<char> getLastSenderAddress() {
        return lastSenderAddress;
    }
};

