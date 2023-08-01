#include <iostream>
#include <RakPeerInterface.h>
#include <RakNetTypes.h>
#include <MessageIdentifiers.h>

// �������״̬
struct PlayerState {
    int id;
    float x, y, z;
    float velocity;
    bool isOnGround;
    // ��������
};

// ���峵��״̬
struct VehicleState {
    int id;
    float x, y, z;
    float velocity;
    // ��������
};

// ����˿�״̬
struct PassengerState {
    int id;
    int vehicleId;
    float x, y, z;
    // ��������
};

// ������׼״̬
struct AimState {
    int playerId;
    float pitch, yaw;
};

// ���嵯��״̬
struct BulletState {
    int playerId;
    float x, y, z;
    float velocity;
};

// ���ͬ������
void SyncPlayerState(PlayerState& state, RakNet::BitStream& stream) {
    // �����ж�ȡ���״̬��Ϣ
    stream.Read(state.id);
    stream.Read(state.x);
    stream.Read(state.y);
    stream.Read(state.z);
    stream.Read(state.velocity);
    stream.Read(state.isOnGround);

    // �������״̬
    // ...

    // �������״̬��Ϣ���������
    // ...
}

// ����ͬ������
void SyncVehicleState(VehicleState& state, RakNet::BitStream& stream) {
    // �����ж�ȡ����״̬��Ϣ
    stream.Read(state.id);
    stream.Read(state.x);
    stream.Read(state.y);
    stream.Read(state.z);
    stream.Read(state.velocity);

    // ���³���״̬
    // ...

    // ���ͳ���״̬��Ϣ���������
    // ...
}

// �˿�ͬ������
void SyncPassengerState(PassengerState& state, RakNet::BitStream& stream) {
    // �����ж�ȡ�˿�״̬��Ϣ
    stream.Read(state.id);
    stream.Read(state.vehicleId);
    stream.Read(state.x);
    stream.Read(state.y);
    stream.Read(state.z);

    // ���³˿�״̬
    // ...

    // ���ͳ˿�״̬��Ϣ���������
    // ...
}

// ��׼ͬ������
void SyncAimState(AimState& state, RakNet::BitStream& stream) {
    // ������
// ��ȡ��׼״̬��Ϣ
    stream.Read(state.playerId);
    stream.Read(state.pitch);
    stream.Read(state.yaw);

    // ������׼״̬
    // ...

    // ������׼״̬��Ϣ���������
    // ...
}

// ����ͬ������
void SyncBulletState(BulletState& state, RakNet::BitStream& stream) {
// �����ж�ȡ����״̬��Ϣ
    stream.Read(state.playerId);
    stream.Read(state.x);
    stream.Read(state.y);
    stream.Read(state.z);
    stream.Read(state.velocity);
}

// ����ͬ������
void SyncBulletState(BulletState& state, RakNet::BitStream& stream) {
// �����ж�ȡ����״̬��Ϣ
    stream.Read(state.playerId);
    stream.Read(state.x);
    stream.Read(state.y);
    stream.Read(state.z);
    stream.Read(state.velocity);
}

int main() {
// ��ʼ��RakNet�����
    RakNet::RakPeerInterface* peer = RakNet::RakPeerInterface::GetInstance();
    RakNet::SocketDescriptor sd;
    peer->Startup(1, &sd, 1);
    // ������Ϸ������
    RakNet::ConnectionAttemptResult result = peer->Connect("localhost", 1234, nullptr, 0);

    // ѭ��������Ϣ
    while (true) {
        for (RakNet::Packet* packet = peer->Receive(); packet != nullptr; peer->DeallocatePacket(packet), packet = peer->Receive()) {
            // ������������͵�ͬ����Ϣ
            switch (packet->data[0]) {
                case ID_SYNC_PLAYER_STATE:
                    PlayerState playerState;
                    RakNet::BitStream playerStream(packet->data, packet->length, false);
                    SyncPlayerState(playerState, playerStream);
                    break;
                case ID_SYNC_VEHICLE_STATE:
                    VehicleState vehicleState;
                    RakNet::BitStream vehicleStream(packet->data, packet->length, false);
                    SyncVehicleState(vehicleState, vehicleStream);
                    break;
                case ID_SYNC_PASSENGER_STATE:
                    PassengerState passengerState;
                    RakNet::BitStream passengerStream(packet->data, packet->length, false);
                    SyncPassengerState(passengerState, passengerStream);
                    break;
                case ID_SYNC_AIM_STATE:
                    AimState aimState;
                    RakNet::BitStream aimStream(packet->data, packet->length, false);
                    SyncAimState(aimState, aimStream);
                    break;
                case ID_SYNC_BULLET_STATE:
                    BulletState bulletState;
                    RakNet::BitStream bulletStream(packet->data, packet->length, false);
                    SyncBulletState(bulletState, bulletStream);
                    break;
                default:
                    break;
            }
        }
    }

    // �ر�RakNet�����
    RakNet::RakPeerInterface::DestroyInstance(peer);

    return 0;
}