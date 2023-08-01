#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cstring>

using namespace std;

// 玩家ID结构体
struct PlayerID {
    unsigned int ipAddress; // 二进制地址
    unsigned short port; // 端口号
};

// 网络ID结构体
struct NetworkID {
    PlayerID playerID; // 所属玩家的ID
    unsigned int objectID; // 对象的本地标识符

    bool operator==(const NetworkID& other) const {
        return (playerID.ipAddress == other.playerID.ipAddress &&
            playerID.port == other.playerID.port &&
            objectID == other.objectID);
    }
};

// 转换函数，将PlayerID转换成字符串
string playerIDToString(const PlayerID& playerID) {
    string result = to_string((playerID.ipAddress >> 24) & 0xFF) + "." +
        to_string((playerID.ipAddress >> 16) & 0xFF) + "." +
        to_string((playerID.ipAddress >> 8) & 0xFF) + "." +
        to_string(playerID.ipAddress & 0xFF) + ":" +
        to_string(playerID.port);
    return result;
}

// 转换函数，将字符串转换成PlayerID
PlayerID stringToPlayerID(const string& str) {
    PlayerID playerID;
    memset(&playerID, 0, sizeof(playerID));
    int colonPos = str.find(':');
    if (colonPos != string::npos) {
        string ipAddressStr = str.substr(0, colonPos);
        string portStr = str.substr(colonPos + 1);
        int dot1Pos = ipAddressStr.find('.');
        int dot2Pos = ipAddressStr.find('.', dot1Pos + 1);
        int dot3Pos = ipAddressStr.find('.', dot2Pos + 1);
        if (dot1Pos != string::npos && dot2Pos != string::npos && dot3Pos != string::npos) {
            playerID.ipAddress = stoi(ipAddressStr.substr(0, dot1Pos)) << 24 |
                stoi(ipAddressStr.substr(dot1Pos + 1, dot2Pos - dot1Pos - 1)) << 16 |
                stoi(ipAddressStr.substr(dot2Pos + 1, dot3Pos - dot2Pos - 1)) << 8 |
                stoi(ipAddressStr.substr(dot3Pos + 1));
            playerID.port = stoi(portStr);
        }
    }
    return playerID;
}

// 网络数据包结构体
struct NetworkPacket {
    PlayerID sender; // 发送者的ID
    vector<unsigned char> data; // 数据

    NetworkPacket() {}
    NetworkPacket(const PlayerID& sender, const vector<unsigned char>& data): sender(sender), data(data) {}
};

// 网络连接接口类
class NetworkConnection {
    public:
    virtual bool sendPacket(const PlayerID& receiver, const vector<unsigned char>& data) = 0;
    virtual bool isPacketAvailable() = 0;
    virtual bool receivePacket(NetworkPacket& packet) = 0;
};

// 简单实现的网络连接类，仅用于示例
class SimpleNetworkConnection: public NetworkConnection {
    public:
    SimpleNetworkConnection() {}

    bool sendPacket(const PlayerID& receiver, const vector<unsigned char>& data) {
        cout << "Sending packet to" "player " << playerIDToString(receiver) << endl;
        return true;
    }
    bool isPacketAvailable() {
        return !mPacketQueue.empty();
    }

    bool receivePacket(NetworkPacket& packet) {
        if (mPacketQueue.empty()) {
            return false;
        }
        packet = mPacketQueue.front();
        mPacketQueue.pop();
        return true;
    }

    void addPacketToQueue(const NetworkPacket& packet) {
        mPacketQueue.push(packet);
    }
    private:
    queue<NetworkPacket> mPacketQueue;
};

// 网络对象基类
class NetworkObject {
    public:
    NetworkObject(NetworkConnection* networkConnection, const NetworkID& networkID):
        mNetworkConnection(networkConnection), mNetworkID(networkID) {}
    virtual void update() = 0;

    NetworkID getNetworkID() const {
        return mNetworkID;
    }

    void sendPacket(const vector<unsigned char>& data) {
        if (mNetworkConnection != nullptr) {
            mNetworkConnection->sendPacket(mNetworkID.playerID, data);
        }
    }
    protected:
    NetworkConnection* mNetworkConnection; // 网络连接对象
    NetworkID mNetworkID; // 网络ID
};

