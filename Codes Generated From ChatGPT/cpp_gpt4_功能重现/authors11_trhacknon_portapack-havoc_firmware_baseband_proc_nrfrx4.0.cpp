#include <iostream>
#include <queue>
#include <memory>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <RF24/RF24.h>

// 示例 buffer_c8_t 类型
using buffer_c8_t = std::vector<uint8_t>;

class NRFRxProcessor {
public:
    void execute(buffer_c8_t &buffer) {
        if (!configured) {
            return;
        }

        // 解调和解码过程
        radio.read(&buffer[0], buffer.size());

        // 处理解码后的数据并推入共享内存队列
        std::unique_lock<std::mutex> lock(queue_mutex);
        shared_queue.push(buffer);
        queue_cv.notify_one();
    }

    void configure(/* NRFRxConfigureMessage msg */) {
        // 对调制器和解调器进行配置
        // 示例配置
        radio.begin();
        radio.setChannel(76);
        radio.setPALevel(RF24_PA_MAX);
        radio.setDataRate(RF24_1MBPS);
        radio.setAutoAck(1, 0);
        radio.setCRCLength(RF24_CRC_8);
        radio.openReadingPipe(1, 0xF0F0F0F0E1LL);
        radio.startListening();

        configured = true;
    }

private:
    bool configured = false;
    std::queue<buffer_c8_t> shared_queue;
    std::mutex queue_mutex;
    std::condition_variable queue_cv;
    RF24 radio{25, 0};  // 设置 CE 和 CSN 引脚
};

class EventDispatcher {
public:
    EventDispatcher(NRFRxProcessor &processor) : rx_processor(processor) {}

    void run() {
        while (true) {
            // 接收消息
            if (rx_processor.radio.available()) {
                buffer_c8_t received_msg(32);  // 假设消息大小为 32 字节
                rx_processor.execute(received_msg);
            }
        }
    }

private:
    NRFRxProcessor &rx_processor;
};

