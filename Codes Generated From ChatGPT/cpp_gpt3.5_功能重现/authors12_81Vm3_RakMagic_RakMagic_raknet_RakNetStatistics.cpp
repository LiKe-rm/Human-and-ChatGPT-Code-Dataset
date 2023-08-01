#include <cstdio>
#include <cstring>

// 宏定义，将位转换为字节
#define BITS_TO_BYTES(x) ((x+7)>>3)
// 宏定义，将字节转换为位
#define BYTES_TO_BITS(x) (x<<3)

// 定义RakNet统计信息结构体
struct RakNetStatisticsStruct {
    // 包发送相关
    unsigned long long messageSendBuffer[NUMBER_OF_PRIORITIES];  // 消息发送缓冲区
    unsigned long messageSendBufferHighWaterMark[NUMBER_OF_PRIORITIES];  // 消息发送缓冲区高水位标记
    // 包接收相关
    unsigned long long messageRecvBuffer[NUMBER_OF_PRIORITIES];  // 消息接收缓冲区
    unsigned long messageRecvBufferHighWaterMark[NUMBER_OF_PRIORITIES];  // 消息接收缓冲区高水位标记
    // 其他相关
    unsigned long messagesInSendBuffer[NUMBER_OF_PRIORITIES];  // 发送缓冲区中的消息数量
    unsigned long messagesInRecvBuffer[NUMBER_OF_PRIORITIES];  // 接收缓冲区中的消息数量
    unsigned long messageDataBitsSent;  // 发送的消息数据位数
    unsigned long messageDataBitsResent;  // 重发的消息数据位数
    unsigned long long messagesTotalBitsSent;  // 发送的总消息数据位数
    unsigned long long messageTotalBitsResent;  // 重发的总消息数据位数
    unsigned long messageDataBitsReceived;  // 接收到的消息数据位数
    unsigned long messageDuplicateBitsReceived;  // 接收到的重复消息数据位数
    unsigned long messageBitsReceivedIgnored;  // 接收到但被忽略的消息数据位数
    unsigned long messageBitsReceivedWithBadCRC;  // 接收到但CRC校验失败的消息数据位数
    unsigned long messagesRecvWidthBadCRC;  // 接收到但CRC校验失败的消息数量
};

// 统计信息输出函数
void printRakNetStatisticsStruct(RakNetStatisticsStruct* s, char* buffer, int verbosityLevel) {
    int offset = 0; // 字符数组偏移量
    if (verbosityLevel >= 0) {
        // 输出发送和接收缓冲区的状态
        for (int i = 0; i < NUMBER_OF_PRIORITIES; i++) {
            offset += sprintf(buffer + offset, "Priority %d: ", i);
            offset += sprintf(buffer + offset, "Send buffer: %llu/%lu, Recv buffer: %llu/%lu\n",
                s->messageSendBuffer[i], s->messageSendBufferHighWaterMark[i],
                s->messageRecvBuffer[i], s->messageRecvBufferHighWaterMark[i]);
        }
        // 输出发送和接收消息的数量和数据位数
        offset += sprintf(buffer + offset, "Messages in send buffer: %lu, Messages in recv buffer: %lu\n",
            s->messagesInSendBuffer[0], s->messagesInRecvBuffer[0]);
        offset += sprintf(buffer + offset, "Sent data bits: %lu, Resent data bits: %lu\n",
            s->messageDataBitsSent, s->messageDataBitsBitsResent);
        offset += sprintf(buffer + offset, "Total sent bits: %llu, Total resent bits: %llu\n",
            s->messagesTotalBitsSent, s->messageTotalBitsResent);
        offset += sprintf(buffer + offset, "Received data bits: %lu, Duplicate data bits: %lu\n",
            s->messageDataBitsReceived, s->messageDuplicateBitsReceived);
    }
    if (verbosityLevel >= 1) {
    // 输出被忽略和CRC校验失败的消息数和数据位数
        offset += sprintf(buffer + offset, "Ignored data bits: %lu, Bad CRC data bits: %lu\n",
            s->messageBitsReceivedIgnored, s->messageBitsReceivedWithBadCRC);
        offset += sprintf(buffer + offset, "Messages with bad CRC: %lu\n", s->messagesRecvWidthBadCRC);
    }
    if (verbosityLevel >= 2) {
    // 输出每个缓冲区中的消息数量
        offset += sprintf(buffer + offset, "Messages in send buffer: ");
        for (int i = 0; i < NUMBER_OF_PRIORITIES; i++) {
            offset += sprintf(buffer + offset, "%lu ", s->messagesInSendBuffer[i]);
        }
        offset += sprintf(buffer + offset, "\nMessages in recv buffer: ");
        for (int i = 0; i < NUMBER_OF_PRIORITIES; i++) {
            offset += sprintf(buffer + offset, "%lu ", s->messagesInRecvBuffer[i]);
        }
        offset += sprintf(buffer + offset, "\n");
    }
}
