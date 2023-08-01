#include <iostream>
#include <vector>
#include <stdexcept>

enum MethodType {
    mtByte,
    mtShort,
    mtInt,
    mtLong,
    mtFloat,
    mtDouble
};

class ReceiveMethodHost {
private:
    const uint8_t* buffer;
    size_t bufferLength;

    size_t _GetArgumentLength(MethodType type) {
        switch (type) {
            case mtByte:
                return sizeof(uint8_t);
            case mtShort:
                return sizeof(uint16_t);
            case mtInt:
                return sizeof(uint32_t);
            case mtLong:
                return sizeof(uint64_t);
            case mtFloat:
                return sizeof(float);
            case mtDouble:
                return sizeof(double);
            default:
                throw std::runtime_error("Invalid method type");
        }
    }

    size_t _GetArgPositionAndCheckIt(size_t argIndex) {
        size_t position = 1;
        for (size_t i = 0; i < argIndex; ++i) {
            MethodType argType = static_cast<MethodType>(buffer[position]);
            position += 1 + _GetArgumentLength(argType);
            if (position >= bufferLength) {
                throw std::runtime_error("Invalid argument index");
            }
        }
        return position;
    }

public:
    ReceiveMethodHost(const uint8_t* dataBuffer, size_t length) : buffer(dataBuffer), bufferLength(length) {}

    uint8_t GetMethodNumber() {
        return buffer[0];
    }

    size_t GetMethodArgumentCount() {
        size_t count = 0;
        size_t position = 1;
        while (position < bufferLength) {
            MethodType argType = static_cast<MethodType>(buffer[position]);
            position += 1 + _GetArgumentLength(argType);
            count++;
        }
        return count;
    }

    MethodType GetMethodArgumentType(size_t argIndex) {
        return static_cast<MethodType>(buffer[_GetArgPositionAndCheckIt(argIndex)]);
    }

    bool CheckMethodHasNoArguments() {
        return GetMethodArgumentCount() == 0;
    }

    bool CheckMethodHasOneArgumentOfType(MethodType type) {
        return GetMethodArgumentCount() == 1 && GetMethodArgumentType(0) == type;
    }

    void GetArgumentByte(size_t argIndex, uint8_t& value) {
        size_t position = _GetArgPositionAndCheckIt(argIndex);
        if (buffer[position] != mtByte) {
            throw std::runtime_error("Invalid argument type");
        }
        value = buffer[position + 1];
    }

    void GetArgumentShort(size_t argIndex, uint16_t& value) {
        size_t position = _GetArgPositionAndCheckIt(argIndex);
        if (buffer[position] != mtShort) {
            throw std::runtime_error("Invalid argument type");
        }
        value = static_cast<uint16_t>(buffer[position + 1]) | (static_cast<uint16_t>(buffer[position + 2]) << 8);
    }

    // 同样，您可以为其他类型实现类似的GetArgumentInt，GetArgumentLong，GetArgumentFloat和GetArgumentDouble方法。
};

int main() {
    uint8_t data[] = {1, mtByte, 42, mtShort, 0x34, 0x12};
    ReceiveMethodHost host(data, sizeof(data));

    std::cout << "Method Number: " << static_cast<int>(host.GetMethodNumber()) << std::endl;
    std::cout << "Method Argument Count: " << host.GetMethodArgumentCount() << std::endl;

    uint8_t byteValue;
    uint16_t shortValue;
    host.GetArgumentByte(0, byteValue);
    host.GetArgumentShort(1, shortValue);
    
    std::cout << "Byte Argument Value: " << static_cast<int>(byteValue) << std::endl;
    std::cout << "Short Argument Value: " << shortValue << std::endl;
    
    // 实现其他类型的方法后，您可以继续从类中获取相应的值。
    
    return 0;
}
