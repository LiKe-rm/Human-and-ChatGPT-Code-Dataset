#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>

typedef char buffer_c8_t;  // 假设接收到的无线信号为char类型的缓冲区

class NRFRxProcessor {
public:
    NRFRxProcessor() : is_configured_(false) {}
    ~NRFRxProcessor() {}

    void execute(buffer_c8_t buffer[]) {
        if (!is_configured_) {
            std::cout << "NRFRxProcessor has not been configured yet." << std::endl;
            return;
        }
        // 调制解调
        decim_0.execute(buffer, buffer_size_);
        demod.execute(buffer, buffer_size_);
        // 统计解调输出
        int num_samples = demod.getNumSamples();
        std::vector<int> demod_output(num_samples);
        demod.getOutput(demod_output.data(), num_samples);
        // 处理音频信号
        int i = 0;
        while (i < num_samples) {
            // 在环形缓冲区中存储音频数据
            audio_buffer_[audio_buffer_head_] = demod_output[i];
            audio_buffer_head_ = (audio_buffer_head_ + 1) % audio_buffer_size_;
            // 跳跃样本技术降低计算成本
            i += jump_;
            // 根据阈值检测NRF24L01+包
            if (detectNRF24L01Packet()) {
                // 提取包的信息并将其放入共享内存队列
                std::unique_lock<std::mutex> lock(queue_mutex_);
                shared_queue_.push(packet_);
                queue_cond_var_.notify_one();
            }
        }
    }

    void configure(int decim_0_factor, int demod_filter_length, float demod_threshold) {
        decim_0.configure(decim_0_factor);
        demod.configure(demod_filter_length, demod_threshold);
        is_configured_ = true;
    }

    class NRFRxConfigureMessage {
    public:
        int decim_0_factor;
        int demod_filter_length;
        float demod_threshold;
    };

    void handleMessage(NRFRxConfigureMessage message) {
        configure(message.decim_0_factor, message.demod_filter_length, message.demod_threshold);
    }

private:
    class Decimator {
    public:
        Decimator() : is_configured_(false) {}
        ~Decimator() {}

        void execute(buffer_c8_t buffer[], int buffer_size) {
            if (!is_configured_) {
                std::cout << "Decimator has not been configured yet." << std::endl;
                return;
            }
            int num_samples = buffer_size / decimation_factor_;
            for (int i = 0; i < num_samples; i++) {
                int sum = 0;
                for (int j = 0; j < decimation_factor_; j++) {
                    sum += buffer[i*decimation_factor_ + j];
                }
                output_buffer_[i] = sum / decimation_factor_;
            }
        }

        void configure(int decimation_factor) {
            decimation_factor_ = decimation_factor;
            output_buffer_.resize(buffer_size_ / decimation_factor_);
            is_configured_ = true;
        }

        bool is_configured() {
            return is_configured_;
        }

    private:
        const int buffer_size_ = 256;
            int decimation_factor_;
    std::vector<int> output_buffer_;
    bool is_configured_;
};

    class Demodulator {
    public:
        Demodulator() : is_configured_(false) {}
        ~Demodulator() {}

        void execute(buffer_c8_t buffer[], int buffer_size) {
            if (!is_configured_) {
                std::cout << "Demodulator has not been configured yet." << std::endl;
                return;
            }
            int num_samples = buffer_size / decim_0_factor_;
            for (int i = 0; i < num_samples; i++) {
                // FM调制解调
                float angle = std::arg(buffer[i*decim_0_factor_]);
                float prev_angle = i > 0 ? std::arg(buffer[(i-1)*decim_0_factor_]) : 0.0;
                float delta = angle - prev_angle;
                if (delta > M_PI) {
                    delta -= 2 * M_PI;
                } else if (delta < -M_PI) {
                    delta += 2 * M_PI;
                }
                float freq_deviation = delta * sample_rate_ / (2 * M_PI * decim_0_factor_);
                // NRF24L01+解调
                float filtered_sample = fir_filter_.execute(freq_deviation);
                int quantized_sample = (filtered_sample > threshold_) ? 1 : 0;
                // 存储解调输出
                output_buffer_[i] = quantized_sample;
            }
            num_samples_ = num_samples;
        }

        void configure(int decim_0_factor, int filter_length, float threshold) {
            decim_0_factor_ = decim_0_factor;
            fir_filter_.configure(filter_length, sample_rate_ / (2 * M_PI * decim_0_factor_));
            threshold_ = threshold;
            output_buffer_.resize(buffer_size_ / decim_0_factor_);
            is_configured_ = true;
        }

        int getNumSamples() {
            return num_samples_;
        }

        void getOutput(int* output, int num_samples) {
            int num_samples_to_copy = std::min(num_samples, num_samples_);
            std::copy(output_buffer_.begin(), output_buffer_.begin() + num_samples_to_copy, output);
        }

        bool is_configured() {
            return is_configured_;
        }

    private:
        const int buffer_size_ = 256;
        const float sample_rate_ = 1.0e6;
        int decim_0_factor_;
        FIRFilter fir_filter_;
        float threshold_;
        std::vector<int> output_buffer_;
        int num_samples_;
        bool is_configured_;
    };

    bool detectNRF24L01Packet() {
        if (audio_buffer_tail_ == audio_buffer_head_) {
            return false;
        }
        int num_samples = (audio_buffer_head_ - audio_buffer_tail_ + audio_buffer_size_) % audio_buffer_size_;
        int threshold = num_samples * 0.9; // 简单设定阈值为90%
        int count = 0;
        int i = audio_buffer_tail_;
        while (i != audio_buffer_head_) {
            count += audio_buffer_[i];
            i = (i + jump_) % audio_buffer_size_;
        }
        if (count >= threshold) {
            // 提取NRF24L01+包的信息
            packet_ = extractPacketInfo();
            // 从环形缓冲区中删除已经处理过的音频数据
            int num_samples_processed = (i - audio_buffer_tail_ + audio_buffer_size) % audio_buffer_size_;
            audio_buffer_tail_ = i;
            return true;
        } else {
            return false;
        }
    }
    std::vector<int> extractPacketInfo() {
        // 从环形缓冲区中提取NRF24L01+包的信息
        // 包的信息是一组整数，具体格式取决于实际情况
        std::vector<int> packet;
        // ...
        return packet;
    }

    const int audio_buffer_size_ = 1024;
    std::vector<int> audio_buffer_;
    int audio_buffer_head_ = 0;
    int audio_buffer_tail_ = 0;
    int jump_ = 16;
    Demodulator demod;
    Decimator decim_0;
    bool is_configured_;
    std::mutex queue_mutex_;
    std::queue<std::vector<int>> shared_queue_;
    std::condition_variable queue_cond_var_;
    std::vector<int> packet_;
};

class EventDispatcher {
public:
    EventDispatcher(NRFRxProcessor* rx_processor) : rx_processor_(rx_processor) {}
    ~EventDispatcher() {}
    void run() {
        while (true) {
            // 从事件队列中获取消息
            NRFRxProcessor::NRFRxConfigureMessage message;
            // ...
            // 将消息传递给NRFRxProcessor进行处理
            rx_processor_->handleMessage(message);
        }
    }
private:
    NRFRxProcessor* rx_processor_;
};
