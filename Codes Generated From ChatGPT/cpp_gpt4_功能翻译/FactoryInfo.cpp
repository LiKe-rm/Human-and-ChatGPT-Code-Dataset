#include <vector>
#include <mutex>
#include <iostream>
#include <stdexcept>
#include <cstring>

class QcNvItemsJRD {
public:
    std::vector<char> doNvRead(int id) {
        // Implement reading here...
    }
    void doNvWrite(int id, const std::vector<char>& data) {
        // Implement writing here...
    }
};

class FactoryInfo {
public:
    int nvi_length = 0;
    std::vector<char> data;
    bool isSync = false;
    std::vector<int> mNvItemsIds;

    static QcNvItemsJRD nvio;

private:
    static constexpr const char* TAG = "FactoryInfo";
    std::mutex mtx;

public:
    FactoryInfo(int size) {
        data.resize(size);
        isSync = false;
    }

    FactoryInfo(int size, const std::vector<int>& ids) : FactoryInfo(size) {
        nvi_length = size / ids.size();
        mNvItemsIds = ids;
    }

    FactoryInfo(int size, int id) : FactoryInfo(size) {
        nvi_length = size;
        mNvItemsIds.push_back(id);
    }

    std::vector<char> read() {
        std::lock_guard<std::mutex> lock(mtx);

        if (!isSync) {
            int offset = 0;
            std::vector<char> temp(nvi_length);

            for (int id : mNvItemsIds) {
                try {
                    temp = nvio.doNvRead(id);
                    std::memcpy(data.data() + offset, temp.data(), nvi_length);
                    offset += nvi_length;
                } catch (std::exception& e) {
                    std::cerr << TAG << ": Unable to read item " << id << " Value from NV \n";
                }
            }

            isSync = true;
        }

        return data;
    }

    void write(const std::vector<char>& newdata, int pos) {
        std::lock_guard<std::mutex> lock(mtx);

        isSync = false;

        try {
            std::memcpy(data.data() + pos, newdata.data(), newdata.size());
        } catch (std::exception& e) {
            std::cerr << TAG << ": can't copy " << newdata.size() << "bytes to data[" << pos << "--" << data.size() << "]\n";
        }

        int offset = 0;
        std::vector<char> temp(nvi_length);

        for (int id : mNvItemsIds) {
            try {
                std::memcpy(temp.data(), data.data() + offset, nvi_length);
                nvio.doNvWrite(id, temp);
                offset += nvi_length;
            } catch (std::exception& e) {
                std::cerr << TAG << ": Unable to write item " << id << " Value from NV \n";
            }
        }

        isSync = true;
    }
};

QcNvItemsJRD FactoryInfo::nvio;
