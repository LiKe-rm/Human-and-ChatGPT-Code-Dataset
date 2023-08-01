#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_map>
#include <bitset>

using namespace std;

// 哈夫曼树节点结构体
struct HuffmanNode {
    char ch;  // 字符
    int freq; // 频率
    string code; // 哈夫曼编码
    HuffmanNode *left, *right; // 左右子树指针

    HuffmanNode(char c, int f): ch(c), freq(f), left(nullptr), right(nullptr) {}
};

// 哈夫曼树节点比较函数
struct cmp {
    bool operator()(HuffmanNode* a, HuffmanNode* b) const {
        return a->freq > b->freq;
    }
};

// 生成频率表
unordered_map<char, int> generateFreqTable(string& data) {
    unordered_map<char, int> freqTable;
    for (char c : data) {
        freqTable[c]++;
    }
    return freqTable;
}

// 构建哈夫曼树
HuffmanNode* buildHuffmanTree(unordered_map<char, int>& freqTable) {
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, cmp> pq;
    for (auto it = freqTable.begin(); it != freqTable.end(); it++) {
        pq.push(new HuffmanNode(it->first, it->second));
    }
    while (pq.size() > 1) {
        HuffmanNode *left = pq.top(); pq.pop();
        HuffmanNode *right = pq.top(); pq.pop();
        HuffmanNode *parent = new HuffmanNode('\0', left->freq + right->freq);
        parent->left = left;
        parent->right = right;
        pq.push(parent);
    }
    return pq.top();
}

// 递归遍历哈夫曼树，得出每个字符的哈夫曼编码
void getHuffmanCode(HuffmanNode* root, string code, unordered_map<char, string>& codeTable) {
    if (!root) return;
    if (root->ch != '\0') {
        codeTable[root->ch] = code;
        root->code = code;
    }
    getHuffmanCode(root->left, code + "0", codeTable);
    getHuffmanCode(root->right, code + "1", codeTable);
}

// 压缩数据
string compressData(string& data, unordered_map<char, string>& codeTable) {
    string compressedData = "";
    for (char c : data) {
        compressedData += codeTable[c];
    }
    int padding = 8 - compressedData.size() % 8; // 计算需要填充的位数
    if (padding < 8) {
        compressedData += string(padding, '0');
    }
    int len = compressedData.size() / 8;
    string res = "";
    for (int i = 0; i < len; i++) {
        bitset<8> bits(compressedData.substr(i * 8, 8));
        res += char(bits.to_ulong());
    }
    return res;
}

// 测试压缩算法
int main() {
    string data = "hello world";
    unordered_map<char, int> freqTable = generateFreqTable(data);
    HuffmanNode *root = buildHuffmanTree(freqTable);
    unordered_map<char, string> codeTable;
    getHuffmanCode(root, "", codeTable);
    string compressedData = compressData(data, codeTable);
    cout << "Original data: " << data << endl;
    cout << "Compressed data: " << compressedData << endl;
    return 0;
}
