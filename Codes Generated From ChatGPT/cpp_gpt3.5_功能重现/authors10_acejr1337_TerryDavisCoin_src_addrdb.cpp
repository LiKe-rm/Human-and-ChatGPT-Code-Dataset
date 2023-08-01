#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

// 定义Bitcoin协议的版本信息
const int BITCOIN_VERSION = 1;

// 定义地址数据库和禁止IP数据库的文件名
const string ADDR_DB_FILE = "addr.db";
const string BAN_DB_FILE = "ban.db";

// 定义地址和禁止IP的结构体
struct CAddr {
    string addr;    // 地址
    long long nTime;    // 时间戳

    // 序列化函数
    template <typename Stream>
    void Serialize(Stream& s) const {
        s << addr;
        s << nTime;
    }

    // 反序列化函数
    template <typename Stream>
    void Unserialize(Stream& s) {
        s >> addr;
        s >> nTime;
    }
};

struct CBan {
    string strSubNet;    // 网络地址
    long long nCreateTime;    // 创建时间
    long long nBanUntil;    // 禁止到期时间

    // 序列化函数
    template <typename Stream>
    void Serialize(Stream& s) const {
        s << strSubNet;
        s << nCreateTime;
        s << nBanUntil;
    }

    // 反序列化函数
    template <typename Stream>
    void Unserialize(Stream& s) {
        s >> strSubNet;
        s >> nCreateTime;
        s >> nBanUntil;
    }
};

// 定义序列化和反序列化模板函数
template <typename T>
void Serialize(T& obj, vector<char>& serialized) {
    stringstream ss;
    obj.Serialize(ss);
    string str = ss.str();
    serialized.resize(str.size());
    memcpy(serialized.data(), str.data(), str.size());
}

template <typename T>
void Deserialize(T& obj, const vector<char>& serialized) {
    stringstream ss;
    string str(serialized.data(), serialized.size());
    ss.str(str);
    obj.Unserialize(ss);
}

// 定义CBanDB类，用于禁止IP数据库的读写操作
class CBanDB {
    public:
        // 写入禁止IP数据
    bool WriteBan(const CBan& ban) {
        // 打开禁止IP数据库文件
        fstream file(BAN_DB_FILE, ios::binary | ios::in | ios::out | ios::app);
        if (!file) {
            cerr << "Failed to open ban database file!" << endl;
            return false;
        }

        // 序列化禁止IP数据
        vector<char> serialized;
        Serialize(ban, serialized);

        // 写入数据到文件
        file.write(serialized.data(), serialized.size());

        // 关闭文件
        file.close();

        return true;
    }

    // 读取禁止IP数据
    vector<CBan> ReadBans() {
        vector<CBan> bans;

        // 打开禁止IP数据库文件
        fstream file(BAN_DB_FILE, ios::binary | ios::in | ios::out);
        if (!file) {
            cerr << "Failed to open ban database file!" << endl;
            return bans;
        }

        // 从文件读取数据
        while (file) {
            // 读取数据长度
            int length = 0;
            file.read((char*)&length, sizeof(int));
            if (!file || length == 0) {
                break;
            }

            // 读取数据
            vector<char> serialized(length);
            file.read(serialized.data(), length);
            if (!file) {
                cerr << "Failed to read ban data from file!" << endl;
                break;
            }

            // 反序列化数据
            CBan ban;
            Deserialize(ban, serialized);
            bans.push_back(ban);
        }

        // 关闭文件
        file.close();

        return bans;
    }
};

// 定义CAddrDB类，用于地址数据库的读写操作
class CAddrDB {
    public:
    // 写入地址数据
    bool WriteAddr(const CAddr& addr) {
    // 打开地址数据库文件
        fstream file(ADDR_DB_FILE, ios::binary | ios::in | ios::out | ios::app);
        if (!file) {
            cerr << "Failed to open address database file!" << endl;
            return false;
        }
            // 序列化地址数据
        vector<char> serialized;
        Serialize(addr, serialized);

        // 写入数据到文件
        file.write(serialized.data(), serialized.size());

        // 关闭文件
        file.close();

        return true;
    }

    // 读取地址数据
    vector<CAddr> ReadAddrs() {
        vector<CAddr> addrs;

        // 打开地址数据库文件
        fstream file(ADDR_DB_FILE, ios::binary | ios::in | ios::out);
        if (!file) {
            cerr << "Failed to open address database file!" << endl;
            return addrs;
        }

        // 从文件读取数据
        while (file) {
            // 读取数据长度
            int length = 0;
            file.read((char*)&length, sizeof(int));
            if (!file || length == 0) {
                break;
            }

            // 读取数据
            vector<char> serialized(length);
            file.read(serialized.data(), length);
            if (!file) {
                cerr << "Failed to read address data from file!" << endl;
                break;
            }

            // 反序列化数据
            CAddr addr;
            Deserialize(addr, serialized);
            addrs.push_back(addr);
        }

        // 关闭文件
        file.close();

        return addrs;
    }
};

// 序列化数据到文件
template <typename T>
void SerializeFileDB(const vector<T>& data, const string& file) {
// 打开文件
    ofstream fout(file, ios::binary);
    if (!fout) {
        cerr << "Failed to open file for writing!" << endl;
        return;
    }
    // 写入数据
    for (const T& item : data) {
        // 写入版本信息
        fout.write((char*)&BITCOIN_VERSION, sizeof(int));

        // 序列化数据
        vector<char> serialized;
        Serialize(item, serialized);

        // 写入数据长度和数据
        int length = serialized.size();
        fout.write((char*)&length, sizeof(int));
        fout.write(serialized.data(), serialized.size());
    }

    // 关闭文件
    fout.close();
}

// 从文件反序列化数据
template <typename T>
vector<T> DeserializeFileDB(const string& file) {
    vector<T> data;
    // 打开文件
    ifstream fin(file, ios::binary);
    if (!fin) {
        cerr << "Failed to open file for reading!" << endl;
        return data;
    }

    // 读取数据
    while (fin) {
        // 读取版本信息
        int version = 0;
        fin.read((char*)&version, sizeof(int));
        if (!fin || version != BITCOIN_VERSION) {
            break;
        }

        // 读取数据长度
        int length = 0;
        fin.read((char*)&length, sizeof(int));
        if (!fin || length == 0) {
            break;
        }

        // 读取数据
        vector<char> serialized(length);
        fin.read(serialized.data(), length);
        if (!fin) {
            cerr << "Failed to read data from file!" << endl;
            break;
        }

        // 反序列化数据
        T item;
        Deserialize(item, serialized);
        data.push_back(item);
    }

    // 关闭文件
    fin.close();

    return data;
}

