#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstdint>
#include <cstring>
#include <vector>

// 日志标记
const char* LOG_TAG = "InputChannelTest";

// 辅助函数，将内存转换为十六进制字符串
std::string memoryAsHexString(const void* memory, size_t size) {
    std::ostringstream stream;
    stream << std::hex << std::setfill('0');

    const uint8_t* data = static_cast<const uint8_t*>(memory);
    for (size_t i = 0; i < size; ++i) {
        stream << std::setw(2) << static_cast<int>(data[i]) << ' ';
    }

    return stream.str();
}

class InputMessage {
public:
    enum Type {
        TYPE_KEY = 0,
        TYPE_MOTION = 1,
        TYPE_FINISHED = 2
    };

    Type type;
    uint32_t header;
    uint32_t body;
    uint8_t padding[32];

    InputMessage() {
        memset(this, 0, sizeof(InputMessage));
    }
};

// 清洗消息
void sanitizeMessage(InputMessage& message) {
    uint32_t header = message.header;
    uint32_t body = message.body;
    memset(&message, 0, sizeof(InputMessage));
    message.header = header;
    message.body = body;
}

// 检查消息是否存在未初始化的字节
bool checkMessage(const InputMessage& message) {
    const uint8_t* data = reinterpret_cast<const uint8_t*>(&message);
    for (size_t i = offsetof(InputMessage, padding);
         i < sizeof(InputMessage);
         ++i) {
        if (data[i] != 0) {
            std::cout << LOG_TAG << ": Found uninitialized byte at offset "
                      << i << ": " << memoryAsHexString(data, sizeof(InputMessage)) << std::endl;
            return false;
        }
    }
    return true;
}

// 模拟服务端发送消息
void sendMessageToServer(InputMessage& message) {
    // 实际情况下，这里应该将消息发送到服务端进行处理。
}

// 模拟客户端接收消息
void receiveMessageFromClient(InputMessage& message) {
    // 实际情况下，这里应该从服务端接收已清洗的消息。
}

int main() {
    InputMessage messageTypes[] = {
        {InputMessage::TYPE_KEY, 0, 0},
        {InputMessage::TYPE_MOTION, 0, 0},
        {InputMessage::TYPE_FINISHED, 0, 0}
    };

    for (const auto& msgType : messageTypes) {
        InputMessage originalMessage = msgType;
        originalMessage.padding[0] = 0xFF; // 模拟未被清洗的消息

        std::cout << LOG_TAG << ": Sending message of type " << msgType.type << std::endl;
        sendMessageToServer(originalMessage);

        InputMessage sanitizedMessage = originalMessage;
        sanitizeMessage(sanitizedMessage);
        receiveMessageFromClient(sanitizedMessage);

        if (!checkMessage(sanitizedMessage)) {
            std::cout << LOG_TAG << ": Detected uninitialized bytes in message of type "
                      << msgType.type << std::endl;
        } else {
            std::cout << LOG_TAG << ": Message of type " << msgType.type
                      << " is safe." << std::endl;
        }
    }

    return 0;
}
