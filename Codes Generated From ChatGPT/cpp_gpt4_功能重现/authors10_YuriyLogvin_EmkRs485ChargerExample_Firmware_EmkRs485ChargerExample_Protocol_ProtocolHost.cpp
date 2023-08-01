#include <iostream>
#include <vector>

// 定义协议中的特殊字符和状态
const char CharStart = 0x01; // 起始字符
const char CharEsc = 0x02;   // 转义字符
const char CharEnd = 0x03;   // 结束字符
const char BroadcastAddress = 0xff; // 广播地址

enum ReceiveState
{
    Address,     // 接收到目的地址
    DataLength,  // 接收到数据长度
    Data,        // 接收到数据
    Checksum0,   // 接收到校验和0
    Checksum1,   // 接收到校验和1
    Finished     // 接收完成
};

enum SendingState
{
    SendStart,   // 发送起始字符
    SendAddress, // 发送目的地址
    SendLength,  // 发送数据长度
    SendData,    // 发送数据
    SendChecksum // 发送校验和
};

// 模拟串口通讯的类
class SerialPort
{
public:
    SerialPort() {}
    ~SerialPort() {}

    // 模拟串口接收数据
    std::vector<char>* Receive()
    {
        std::vector<char>* data = new std::vector<char>;
        char byte;
        bool EscSymbol = false;
        ReceiveState state = Address;

        while (true)
        {
            byte = ReadByteFromSerialPort();
            if (byte == CharStart)
            {
                state = Address;
                data->clear();
            }
            else if (byte == CharEsc)
            {
                EscSymbol = true;
                continue;
            }
            else if (byte == CharEnd)
            {
                if (state == Finished)
                {
                    if (CheckCRC(data))
                    {
                        return data;
                    }
                }
                continue;
            }

            if (EscSymbol)
            {
                byte ^= 0x20;
                EscSymbol = false;
            }

            switch (state)
            {
            case Address:
                if (byte == BroadcastAddress)
                {
                    state = DataLength;
                }
                else if (byte == MyAddress)
                {
                    state = DataLength;
                }
                break;
            case DataLength:
                DataPacketLength = byte;
                state = Data;
                break;
            case Data:
                DataBuff[DataBufferPosition] = byte;
                DataBufferPosition++;
                if (DataBufferPosition >= DataPacketLength)
                {
                    state = Checksum0;
                }
                break;
            case Checksum0:
                CheckSum0 = byte;
                state = Checksum1;
                break;
            case Checksum1:
                CheckSum1 = byte;
                state = Finished;
                break;
            }
            data->push_back(byte);
        }
        return nullptr;
    }

    // 模拟串口发送数据
    bool Send(std::vector<char> data)
    {
        SendingState state = SendStart;
        char byte;
        bool SendEscChar = false;

        WriteByteToSerialPort(CharStart);
        for (int i = 0; i < data.size(); i++)
        {
            byte = data[i];
            if (byte == CharStart || byte == CharEsc || byte == CharEnd)
            {
                WriteByteToSerialPort(CharEsc);
                WriteByteToSerialPort(byte ^ 0x20);
                SendEscChar = false;
                continue;
            }
            if (SendEscChar)
            {
                byte ^= 0x20;
                SendEscChar = false;
            }

            switch (state)
            {
            case SendStart:
                WriteByteToSerialPort(MyAddress);
                state = SendLength;
                break;
            case SendLength:
                WriteByteToSerialPort(DataPacketLength);
                state = SendData;
                break;
            case SendData:
                WriteByteToSerialPort(DataBuff[DataBufferPosition]);
                DataBufferPosition++;
                if (DataBufferPosition >= DataPacketLength)
                {
                    state = SendChecksum;
                }
                break;
            case SendChecksum:
                WriteByteToSerialPort(CheckSum0);
                WriteByteToSerialPort(CheckSum1);
                state = Finished;
                break;
            }
        }
        WriteByteToSerialPort(CharEnd);

        if (state == Finished)
        {
            _SendingState = Finished;
            return true;
        }
        else
        {
            return false;
        }
    }
private:
    // 数据缓冲区
    char* DataBuff;
    int DataBufferPosition;
    int DataPacketLength;
    int CheckSum0;
    int CheckSum1;
    // 定义自身地址
    const char MyAddress = 0x01;

    // 发送状态
    SendingState _SendingState;

    // 从串口中读取一个字节
    char ReadByteFromSerialPort()
    {
        // 这里省略了读取串口数据的代码
        return 0x00;
    }

    // 向串口中写入一个字节
    void WriteByteToSerialPort(char byte)
    {
        // 这里省略了向串口发送数据的代码
    }

    // 计算CRC校验和
    bool CheckCRC(std::vector<char>* data)
    {
        // 这里省略了计算CRC校验和的代码
        return true;
    }
};

