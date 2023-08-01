#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cstring>

using namespace std;

// ���ID�ṹ��
struct PlayerID {
    unsigned int ipAddress; // �����Ƶ�ַ
    unsigned short port; // �˿ں�
};

// ����ID�ṹ��
struct NetworkID {
    PlayerID playerID; // ������ҵ�ID
    unsigned int objectID; // ����ı��ر�ʶ��

    bool operator==(const NetworkID& other) const {
        return (playerID.ipAddress == other.playerID.ipAddress &&
            playerID.port == other.playerID.port &&
            objectID == other.objectID);
    }
};

// ת����������PlayerIDת�����ַ���
string playerIDToString(const PlayerID& playerID) {
    string result = to_string((playerID.ipAddress >> 24) & 0xFF) + "." +
        to_string((playerID.ipAddress >> 16) & 0xFF) + "." +
        to_string((playerID.ipAddress >> 8) & 0xFF) + "." +
        to_string(playerID.ipAddress & 0xFF) + ":" +
        to_string(playerID.port);
    return result;
}

// ת�����������ַ���ת����PlayerID
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

// �������ݰ��ṹ��
struct NetworkPacket {
    PlayerID sender; // �����ߵ�ID
    vector<unsigned char> data; // ����

    NetworkPacket() {}
    NetworkPacket(const PlayerID& sender, const vector<unsigned char>& data): sender(sender), data(data) {}
};

// �������ӽӿ���
class NetworkConnection {
    public:
    virtual bool sendPacket(const PlayerID& receiver, const vector<unsigned char>& data) = 0;
    virtual bool isPacketAvailable() = 0;
    virtual bool receivePacket(NetworkPacket& packet) = 0;
};

// ��ʵ�ֵ����������࣬������ʾ��
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

// ����������
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
    NetworkConnection* mNetworkConnection; // �������Ӷ���
    NetworkID mNetworkID; // ����ID
};

// ����������������������������
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
            // �ڵ�Ե�ģʽ�£��������ID���ϴ����������ҵ�ID���Ա�֤�����������ϵ�Ψһ��
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
                // ������յ������ݰ�
                handlePacket(packet);
            }
        }
        // ���������������
        for (auto it = mNetworkObjects.begin(); it != mNetworkObjects.end(); ++it) {
            it->second->update();
        }
    }
    private:
    NetworkConnection* mNetworkConnection; // �������Ӷ���
    bool mPeerToPeerMode; // �Ƿ��ڵ�Ե�ģʽ
    PlayerID mPlayerID; // ���ID
    map<NetworkID, NetworkObject*> mNetworkObjects; // �������ӳ���
    void handlePacket(const NetworkPacket& packet) {
        // ���ҽ����߶�Ӧ���������
        NetworkObject* receiver = getNetworkObject(packet.sender, packet.data);
        if (receiver != nullptr) {
            // �����ݰ����͸���Ӧ���������
            receiver->handlePacket(packet.sender, packet.data);
        }
    }

    // ���ҽ����߶�Ӧ���������
    NetworkObject* getNetworkObject(const PlayerID& sender, const vector<unsigned char>& data) const {
        NetworkID networkID;
        memcpy(&networkID, &data[0], sizeof(networkID));
        if (mPeerToPeerMode) {
            // �ڵ�Ե�ģʽ�£��������ID���ϴ����������ҵ�ID���Ա�֤�����������ϵ�Ψһ��
            networkID.playerID = sender;
        }
        return getNetworkObject(networkID);
    }
};

// �������������࣬��Ҫʵ��update��handlePacket����
class MyNetworkObject: public NetworkObject {
    public:
    MyNetworkObject(NetworkConnection* networkConnection, const NetworkID& networkID):
        NetworkObject(networkConnection, networkID) {}
    void update() override {
        // TODO: ʵ�־���ĸ����߼�
    }

    void handlePacket(const PlayerID& sender, const vector<unsigned char>& data) override {
        // TODO: ������յ������ݰ�
    }
};

int main() {
// �����������Ӷ���
    SimpleNetworkConnection networkConnection;
    // ����������������
    bool peerToPeerMode = true;
    NetworkObjectManager networkObjectManager(&networkConnection, peerToPeerMode);

    // �������ID������ID
    PlayerID playerID;
    playerID.ipAddress = 0x7F000001; // 127.0.0.1
    playerID.port = 12345;
    NetworkID networkID;
    networkID.playerID = playerID;
    networkID.objectID = 1;

    // �������������ӵ���������������
    MyNetworkObject* myNetworkObject = new MyNetworkObject(&networkConnection, networkID);
    networkObjectManager.addNetworkObject(myNetworkObject);

    // ���������������������ID
    networkObjectManager.setPlayerID(playerID);

    // ģ���������ݰ��ķ��ͺͽ���
    vector<unsigned char> packetData;
    memcpy(&packetData[0], &networkID, sizeof(networkID));
    networkConnection.addPacketToQueue(NetworkPacket(playerID, packetData));
    networkObjectManager.update();

    return 0;
}