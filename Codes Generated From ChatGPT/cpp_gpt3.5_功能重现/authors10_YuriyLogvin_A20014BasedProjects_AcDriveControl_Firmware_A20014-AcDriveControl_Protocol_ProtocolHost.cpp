#include <iostream>
#include <vector>
#include <stdexcept>
#include <cstring>

class ProtocolHost
{
private:
    std::vector<unsigned char> address;
    std::vector<unsigned char> sendBuffer;
    std::vector<unsigned char> receiveBuffer;
    int sendState;
    int receiveState;
    int packetLength;

public:
    ProtocolHost(const std::vector<unsigned char> &addr)
    {
        setAddress(addr);
        sendState = 0;
        receiveState = 0;
        packetLength = 0;
    }

    const std::vector<unsigned char> &getAddress() const
    {
        return address;
    }

    void setAddress(const std::vector<unsigned char> &addr)
    {
        if (addr.size() != 4)
        {
            throw std::invalid_argument("Invalid address size. Must be 4 bytes.");
        }
        address = addr;
    }

    std::pair<const unsigned char *, int> receiveData(const unsigned char *data, int length)
    {
        if (length <= 0)
        {
            throw std::invalid_argument("Invalid data length. Must be greater than 0.");
        }

        receiveBuffer.clear();

        for (int i = 0; i < length; ++i)
        {
            unsigned char currentByte = data[i];

            switch (receiveState)
            {
            case 0:
                if (currentByte == 0x7E) // Start of packet
                {
                    receiveState = 1;
                }
                break;
            case 1:
                packetLength = currentByte;
                receiveState = 2;
                break;
            case 2:
                receiveBuffer.push_back(currentByte);
                if (--packetLength == 0)
                {
                    receiveState = 0;
                }
                break;
            default:
                receiveState = 0;
                break;
            }
        }

        return std::make_pair(receiveBuffer.data(), static_cast<int>(receiveBuffer.size()));
    }

    void prepareToSend(const unsigned char *data, int length)
    {
        if (length <= 0)
        {
            throw std::invalid_argument("Invalid data length. Must be greater than 0.");
        }

        sendBuffer.clear();
        sendBuffer.push_back(0x7E);        // Start of packet
        sendBuffer.push_back(length + 2);  // Data length + 2 bytes (address)

        sendBuffer.insert(sendBuffer.end(), address.begin(), address.end()); // Add address
        sendBuffer.insert(sendBuffer.end(), data, data + length);            // Add data

        sendState = 0;
    }

    bool sendData()
    {
        if (sendBuffer.empty())
        {
            throw std::runtime_error("No data to send. Call prepareToSend() first.");
        }

        switch (sendState)
        {
        case 0:
            std::cout << "Sending packet header..." << std::endl;
            sendState = 1;
            break;
        case 1:
            std::cout << "Sending packet data..." << std::endl;
            for (size_t i = 0; i < sendBuffer.size(); ++i)
            {
                std::cout << "0x" << std::hex << static_cast<int>(sendBuffer[i]) << " ";
            }
            std::cout << std::endl;
            sendState = 2;
            break;
        case 2:
            std::cout << "Sending checksum..." << std::endl;
            sendState = 3;
            break;
        default:
            sendBuffer.clear();
            sendState = 0;
        return false; // Data sent successfully
        break;
        }

        return true; // More data to send
    }
};
