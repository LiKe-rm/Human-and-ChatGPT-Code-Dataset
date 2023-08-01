#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <mutex>
#include <map>
#include <regex>
#include <arpa/inet.h>

using namespace std;

class BanList {
    public:
    BanList() {}

    ~BanList() {}

    // 根据IP地址或子网划分封锁该地址；如果封锁成功，则返回true。
    bool Ban(const string& ip, int level = 2) {
        lock_guard<mutex> lock(m_mutex);

        uint32_t address = inet_addr(ip.c_str());
        if (address == INADDR_NONE) {
            return false;
        }

        for (const auto& entry : m_banned) {
            if (entry.first.first == (address & entry.first.second)) {
                return false;
            }
        }

        m_banned[make_pair(address, 0xffffffff)] = level;

        return true;
    }

    // 根据IP地址或子网划分解锁该地址；如果解锁成功，则返回true。
    bool Unban(const string& ip) {
        lock_guard<mutex> lock(m_mutex);

        uint32_t address = inet_addr(ip.c_str());
        if (address == INADDR_NONE) {
            return false;
        }

        for (auto it = m_banned.begin(); it != m_banned.end(); ++it) {
            if (it->first.first == address) {
                m_banned.erase(it);
                return true;
            }
        }

        return false;
    }

    // 根据IP地址判断该地址是否被封锁；如果被封锁，则返回true。
    bool IsBanned(const string& ip) {
        lock_guard<mutex> lock(m_mutex);

        uint32_t address = inet_addr(ip.c_str());
        if (address == INADDR_NONE) {
            return false;
        }

        for (const auto& entry : m_banned) {
            if (entry.first.first == address) {
                return true;
            }
        }

        return false;
    }

    // 返回IP地址封锁的严重级别。如果没有被封锁，则返回0；如果被自动封锁，则返回1；否则返回2。
    int IsBannedLevel(const string& ip) {
        lock_guard<mutex> lock(m_mutex);

        uint32_t address = inet_addr(ip.c_str());
        if (address == INADDR_NONE) {
            return 0;
        }

        for (const auto& entry : m_banned) {
            if (entry.first.first == address) {
                return entry.second;
            }
        }

        return 0;
    }

    // 取消所有IP地址封锁。
    void ClearBanned() {
        lock_guard<mutex> lock(m_mutex);

        m_banned.clear();
    }

    // 将当前的封锁列表写入 banlist.dat 文件并清除不需要的条目。
    void DumpBanlist() {
        lock_guard<mutex> lock(m_mutex);

        ofstream fout("banlist.dat");
        if (!fout.is_open()) {
            return;
        }

        for (auto it = m_banned.begin(); it != m_banned.end(); ++it) {
            if (it->second == 0 || it->second == 1) {
                m_banned.erase(it);
            } else {
                fout << inet_ntoa({ it->first.first }) << "/" << CountBits(it->first.second) << "," << it->second << endl;
            }
        }

        fout.close();
    }

    // 删除已过期的封锁条目。
    void SweepBanned() {
        lock_guard<mutex> lock(m_mutex);

        uint32_t now = time(nullptr);
        for (auto it = m_banned.begin(); it != m_banned.end(); ++it) {
            if (it->second != 0 && it->second != 1 && now > it->second) {
                m_banned.erase(it);
            }
        }
    }
    scss
        Copy code
        1) {
            m_banned.erase(it);
            } else {
        fout << inet_ntoa({ it->first.first }) << "/" << CountBits(it->first.second) << "," << it->second << endl;
    }
}

fout.close();
}

// 删除已过期的封锁条目。
void SweepBanned() {
    lock_guard<mutex> lock(m_mutex);

    uint32_t now = time(nullptr);
    for (auto it = m_banned.begin(); it != m_banned.end(); ++it) {
        if (it->second != 0 && it->second != 1 && now > it->second) {
            m_banned.erase(it);
        }
    }
}
        private:
        // 计算掩码中的位数。
        int CountBits(uint32_t mask) {
            int count = 0;
            while (mask != 0) {
                count++;
                mask = mask << 1;
            }
            return count;
        }

        private:
        map<pair<uint32_t, uint32_t>, int> m_banned; // 存储封锁列表
        mutex m_mutex; // 保护封锁列表的互斥量
};

int main() {
    BanList banlist;
    // 封锁单个IP地址
    banlist.Ban("192.168.1.1");
    cout << "192.168.1.1 is banned: " << banlist.IsBanned("192.168.1.1") << endl;

    // 解锁单个IP地址
    banlist.Unban("192.168.1.1");
    cout << "192.168.1.1 is banned: " << banlist.IsBanned("192.168.1.1") << endl;

    // 封锁整个子网
    banlist.Ban("192.168.1.0/24");
    cout << "192.168.1.1 is banned: " << banlist.IsBanned("192.168.1.1") << endl;
    cout << "192.168.1.100 is banned: " << banlist.IsBanned("192.168.1.100") << endl;

    // 解锁整个子网
    banlist.Unban("192.168.1.0/24");
    cout << "192.168.1.1 is banned: " << banlist.IsBanned("192.168.1.1") << endl;
    cout << "192.168.1.100 is banned: " << banlist.IsBanned("192.168.1.100") << endl;

    // 将当前的封锁列表写入文件并清除不需要的条目
    banlist.Ban("192.168.1.1");
    banlist.Ban("192.168.1.0/24");
    banlist.DumpBanlist();
    banlist.ClearBanned();

    // 删除已过期的封锁条目
    banlist.Ban("192.168.1.1", time(nullptr) + 3600); // 1小时后过期
    banlist.Ban("192.168.1.0/24", time(nullptr) + 7200); // 2小时后过期
    banlist.SweepBanned();
    cout << "192.168.1.1 is banned: " << banlist.IsBanned("192.168.1.1") << endl;
    cout << "192.168.1.100 is banned: " << banlist.IsBanned("192.168.1.100") << endl;

    return 0;
}
