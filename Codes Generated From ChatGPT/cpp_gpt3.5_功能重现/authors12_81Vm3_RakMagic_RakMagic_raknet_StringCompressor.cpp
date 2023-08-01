#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>

using namespace std;

// 定义哈夫曼树节点结构体
struct HuffmanNode {
    char ch;
    int freq;
    HuffmanNode *left;
    HuffmanNode *right;
    HuffmanNode(char c = '\0', int f = 0, HuffmanNode *l = nullptr,
        HuffmanNode *r = nullptr)
        : ch(c), freq(f), left(l), right(r) {}
};

// 定义比较函数，用于优先队列中的节点排序
struct CompareNodes {
    bool operator()(HuffmanNode *n1, HuffmanNode *n2) {
        return n1->freq > n2->freq;
    }
};

// 定义字符串压缩和解压缩类
class StringCompressor {
    public:
    StringCompressor(int langId = 0): langId_(langId) {}

    // 压缩字符串并将编码后的数据写入输出流
    void compress(const string &str, ostream &out) {
      // 统计字符出现频率
        map<char, int> freqMap;
        for (char ch : str) {
            freqMap[ch]++;
        }

        // 构建哈夫曼树
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

        // 生成编码表
        map<char, string> codeTable;
        buildCodeTable(root, "", codeTable);

        // 写入语言ID和编码表
        out.write(reinterpret_cast<char *>(&langId_), sizeof(langId_));
        int tableSize = codeTable.size();
        out.write(reinterpret_cast<char *>(&tableSize), sizeof(tableSize));
        for (auto it : codeTable) {
            out.write(&it.first, sizeof(it.first));
            int codeSize = it.second.size();
            out.write(reinterpret_cast<char *>(&codeSize), sizeof(codeSize));
            out.write(it.second.c_str(), codeSize);
        }

        // 写入编码后的字符串数据
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

    // 从输入流中读取编码数据并解码为原始字符串数据
    string decompress(istream &in) {
      // 读取语言ID和编码表
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

        // 解码编码后的字符串数据
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

    // 递归生成编码表
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
// 测试代码
    StringCompressor compressor(1);

    string str = "hello world";
    cout << "原始字符串：" << str << endl;

    stringstream ss;
    compressor.compress(str, ss);
    cout << "压缩后的数据大小：" << ss.tellp() << endl;

    string compressedStr = ss.str();
    cout << "压缩后的数据：" << compressedStr << endl;

    string decompressedStr = compressor.decompress(ss);
    cout << "解压后的字符串：" << decompressedStr << endl;

    return 0;
}