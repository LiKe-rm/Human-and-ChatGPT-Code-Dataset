#include <iostream>
#include <vector>

using namespace std;

// 定义 LccParsedPacket 结构体
struct LccParsedPacket {
    uint8_t command;
    uint8_t data[2];
};

// 定义 LccRawPacket 结构体
struct LccRawPacket {
    uint8_t header;
    uint8_t command;
    uint8_t data[2];
    uint8_t checksum;
};

// 将 LccParsedPacket 转换为 LccRawPacket
LccRawPacket convert_lcc_parsed_to_raw(const LccParsedPacket& parsed_packet) {
    LccRawPacket raw_packet = {0};
    raw_packet.header = 0x80;
    raw_packet.command = parsed_packet.command;
    raw_packet.data[0] = parsed_packet.data[0];
    raw_packet.data[1] = parsed_packet.data[1];
    raw_packet.checksum = raw_packet.header + raw_packet.command + raw_packet.data[0] + raw_packet.data[1];
    return raw_packet;
}

// 将 LccRawPacket 转换为 LccParsedPacket
LccParsedPacket convert_lcc_raw_to_parsed(const LccRawPacket& raw_packet) {
    LccParsedPacket parsed_packet = {0};
    parsed_packet.command = raw_packet.command;
    parsed_packet.data[0] = raw_packet.data[0];
    parsed_packet.data[1] = raw_packet.data[1];
    return parsed_packet;
}

// 创建一个所有字段都为零的 LccRawPacket
LccRawPacket create_safe_packet() {
    LccRawPacket safe_packet = {0};
    return safe_packet;
}

// 验证 LccRawPacket 是否符合规范
int validate_lcc_raw_packet(const LccRawPacket& raw_packet) {
    if (raw_packet.header != 0x80) {
        return 1;
    }
    uint8_t checksum = raw_packet.header + raw_packet.command + raw_packet.data[0] + raw_packet.data[1];
    if (checksum != raw_packet.checksum) {
        return 2;
    }
    return 0;
}

int main() {
    // 测试代码
    LccParsedPacket parsed_packet = {0x01, {0x02, 0x03}};
    LccRawPacket raw_packet = convert_lcc_parsed_to_raw(parsed_packet);
    LccParsedPacket parsed_packet2 = convert_lcc_raw_to_parsed(raw_packet);
    LccRawPacket safe_packet = create_safe_packet();
    int validation_result = validate_lcc_raw_packet(raw_packet);
    cout << "Validation result: " << validation_result << endl;
    return 0;
}
