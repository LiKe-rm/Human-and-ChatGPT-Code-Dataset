#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <memory>
#include <functional>

#include <tinyxml2.h>
#include <sqlite3.h>
using namespace std;

class Device {
public:
    Device(const std::string &guid, const std::string &name, const std::string &description)
        : guid_(guid), name_(name), description_(description) {}

    const std::string &GetGuid() const { return guid_; }
    const std::string &GetName() const { return name_; }
    const std::string &GetDescription() const { return description_; }

private:
    std::string guid_;
    std::string name_;
    std::string description_;
};

class GuidList {
public:
    bool AddGuid(const std::string &guid) {
        if (guid_set_.find(guid) != guid_set_.end()) {
            return false;
        }
        guid_set_.insert(guid);
        return true;
    }

    bool CheckIfGuidExists(const std::string &guid) const {
        return guid_set_.find(guid) != guid_set_.end();
    }

private:
    std::unordered_set<std::string> guid_set_;
};

class DeviceInfoParser {
public:
    DeviceInfoParser() = default;

    std::unique_ptr<Device> Parse(const std::string &xml_data) {
        tinyxml2::XMLDocument doc;
        if (doc.Parse(xml_data.c_str()) != tinyxml2::XML_SUCCESS) {
            return nullptr;
        }

        tinyxml2::XMLElement *root = doc.RootElement();
        if (root == nullptr) {
            return nullptr;
        }

        const char *guid = root->Attribute("guid");
        const char *name = root->Attribute("name");
        const char *description = root->Attribute("description");

        if (guid == nullptr || name == nullptr || description == nullptr) {
            return nullptr;
        }

        return std::make_unique<Device>(guid, name, description);
    }
};

class DeviceInfoReceived {
public:
    using DeviceCallback = std::function<void(const Device &)>;
    using LogCallback = std::function<void(const std::string &, const std::string &)>;

    DeviceInfoReceived(GuidList &guid_list, DeviceCallback device_callback, LogCallback log_callback)
        : guid_list_(guid_list), device_callback_(device_callback), log_callback_(log_callback) {}

    std::string ProcessXmlData(const std::string &xml_data) {
        DeviceInfoParser parser;
        auto device = parser.Parse(xml_data);
        if (device == nullptr) {
            return "Failed to parse XML data";
        }

        if (guid_list_.CheckIfGuidExists(device->GetGuid())) {
            return "Error: GUID already exists";
        }

        guid_list_.AddGuid(device->GetGuid());
        device_callback_(*device);

        log_callback_(device->GetGuid(), "Device information added to database");

        return "New GUID: " + device->GetGuid();
    }

private:
    GuidList &guid_list_;
    DeviceCallback device_callback_;
    LogCallback log_callback_;
};

void StoreDeviceInDatabase(const Device &device) {
    sqlite3 *db = InitializeDatabase("device_info.db");
    if (db == nullptr) {
        return;
    }

    const char *insert_device_sql = R"(
        INSERT INTO devices (guid, name, description) VALUES (?, ?, ?);
    )";

    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, insert_device_sql, -1, &stmt, nullptr);

    sqlite3_bind_text(stmt, 1, device.GetGuid().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, device.GetName().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, device.GetDescription().c_str(), -1, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        cerr << "Failed to store device in database: " << sqlite3_errmsg(db) << endl;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void StoreLogInDatabase(const std::string &guid, const std::string &log_message) {
    sqlite3 *db = InitializeDatabase("device_info.db");
    if (db == nullptr) {
        return;
    }

    const char *insert_log_sql = R"(INSERT INTO logs (guid, log_message) VALUES (?, ?);
    )";

    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, insert_log_sql, -1, &stmt, nullptr);

    sqlite3_bind_text(stmt, 1, guid.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, log_message.c_str(), -1, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        cerr << "Failed to store log in database: " << sqlite3_errmsg(db) << endl;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

sqlite3 *InitializeDatabase(const std::string &db_name) {
    sqlite3 *db;
    int rc = sqlite3_open(db_name.c_str(), &db);

    if (rc) {
        cerr << "Can't open database: " << sqlite3_errmsg(db) << endl;
        return nullptr;
    }

    const char *create_device_table_sql = R"(
        CREATE TABLE IF NOT EXISTS devices (
            guid TEXT PRIMARY KEY,
            name TEXT NOT NULL,
            description TEXT NOT NULL
        );
    )";

    const char *create_log_table_sql = R"(
        CREATE TABLE IF NOT EXISTS logs (
            guid TEXT NOT NULL,
            log_message TEXT NOT NULL
        );
    )";

    char *error_msg = nullptr;
    rc = sqlite3_exec(db, create_device_table_sql, nullptr, nullptr, &error_msg);
    if (rc != SQLITE_OK) {
        cerr << "Cannot create devices table: " << error_msg << endl;
        sqlite3_free(error_msg);
    }

    rc = sqlite3_exec(db, create_log_table_sql, nullptr, nullptr, &error_msg);
    if (rc != SQLITE_OK) {
        cerr << "Cannot create logs table: " << error_msg << endl;
        sqlite3_free(error_msg);
    }

    return db;
}

