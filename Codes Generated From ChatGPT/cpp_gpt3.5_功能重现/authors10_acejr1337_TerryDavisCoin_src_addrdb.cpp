#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

// ����BitcoinЭ��İ汾��Ϣ
const int BITCOIN_VERSION = 1;

// �����ַ���ݿ�ͽ�ֹIP���ݿ���ļ���
const string ADDR_DB_FILE = "addr.db";
const string BAN_DB_FILE = "ban.db";

// �����ַ�ͽ�ֹIP�Ľṹ��
struct CAddr {
    string addr;    // ��ַ
    long long nTime;    // ʱ���

    // ���л�����
    template <typename Stream>
    void Serialize(Stream& s) const {
        s << addr;
        s << nTime;
    }

    // �����л�����
    template <typename Stream>
    void Unserialize(Stream& s) {
        s >> addr;
        s >> nTime;
    }
};

struct CBan {
    string strSubNet;    // �����ַ
    long long nCreateTime;    // ����ʱ��
    long long nBanUntil;    // ��ֹ����ʱ��

    // ���л�����
    template <typename Stream>
    void Serialize(Stream& s) const {
        s << strSubNet;
        s << nCreateTime;
        s << nBanUntil;
    }

    // �����л�����
    template <typename Stream>
    void Unserialize(Stream& s) {
        s >> strSubNet;
        s >> nCreateTime;
        s >> nBanUntil;
    }
};

// �������л��ͷ����л�ģ�庯��
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

// ����CBanDB�࣬���ڽ�ֹIP���ݿ�Ķ�д����
class CBanDB {
    public:
        // д���ֹIP����
    bool WriteBan(const CBan& ban) {
        // �򿪽�ֹIP���ݿ��ļ�
        fstream file(BAN_DB_FILE, ios::binary | ios::in | ios::out | ios::app);
        if (!file) {
            cerr << "Failed to open ban database file!" << endl;
            return false;
        }

        // ���л���ֹIP����
        vector<char> serialized;
        Serialize(ban, serialized);

        // д�����ݵ��ļ�
        file.write(serialized.data(), serialized.size());

        // �ر��ļ�
        file.close();

        return true;
    }

    // ��ȡ��ֹIP����
    vector<CBan> ReadBans() {
        vector<CBan> bans;

        // �򿪽�ֹIP���ݿ��ļ�
        fstream file(BAN_DB_FILE, ios::binary | ios::in | ios::out);
        if (!file) {
            cerr << "Failed to open ban database file!" << endl;
            return bans;
        }

        // ���ļ���ȡ����
        while (file) {
            // ��ȡ���ݳ���
            int length = 0;
            file.read((char*)&length, sizeof(int));
            if (!file || length == 0) {
                break;
            }

            // ��ȡ����
            vector<char> serialized(length);
            file.read(serialized.data(), length);
            if (!file) {
                cerr << "Failed to read ban data from file!" << endl;
                break;
            }

            // �����л�����
            CBan ban;
            Deserialize(ban, serialized);
            bans.push_back(ban);
        }

        // �ر��ļ�
        file.close();

        return bans;
    }
};

// ����CAddrDB�࣬���ڵ�ַ���ݿ�Ķ�д����
class CAddrDB {
    public:
    // д���ַ����
    bool WriteAddr(const CAddr& addr) {
    // �򿪵�ַ���ݿ��ļ�
        fstream file(ADDR_DB_FILE, ios::binary | ios::in | ios::out | ios::app);
        if (!file) {
            cerr << "Failed to open address database file!" << endl;
            return false;
        }
            // ���л���ַ����
        vector<char> serialized;
        Serialize(addr, serialized);

        // д�����ݵ��ļ�
        file.write(serialized.data(), serialized.size());

        // �ر��ļ�
        file.close();

        return true;
    }

    // ��ȡ��ַ����
    vector<CAddr> ReadAddrs() {
        vector<CAddr> addrs;

        // �򿪵�ַ���ݿ��ļ�
        fstream file(ADDR_DB_FILE, ios::binary | ios::in | ios::out);
        if (!file) {
            cerr << "Failed to open address database file!" << endl;
            return addrs;
        }

        // ���ļ���ȡ����
        while (file) {
            // ��ȡ���ݳ���
            int length = 0;
            file.read((char*)&length, sizeof(int));
            if (!file || length == 0) {
                break;
            }

            // ��ȡ����
            vector<char> serialized(length);
            file.read(serialized.data(), length);
            if (!file) {
                cerr << "Failed to read address data from file!" << endl;
                break;
            }

            // �����л�����
            CAddr addr;
            Deserialize(addr, serialized);
            addrs.push_back(addr);
        }

        // �ر��ļ�
        file.close();

        return addrs;
    }
};

// ���л����ݵ��ļ�
template <typename T>
void SerializeFileDB(const vector<T>& data, const string& file) {
// ���ļ�
    ofstream fout(file, ios::binary);
    if (!fout) {
        cerr << "Failed to open file for writing!" << endl;
        return;
    }
    // д������
    for (const T& item : data) {
        // д��汾��Ϣ
        fout.write((char*)&BITCOIN_VERSION, sizeof(int));

        // ���л�����
        vector<char> serialized;
        Serialize(item, serialized);

        // д�����ݳ��Ⱥ�����
        int length = serialized.size();
        fout.write((char*)&length, sizeof(int));
        fout.write(serialized.data(), serialized.size());
    }

    // �ر��ļ�
    fout.close();
}

// ���ļ������л�����
template <typename T>
vector<T> DeserializeFileDB(const string& file) {
    vector<T> data;
    // ���ļ�
    ifstream fin(file, ios::binary);
    if (!fin) {
        cerr << "Failed to open file for reading!" << endl;
        return data;
    }

    // ��ȡ����
    while (fin) {
        // ��ȡ�汾��Ϣ
        int version = 0;
        fin.read((char*)&version, sizeof(int));
        if (!fin || version != BITCOIN_VERSION) {
            break;
        }

        // ��ȡ���ݳ���
        int length = 0;
        fin.read((char*)&length, sizeof(int));
        if (!fin || length == 0) {
            break;
        }

        // ��ȡ����
        vector<char> serialized(length);
        fin.read(serialized.data(), length);
        if (!fin) {
            cerr << "Failed to read data from file!" << endl;
            break;
        }

        // �����л�����
        T item;
        Deserialize(item, serialized);
        data.push_back(item);
    }

    // �ر��ļ�
    fin.close();

    return data;
}

