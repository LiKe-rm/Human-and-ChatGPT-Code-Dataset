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

    // ����IP��ַ���������ַ����õ�ַ����������ɹ����򷵻�true��
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

    // ����IP��ַ���������ֽ����õ�ַ����������ɹ����򷵻�true��
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

    // ����IP��ַ�жϸõ�ַ�Ƿ񱻷�����������������򷵻�true��
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

    // ����IP��ַ���������ؼ������û�б��������򷵻�0��������Զ��������򷵻�1�����򷵻�2��
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

    // ȡ������IP��ַ������
    void ClearBanned() {
        lock_guard<mutex> lock(m_mutex);

        m_banned.clear();
    }

    // ����ǰ�ķ����б�д�� banlist.dat �ļ����������Ҫ����Ŀ��
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

    // ɾ���ѹ��ڵķ�����Ŀ��
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

// ɾ���ѹ��ڵķ�����Ŀ��
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
        // ���������е�λ����
        int CountBits(uint32_t mask) {
            int count = 0;
            while (mask != 0) {
                count++;
                mask = mask << 1;
            }
            return count;
        }

        private:
        map<pair<uint32_t, uint32_t>, int> m_banned; // �洢�����б�
        mutex m_mutex; // ���������б�Ļ�����
};

int main() {
    BanList banlist;
    // ��������IP��ַ
    banlist.Ban("192.168.1.1");
    cout << "192.168.1.1 is banned: " << banlist.IsBanned("192.168.1.1") << endl;

    // ��������IP��ַ
    banlist.Unban("192.168.1.1");
    cout << "192.168.1.1 is banned: " << banlist.IsBanned("192.168.1.1") << endl;

    // ������������
    banlist.Ban("192.168.1.0/24");
    cout << "192.168.1.1 is banned: " << banlist.IsBanned("192.168.1.1") << endl;
    cout << "192.168.1.100 is banned: " << banlist.IsBanned("192.168.1.100") << endl;

    // ������������
    banlist.Unban("192.168.1.0/24");
    cout << "192.168.1.1 is banned: " << banlist.IsBanned("192.168.1.1") << endl;
    cout << "192.168.1.100 is banned: " << banlist.IsBanned("192.168.1.100") << endl;

    // ����ǰ�ķ����б�д���ļ����������Ҫ����Ŀ
    banlist.Ban("192.168.1.1");
    banlist.Ban("192.168.1.0/24");
    banlist.DumpBanlist();
    banlist.ClearBanned();

    // ɾ���ѹ��ڵķ�����Ŀ
    banlist.Ban("192.168.1.1", time(nullptr) + 3600); // 1Сʱ�����
    banlist.Ban("192.168.1.0/24", time(nullptr) + 7200); // 2Сʱ�����
    banlist.SweepBanned();
    cout << "192.168.1.1 is banned: " << banlist.IsBanned("192.168.1.1") << endl;
    cout << "192.168.1.100 is banned: " << banlist.IsBanned("192.168.1.100") << endl;

    return 0;
}
