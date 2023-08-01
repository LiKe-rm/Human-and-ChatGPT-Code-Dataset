#include <iostream>
#include <vector>
#include <stdexcept>
#include <cstdint>
#include <cstring>

class ReceiveMethodHost {
public:
    // 默认构造函数
    ReceiveMethodHost() = default;

    // 默认析构函数
    ~ReceiveMethodHost() = default;

    // 用于初始化字节流数组和数组长度
    void init(const uint8_t* byteArray, size_t length) {
        byteArray_ = byteArray;
        length_ = length;
    }

    // 根据方法类型和下一个字节确定参数的长度
    size_t parameterLength(uint8_t methodType, uint8_t nextByte) const {
        switch (methodType) {
            case BYTE_TYPE:
                return 1;
            case BOOL_TYPE:
                return 1;
            case SHORT_TYPE:
            case USHORT_TYPE:
                return 2;
            case INT_TYPE:
            case UINT_TYPE:
                return 4;
            default:
                throw std::runtime_error("Invalid method type.");
        }
    }

    // 用于查找给定参数在字节流数组中的位置，并检查其有效性
    size_t findParameterPosition(size_t parameterIndex) const {
        if (parameterIndex >= getParameterCount()) {
            throw std::runtime_error("Invalid parameter index.");
        }

        size_t position = 1; // skip method number
        for (size_t i = 0; i < parameterIndex; ++i) {
            uint8_t methodType = byteArray_[position++];
            size_t length = parameterLength(methodType, byteArray_[position]);
            position += length;
        }

        return position;
    }

    // 获取方法编号
    uint8_t getMethodNumber() const {
        return byteArray_[0];
    }

    // 获取某个参数的值
    template <typename T>
    T getParameterValue(size_t parameterIndex) const {
        size_t position = findParameterPosition(parameterIndex);
        uint8_t methodType = byteArray_[position++];
        T value;
        memcpy(&value, byteArray_ + position, sizeof(T));
        return value;
    }

    // 获取参数的数量
    size_t getParameterCount() const {
        size_t count = 0;
        size_t position = 1; // skip method number

        while (position < length_) {
            uint8_t methodType = byteArray_[position++];
            size_t length = parameterLength(methodType, byteArray_[position]);
            position += length;
            ++count;
        }

        return count;
    }

    // 获取某个参数的类型
    uint8_t getParameterType(size_t parameterIndex) const {
        return byteArray_[findParameterPosition(parameterIndex)];
    }

    // 检查方法是否合法（即参数数量是否为0）
    bool isMethodValid() const {
        return getParameterCount() != 0;
    }

    // 检查方法是否合法，并检查第一个参数的类型是否满足要求
    bool isMethodValidWithFirstParameterType(uint8_t requiredType) const {
        return isMethodValid() && getParameterType(0) == requiredType;
    }

private:
    enum MethodType {
        BYTE_TYPE = 0,
        BOOL_TYPE,
        SHORT_TYPE,
        USHORT_TYPE,
        INT_TYPE,
        UINT_TYPE
    };

    const uint8_t* byteArray_ = nullptr;
    size_t length_ = 0;
};