// 网络对象管理器，负责管理网络对象
class NetworkObjectManager {
    public:
    NetworkObjectManager(NetworkConnection* networkConnection, bool peerToPeerMode):
        mNetworkConnection(networkConnection), mPeerToPeerMode(peerToPeerMode) {}
    ~NetworkObjectManager() {
        for (auto it = mNetworkObjects.begin(); it != mNetworkObjects.end(); ++it) {
            delete it->second;
        }
    }

    void addNetworkObject(NetworkObject* networkObject) {
        NetworkID networkID = networkObject->getNetworkID();
        if (mPeerToPeerMode) {
            // 在点对点模式下，将对象的ID加上创建对象的玩家的ID，以保证对象在网络上的唯一性
            networkID.playerID = mPlayerID;
        }
        mNetworkObjects[networkID] = networkObject;
    }

    void removeNetworkObject(const NetworkID& networkID) {
        auto it = mNetworkObjects.find(networkID);
        if (it != mNetworkObjects.end()) {
            delete it->second;
            mNetworkObjects.erase(it);
        }
    }

    NetworkObject* getNetworkObject(const NetworkID& networkID) const {
        auto it = mNetworkObjects.find(networkID);
        if (it != mNetworkObjects.end()) {
            return it->second;
        }
        return nullptr;
    }

    void setPlayerID(const PlayerID& playerID) {
        mPlayerID = playerID;
    }

    void update() {
        while (mNetworkConnection->isPacketAvailable()) {
            NetworkPacket packet;
            if (mNetworkConnection->receivePacket(packet)) {
                // 处理接收到的数据包
                handlePacket(packet);
            }
        }
        // 更新所有网络对象
        for (auto it = mNetworkObjects.begin(); it != mNetworkObjects.end(); ++it) {
            it->second->update();
        }
    }
    private:
    NetworkConnection* mNetworkConnection; // 网络连接对象
    bool mPeerToPeerMode; // 是否处于点对点模式
    PlayerID mPlayerID; // 玩家ID
    map<NetworkID, NetworkObject*> mNetworkObjects; // 网络对象映射表
    void handlePacket(const NetworkPacket& packet) {
        // 查找接收者对应的网络对象
        NetworkObject* receiver = getNetworkObject(packet.sender, packet.data);
        if (receiver != nullptr) {
            // 将数据包发送给对应的网络对象
            receiver->handlePacket(packet.sender, packet.data);
        }
    }

    // 查找接收者对应的网络对象
    NetworkObject* getNetworkObject(const PlayerID& sender, const vector<unsigned char>& data) const {
        NetworkID networkID;
        memcpy(&networkID, &data[0], sizeof(networkID));
        if (mPeerToPeerMode) {
            // 在点对点模式下，将对象的ID加上创建对象的玩家的ID，以保证对象在网络上的唯一性
            networkID.playerID = sender;
        }
        return getNetworkObject(networkID);
    }
};

// 具体的网络对象类，需要实现update和handlePacket函数
class MyNetworkObject: public NetworkObject {
    public:
    MyNetworkObject(NetworkConnection* networkConnection, const NetworkID& networkID):
        NetworkObject(networkConnection, networkID) {}
    void update() override {
        // TODO: 实现具体的更新逻辑
    }

    void handlePacket(const PlayerID& sender, const vector<unsigned char>& data) override {
        // TODO: 处理接收到的数据包
    }
};

int main() {
// 创建网络连接对象
    SimpleNetworkConnection networkConnection;
    // 创建网络对象管理器
    bool peerToPeerMode = true;
    NetworkObjectManager networkObjectManager(&networkConnection, peerToPeerMode);

    // 创建玩家ID和网络ID
    PlayerID playerID;
    playerID.ipAddress = 0x7F000001; // 127.0.0.1
    playerID.port = 12345;
    NetworkID networkID;
    networkID.playerID = playerID;
    networkID.objectID = 1;

    // 创建网络对象并添加到网络对象管理器中
    MyNetworkObject* myNetworkObject = new MyNetworkObject(&networkConnection, networkID);
    networkObjectManager.addNetworkObject(myNetworkObject);

    // 设置网络对象管理器的玩家ID
    networkObjectManager.setPlayerID(playerID);

    // 模拟网络数据包的发送和接收
    vector<unsigned char> packetData;
    memcpy(&packetData[0], &networkID, sizeof(networkID));
    networkConnection.addPacketToQueue(NetworkPacket(playerID, packetData));
    networkObjectManager.update();

    return 0;
}