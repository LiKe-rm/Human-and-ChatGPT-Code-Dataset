#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <map>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>

class Record {
public:
    std::string key;
    std::string value;

    Record(const std::string &key, const std::string &value) : key(key), value(value) {}
};

class Database {
public:
    Database(const std::string &filepath);
    ~Database();

    void SetRecord(const std::string &key, const std::string &value);
    bool RemoveRecord(const std::string &key);
    void SortRecords();
    std::vector<std::string> UniqueValuesForKey(const std::string &key);
    std::vector<Record> DuplicateRecordsForKey(const std::string &key);
    void Commit();

private:
    std::string filepath_;
    std::vector<Record> records_;
    int file_descriptor_;
    void *file_memory_;
    size_t file_size_;
};

Database::Database(const std::string &filepath) : filepath_(filepath) {
    file_descriptor_ = open(filepath.c_str(), O_RDONLY);
    if (file_descriptor_ == -1) {
        std::cerr << "Error opening the file" << std::endl;
        return;
    }

    struct stat file_stat;
    if (fstat(file_descriptor_, &file_stat) == -1) {
        std::cerr << "Error getting file size" << std::endl;
        close(file_descriptor_);
        return;
    }
    file_size_ = file_stat.st_size;

    file_memory_ = mmap(nullptr, file_size_, PROT_READ, MAP_PRIVATE, file_descriptor_, 0);
    if (file_memory_ == MAP_FAILED) {
        std::cerr << "Error mapping file to memory" << std::endl;
        close(file_descriptor_);
        return;
    }

    std::string file_content(static_cast<char *>(file_memory_), file_size_);
    size_t pos = 0, delimiter_pos;

    while ((delimiter_pos = file_content.find('\n', pos)) != std::string::npos) {
        std::string line = file_content.substr(pos, delimiter_pos - pos);
        size_t key_value_delimiter = line.find(',');
        std::string key = line.substr(0, key_value_delimiter);
        std::string value = line.substr(key_value_delimiter + 1);
        records_.emplace_back(key, value);

        pos = delimiter_pos + 1;
    }
}

Database::~Database() {
    if (file_memory_ != nullptr && file_memory_ != MAP_FAILED) {
        munmap(file_memory_, file_size_);
    }

    if (file_descriptor_ != -1) {
        close(file_descriptor_);
    }
}

void Database::SetRecord(const std::string &key, const std::string &value) {
    records_.emplace_back(key, value);
}

bool Database::RemoveRecord(const std::string &key) {
    auto it = std::find_if(records_.begin(), records_.end(),
                           [&](const Record &record) { return record.key == key; });

    if (it != records_.end()) {
        records_.erase(it);
        return true;
    }

    return false;
}

void Database::SortRecords() {
    std::sort(records_.begin(), records_.end(),
              [](const Record &a, const Record &b) { return a.key < b.key; });
}

std::vector<std::string> Database::UniqueValuesForKey(const std::string &key) {
    std::vector<std::string> values;
    for (const auto &record : records_) {
        if (record.key == key) {
            if (std::find(values.begin(), values.end(), record.value) == values.end()) {
                values.push_back(record.value);
            }
        }
    }
    return values;
}

std::vector<Record> Database::DuplicateRecordsForKey(const std::string &key) {
    std::vector<Record> duplicates;
    std::map<std::string, int> value_count;

    for (const auto &record : records_) {
        if (record.key == key) {
            value_count[record.value]++;
        }
    }

    for (const auto &entry : value_count) {
        if (entry.second > 1) {
            duplicates.emplace_back(key, entry.first);
        }
    }

    return duplicates;
}

void Database::Commit() {
    std::string temp_filepath = filepath_ + ".tmp";
    std::ofstream temp_file(temp_filepath);

    if (!temp_file.is_open()) {
        std::cerr << "Error opening temporary file" << std::endl;
        return;
    }

    for (const auto &record : records_) {
        temp_file << record.key << ',' << record.value << '\n';
    }

    temp_file.close();

    if (std::rename(temp_filepath.c_str(), filepath_.c_str()) != 0) {
        std::cerr << "Error renaming temporary file" << std::endl;
    }
}
