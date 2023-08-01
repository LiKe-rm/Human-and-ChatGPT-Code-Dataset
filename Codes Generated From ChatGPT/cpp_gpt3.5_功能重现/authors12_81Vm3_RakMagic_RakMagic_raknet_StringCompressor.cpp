#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>

using namespace std;

// ������������ڵ�ṹ��
struct HuffmanNode {
    char ch;
    int freq;
    HuffmanNode *left;
    HuffmanNode *right;
    HuffmanNode(char c = '\0', int f = 0, HuffmanNode *l = nullptr,
        HuffmanNode *r = nullptr)
        : ch(c), freq(f), left(l), right(r) {}
};

// ����ȽϺ������������ȶ����еĽڵ�����
struct CompareNodes {
    bool operator()(HuffmanNode *n1, HuffmanNode *n2) {
        return n1->freq > n2->freq;
    }
};

// �����ַ���ѹ���ͽ�ѹ����
class StringCompressor {
    public:
    StringCompressor(int langId = 0): langId_(langId) {}

    // ѹ���ַ�����������������д�������
    void compress(const string &str, ostream &out) {
      // ͳ���ַ�����Ƶ��
        map<char, int> freqMap;
        for (char ch : str) {
            freqMap[ch]++;
        }

        // ������������
        priority_queue<HuffmanNode *, vector<HuffmanNode *>, CompareNodes>
            nodeQueue;
        for (auto it : freqMap) {
            nodeQueue.push(new HuffmanNode(it.first, it.second));
        }
        while (nodeQueue.size() > 1) {
            HuffmanNode *n1 = nodeQueue.top();
            nodeQueue.pop();
            HuffmanNode *n2 = nodeQueue.top();
            nodeQueue.pop();
            nodeQueue.push(new HuffmanNode('\0', n1->freq + n2->freq, n1, n2));
        }
        HuffmanNode *root = nodeQueue.top();

        // ���ɱ����
        map<char, string> codeTable;
        buildCodeTable(root, "", codeTable);

        // д������ID�ͱ����
        out.write(reinterpret_cast<char *>(&langId_), sizeof(langId_));
        int tableSize = codeTable.size();
        out.write(reinterpret_cast<char *>(&tableSize), sizeof(tableSize));
        for (auto it : codeTable) {
            out.write(&it.first, sizeof(it.first));
            int codeSize = it.second.size();
            out.write(reinterpret_cast<char *>(&codeSize), sizeof(codeSize));
            out.write(it.second.c_str(), codeSize);
        }

        // д��������ַ�������
        for (char ch : str) {
            string code = codeTable[ch];
            for (char bit : code) {
                if (bit == '0') {
                    out.put(0);
                } else {
                    out.put(1);
                }
            }
        }
    }

    // ���������ж�ȡ�������ݲ�����Ϊԭʼ�ַ�������
    string decompress(istream &in) {
      // ��ȡ����ID�ͱ����
        int langId, tableSize;
        in.read(reinterpret_cast<char *>(&langId), sizeof(langId));
        in.read(reinterpret_cast<char *>(&tableSize), sizeof(tableSize));
        map<string, char> decodeTable;
        for (int i = 0; i < tableSize; i++) {
            char ch;
            int codeSize;
            in.read(&ch, sizeof(ch));
            in.read(reinterpret_cast<char *>(&codeSize), sizeof(codeSize));
            string code(codeSize, '\0');
            in.read(&code[0], codeSize);
            decodeTable[code] = ch;
        }

        // ����������ַ�������
        string result;
        string code;
        char bit;
        while (in.get(bit)) {
            code += (bit == 0 ? '0' : '1');
            auto it = decodeTable.find(code);
            if (it != decodeTable.end()) {
                result += it->second;
                code = "";
            }
        }

        return result;
    }

    private:
    int langId_;

    // �ݹ����ɱ����
    void buildCodeTable(HuffmanNode *node, string code,
        map<char, string> &codeTable) {
        if (node->left == nullptr && node->right == nullptr) {
            codeTable[node->ch] = code;
        } else {
            buildCodeTable(node->left, code + '0', codeTable);
            buildCodeTable(node->right, code + '1', codeTable);
        }
    }
};

int main() {
// ���Դ���
    StringCompressor compressor(1);

    string str = "hello world";
    cout << "ԭʼ�ַ�����" << str << endl;

    stringstream ss;
    compressor.compress(str, ss);
    cout << "ѹ��������ݴ�С��" << ss.tellp() << endl;

    string compressedStr = ss.str();
    cout << "ѹ��������ݣ�" << compressedStr << endl;

    string decompressedStr = compressor.decompress(ss);
    cout << "��ѹ����ַ�����" << decompressedStr << endl;

    return 0;
}