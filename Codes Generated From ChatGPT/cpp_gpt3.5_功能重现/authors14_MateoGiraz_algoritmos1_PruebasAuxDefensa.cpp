#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_set>
#include <map>
#include <queue>
#include <algorithm>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// 解析链表
ListNode* parseLinkedList(const string& input) {
    ListNode dummy(0), *cur = &dummy;
    istringstream ss(input);
    int value;

    while (ss >> value) {
        cur->next = new ListNode(value);
        cur = cur->next;
    }
    return dummy.next;
}

// 计算两个链表的交集
void printIntersection(ListNode *head1, ListNode *head2) {
    unordered_set<int> set1, set2;

    while (head1) {
        set1.insert(head1->val);
        head1 = head1->next;
    }
    while (head2) {
        set2.insert(head2->val);
        head2 = head2->next;
    }

    vector<int> result;
    for (int value : set1) {
        if (set2.count(value)) {
            result.push_back(value);
        }
    }

    sort(result.begin(), result.end());
    for (int value : result) {
        cout << value << " ";
    }
    cout << endl;
}

// 解析字典
vector<map<int, int>> parseDictionaries(const string& input, int numDicts) {
    istringstream ss(input);
    vector<map<int, int>> dictionaries(numDicts);
    int key, value;

    for (int i = 0; i < numDicts; ++i) {
        while (ss >> key >> value) {
            dictionaries[i][key] = value;
        }
    }
    return dictionaries;
}

// 判断三个字典是否具有相同的元素
void haveCommonElement(vector<map<int, int>>& dictionaries) {
    bool hasCommon = false;

    for (const auto& [key, value] : dictionaries[0]) {
        if (dictionaries[1].count(key) && dictionaries[2].count(key)) {
            hasCommon = true;
            break;
        }
    }

    cout << (hasCommon ? "Yes" : "No") << endl;
}

// 解析二叉树
TreeNode* parseBinaryTree(const string& input) {
    istringstream ss(input);
    queue<TreeNode*> q;
    int value;

    if (!(ss >> value)) return nullptr;

    TreeNode *root = new TreeNode(value);
    q.push(root);

    while (!q.empty() && ss >> value) {
        TreeNode *node = q.front();
        q.pop();

        node->left = new TreeNode(value);
        q.push(node->left);

        if (ss >> value) {
            node->right = new TreeNode(value);
            q.push(node->right);
        }
    }
    return root;
}

// 列出二叉树的所有叶子节点
void printLeafNodes(TreeNode *root) {
    if (!root) return;
    if (!root->left && !root->right) {
        cout << root->val << " ";
    }
    printLeafNodes(root->left);
    printLeafNodes(root->right);
}

// 判断一个链表中的元素是否包含在另一个链表中
void containsAllElements(ListNode *list1, ListNode *list2) {
unordered_set<int> set2;
while (list2) {
    set2.insert(list2->val);
    list2 = list2->next;
}

ListNode *cur = list1;
bool containsAll = true;
while (cur) {
    if (set2.count(cur->val) == 0) {
        containsAll = false;
        break;
    }
    cur = cur->next;
}

cout << (containsAll ? "Yes" : "No") << endl;
}

// 解析优先队列
vector<priority_queue<int>> parsePriorityQueues(const string& input, int numPQs) {
istringstream ss(input);
vector<priority_queue<int>> priorityQueues(numPQs);
int value;
for (int i = 0; i < numPQs; ++i) {
    while (ss >> value) {
        priorityQueues[i].push(value);
    }
}
return priorityQueues;
}

// 合并两个优先队列
void mergePriorityQueues(priority_queue<int>& pq1, priority_queue<int>& pq2) {
while (!pq2.empty()) {
pq1.push(pq2.top());
pq2.pop();
}
while (!pq1.empty()) {
    cout << pq1.top() << " ";
    pq1.pop();
}
cout << endl;
}

// 按层级列出二叉树的叶子节点
void printLeavesByLevel(TreeNode *root) {
if (!root) return;
queue<TreeNode*> q;
q.push(root);

while (!q.empty()) {
    int levelSize = q.size();
    bool hasLeaves = false;
    vector<int> leaves;

    for (int i = 0; i < levelSize; ++i) {
        TreeNode *node = q.front();
        q.pop();

        if (!node->left && !node->right) {
            hasLeaves = true;
            leaves.push_back(node->val);
        }

        if (node->left) q.push(node->left);
        if (node->right) q.push(node->right);
    }

    if (hasLeaves) {
        for (int value : leaves) {
            cout << value << " ";
        }
        cout << endl;
    }
}
}

int main() {
string input1 = "1 2 3 4 5";
string input2 = "4 5 6 7 8";
ListNode *head1 = parseLinkedList(input1);
ListNode *head2 = parseLinkedList(input2);
printIntersection(head1, head2);
string input3 = "1 2 3 4 5 6 7 8 9";
TreeNode *root = parseBinaryTree(input3);
printLeafNodes(root);
cout << endl;
printLeavesByLevel(root);

string input4 = "1 3 5 7";
string input5 = "2 4 6 8";
ListNode *head3 = parseLinkedList(input4);
ListNode *head4 = parseLinkedList(input5);
containsAllElements(head3, head4);

string input6 = "3 1 4 1 5 9 2 6";
string input7 = "5 3 5 8 9 7 9 3 2";
vector<priority_queue<int>> pqs = parsePriorityQueues(input6 + " " + input7, 2);
mergePriorityQueues(pqs[0], pqs[1]);
string input8 = "1 1 2 2 3 3 4 4 5 5";
string input9 = "6 6 7 7 8 8 9 9 10 10";
string input10 = "11 11 12 12 13 13 14 14 15 15";
vector<map<int, int>> dictionaries = parseDictionaries(input8 + " " + input9 + " " + input10, 3);
haveCommonElement(dictionaries);

return 0;
}

