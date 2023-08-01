#include <iostream>
#include <leveldb/db.h>

int main() {
    leveldb::DB* db;
    leveldb::Options options;
    options.create_if_missing = true;

    // Open the database
    leveldb::Status status = leveldb::DB::Open(options, "/tmp/testdb", &db);
    if (!status.ok()) {
        std::cerr << "Failed to open database: " << status.ToString() << std::endl;
        return 1;
    }

    // Write some data
    std::string key = "hello";
    std::string value = "world";
    status = db->Put(leveldb::WriteOptions(), key, value);
    if (!status.ok()) {
        std::cerr << "Failed to write data: " << status.ToString() << std::endl;
        return 1;
    }

    // Read some data
    std::string result;
    status = db->Get(leveldb::ReadOptions(), key, &result);
    if (status.ok()) {
        std::cout << "Value of key " << key << " is " << result << std::endl;
    } else {
        std::cerr << "Failed to read data: " << status.ToString() << std::endl;
        return 1;
    }
// Close the database
    delete db;

    return 0;
}