#include <iostream>
#include <vector>
#include <list>
#include <string>

class Contact {
public:
    std::string name;
    std::string phone_number;
    std::string email;

    Contact(const std::string& name, const std::string& phone_number, const std::string& email)
        : name(name), phone_number(phone_number), email(email) {}
};

class HashMap {
    const double LOAD_FACTOR_THRESHOLD = 0.75;
    int element_count;
    int bucket_count;
    std::vector<std::list<std::pair<std::string, Contact>>> table;

public:
    HashMap(int initial_bucket_count = 8) : element_count(0), bucket_count(initial_bucket_count), table(initial_bucket_count) {}

    ~HashMap() {
        clear();
    }

    void check_load_factor_and_rehash() {
        double load_factor = double(element_count) / double(bucket_count);
        if (load_factor > LOAD_FACTOR_THRESHOLD) {
            rehash();
        }
    }

    void rehash() {
        std::vector<std::pair<std::string, Contact>> contacts = get_all_contacts();
        bucket_count *= 2;
        table.clear();
        table.resize(bucket_count);
        element_count = 0;

        for (const auto& contact : contacts) {
            insert(contact.first, contact.second);
        }
    }

    void clear() {
        for (auto& bucket : table) {
            bucket.clear();
        }
        element_count = 0;
    }

    int size() const {
        return element_count;
    }

    bool empty() const {
        return element_count == 0;
    }

    std::vector<std::pair<std::string, Contact>> get_all_contacts() const {
        std::vector<std::pair<std::string, Contact>> contacts;
        for (const auto& bucket : table) {
            for (const auto& entry : bucket) {
                contacts.push_back(entry);
            }
        }
        return contacts;
    }

    void insert(const std::string& key, const Contact& value) {
        int index = hash(key);
        auto& bucket = table[index];

        for (auto& entry : bucket) {
            if (entry.first == key) {
                entry.second = value;
                return;
            }
        }

        bucket.emplace_back(key, value);
        element_count++;
        check_load_factor_and_rehash();
    }

    int hash(const std::string& key) const {
        std::hash<std::string> hasher;
        return hasher(key) % bucket_count;
    }

    void remove(const std::string& key) {
        int index = hash(key);
        auto& bucket = table[index];

        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->first == key) {
                bucket.erase(it);
                element_count--;
                return;
            }
        }
    }

    bool contains(const std::string& key) const {
        int index = hash(key);
        const auto& bucket = table[index];

        for (const auto& entry : bucket) {
            if (entry.first == key) {
                return true;
            }
        }
        return false;
    }

    Contact get(const std::string& key) const {
        int index = hash(key);
        const auto& bucket = table[index];

        for (const auto& entry : bucket) {
            if (entry.first == key) {
                return entry.second;
            }
        }
        throw std::runtime_error("Key not found in the HashMap.");
    }

    std::vector<std::pair<std::string, Contact>> get_contacts_with_prefix(const std::string& prefix) const {
        std::vector<std::pair<std::string, Contact>> contacts_with_prefix;
        for (const auto& bucket : table) {
            for (const auto& entry : bucket) {
                if (entry.first.substr(0, prefix.size()) == prefix) {
                    contacts_with_prefix.push_back(entry);
                }
            }
        }
        return contacts_with_prefix;
    }

    friend std::ostream& operator<<(std::ostream& os, const HashMap& hashmap) {
        for (const auto& bucket : hashmap.table) {
            for (const auto& entry : bucket) {
                os << "Key: " << entry.first << ", Contact: " << entry.second.name << ", " << entry.second.phone_number << ", " << entry.second.email << std::endl;
            }
        }
        return os;
    }
};

