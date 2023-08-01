#include <iostream>
#include <vector>
#include <deque>
#include <cstring>
#include <cstdint>

class CMemPool {
public:
    CMemPool(size_t size) : blockSize(size) {}

    void* Alloc() {
        if (pool.empty()) {
            return new uint8_t[blockSize];
        } else {
            void* block = pool.back();
            pool.pop_back();
            return block;
        }
    }

    void Free(void* ptr) {
        pool.push_back(ptr);
    }

private:
    size_t blockSize;
    std::vector<void*> pool;
};

CMemPool g_inbufpool(4096);

class CInputBuffer {
public:
    CInputBuffer() : buffer((uint8_t*)g_inbufpool.Alloc()), point(0), end(0) {}

    ~CInputBuffer() {
        g_inbufpool.Free(buffer);
    }

    int GetMessage(uint8_t* netmsg) {
        if (end - point >= 12) {
            uint32_t msgLen = *(uint32_t*)(buffer + point + 8);
            if (msgLen > 4096 || msgLen < 12) {
                return -1;
            }
            memcpy(netmsg, buffer + point, msgLen);
            point += msgLen;
            if (point < end) {
                memmove(buffer, buffer + point, end - point);
            }
            point = 0;
            end -= msgLen;
            return 0;
        }
        return -1;
    }

    uint8_t* GetPoint() {
        return buffer + end;
    }

    size_t GetRemain() {
        return 4096 - end;
    }

    void SetPoint(size_t len) {
        end += len;
    }

private:
    uint8_t* buffer;
    size_t point;
    size_t end;
};

class CInputQueue {
public:
    void Add(const uint8_t* netmsg) {
        size_t msgLen = *(uint32_t*)(netmsg + 8);
        std::vector<uint8_t> msg(netmsg, netmsg + msgLen);
        queue.push_back(msg);
    }

    void Clear() {
        queue.clear();
    }

    int Get(uint8_t* netmsg) {
        if (!queue.empty()) {
            const std::vector<uint8_t>& msg = queue.front();
            memcpy(netmsg, msg.data(), msg.size());
            queue.pop_front();
            return 0;
        }
        return -1;
    }

    bool IsEmpty() {
        return queue.empty();
    }

private:
    std::deque<std::vector<uint8_t>> queue;
};

int main() {
    CInputBuffer inBuf;
    CInputQueue inQueue;

    // 示例：从inBuf获取消息并添加到inQueue
    uint8_t netmsg[4096];
    while (inBuf.GetMessage(netmsg) == 0) {
        inQueue.Add(netmsg);
    }

    // 示例：从inQueue获取消息并处理
    while (!inQueue.IsEmpty()) {
        if (inQueue.Get(netmsg) == 0) {
            // 处理消息
            std::cout << "处理消息：";
            for (size_t i = 0; i < *(uint32_t*)(netmsg + 8); ++i) {
                std::cout << static_cast<int>(netmsg[i]) << ' ';
            }
            std::cout << std::endl;
        }
    }

    return 0;
}
