#include <cstdio>
#include <cstring>

// �궨�壬��λת��Ϊ�ֽ�
#define BITS_TO_BYTES(x) ((x+7)>>3)
// �궨�壬���ֽ�ת��Ϊλ
#define BYTES_TO_BITS(x) (x<<3)

// ����RakNetͳ����Ϣ�ṹ��
struct RakNetStatisticsStruct {
    // ���������
    unsigned long long messageSendBuffer[NUMBER_OF_PRIORITIES];  // ��Ϣ���ͻ�����
    unsigned long messageSendBufferHighWaterMark[NUMBER_OF_PRIORITIES];  // ��Ϣ���ͻ�������ˮλ���
    // ���������
    unsigned long long messageRecvBuffer[NUMBER_OF_PRIORITIES];  // ��Ϣ���ջ�����
    unsigned long messageRecvBufferHighWaterMark[NUMBER_OF_PRIORITIES];  // ��Ϣ���ջ�������ˮλ���
    // �������
    unsigned long messagesInSendBuffer[NUMBER_OF_PRIORITIES];  // ���ͻ������е���Ϣ����
    unsigned long messagesInRecvBuffer[NUMBER_OF_PRIORITIES];  // ���ջ������е���Ϣ����
    unsigned long messageDataBitsSent;  // ���͵���Ϣ����λ��
    unsigned long messageDataBitsResent;  // �ط�����Ϣ����λ��
    unsigned long long messagesTotalBitsSent;  // ���͵�����Ϣ����λ��
    unsigned long long messageTotalBitsResent;  // �ط�������Ϣ����λ��
    unsigned long messageDataBitsReceived;  // ���յ�����Ϣ����λ��
    unsigned long messageDuplicateBitsReceived;  // ���յ����ظ���Ϣ����λ��
    unsigned long messageBitsReceivedIgnored;  // ���յ��������Ե���Ϣ����λ��
    unsigned long messageBitsReceivedWithBadCRC;  // ���յ���CRCУ��ʧ�ܵ���Ϣ����λ��
    unsigned long messagesRecvWidthBadCRC;  // ���յ���CRCУ��ʧ�ܵ���Ϣ����
};

// ͳ����Ϣ�������
void printRakNetStatisticsStruct(RakNetStatisticsStruct* s, char* buffer, int verbosityLevel) {
    int offset = 0; // �ַ�����ƫ����
    if (verbosityLevel >= 0) {
        // ������ͺͽ��ջ�������״̬
        for (int i = 0; i < NUMBER_OF_PRIORITIES; i++) {
            offset += sprintf(buffer + offset, "Priority %d: ", i);
            offset += sprintf(buffer + offset, "Send buffer: %llu/%lu, Recv buffer: %llu/%lu\n",
                s->messageSendBuffer[i], s->messageSendBufferHighWaterMark[i],
                s->messageRecvBuffer[i], s->messageRecvBufferHighWaterMark[i]);
        }
        // ������ͺͽ�����Ϣ������������λ��
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
    // ��������Ժ�CRCУ��ʧ�ܵ���Ϣ��������λ��
        offset += sprintf(buffer + offset, "Ignored data bits: %lu, Bad CRC data bits: %lu\n",
            s->messageBitsReceivedIgnored, s->messageBitsReceivedWithBadCRC);
        offset += sprintf(buffer + offset, "Messages with bad CRC: %lu\n", s->messagesRecvWidthBadCRC);
    }
    if (verbosityLevel >= 2) {
    // ���ÿ���������е���Ϣ����
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
