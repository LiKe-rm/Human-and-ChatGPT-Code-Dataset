#include <iostream>
#include <vector>
#include <stack>
#include <set>
#include <queue>
#include <sstream>
#include <algorithm>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// Helper function to insert values into a BST
TreeNode* insertToBST(TreeNode* root, int val) {
    if (!root) return new TreeNode(val);

    if (val < root->val) {
        root->left = insertToBST(root->left, val);
    } else {
        root->right = insertToBST(root->right, val);
    }

    return root;
}

// 1. Inorder traversal of a BST
void inorderTraversal(TreeNode* root, vector<int>& result) {
    if (!root) return;

    inorderTraversal(root->left, result);
    result.push_back(root->val);
    inorderTraversal(root->right, result);
}

// 2. Merge two sorted lists
vector<int> mergeSortedLists(vector<int>& list1, vector<int>& list2) {
    vector<int> mergedList;
    int i = 0, j = 0;

    while (i < list1.size() && j < list2.size()) {
        if (list1[i] < list2[j]) {
            mergedList.push_back(list1[i++]);
        } else {
            mergedList.push_back(list2[j++]);
        }
    }

    while (i < list1.size()) {
        mergedList.push_back(list1[i++]);
    }

    while (j < list2.size()) {
        mergedList.push_back(list2[j++]);
    }

    return mergedList;
}

// 3. Check if one stack contains another stack
bool isStackContained(stack<int>& stack1, stack<int>& stack2) {
    stack<int> temp1, temp2;

    while (!stack1.empty() && !stack2.empty()) {
        if (stack1.top() == stack2.top()) {
            temp1.push(stack1.top());
            temp2.push(stack2.top());
            stack1.pop();
            stack2.pop();
        } else {
            stack1.pop();
        }
    }

    bool isContained = stack2.empty();

    while (!temp1.empty()) {
        stack1.push(temp1.top());
        temp1.pop();
    }

    while (!temp2.empty()) {
        stack2.push(temp2.top());
        temp2.pop();
    }

    return isContained;
}

// 4. Get all duplicate elements from a multiset
vector<int> getDuplicates(multiset<int>& ms) {
    vector<int> duplicates;

    for (auto it = ms.begin(); it != ms.end();) {
        auto range = ms.equal_range(*it);
        if (distance(range.first, range.second) > 1) {
            duplicates.push_back(*it);
        }
        it = range.second;
    }

    return duplicates;
}

// 5. Compute the XOR of two multisets
multiset<int> multisetXOR(multiset<int>& ms1, multiset<int>& ms2) {
    multiset<int> result;

    for (auto it = ms1.begin(); it != ms1.end();) {
        auto range = ms1.equal_range(*it);
        int count1 = distance(range.first, range.second);
        int count2 = ms2.count(*it);
        int xorCount = count1 ^ count2;
        for (int i = 0; i < xorCount; ++i) {
            result.insert(*it);
        }
        it = range.second;
    }

    for (auto it = ms2.begin(); it != ms2.end();) {
auto range = ms2.equal_range(*it);
if (ms1.count(*it) == 0) {
int count2 = distance(range.first, range.second);
for (int i = 0; i < count2; ++i) {
result.insert(*it);
}
}
it = range.second;
}
return result;
}

// 6. Find the element with the smallest priority in a priority queue
int findSmallestPriority(priority_queue<int, vector<int>, greater<int>>& pq) {
if (pq.empty()) return -1;
return pq.top();
}

int main() {
// Example input strings:
string bstInput = "5 3 7 2 4 6 8";
string list1Input = "1 3 5 7 9";
string list2Input = "2 4 6 8 10";
string stack1Input = "1 2 3 4 5";
string stack2Input = "3 4";
string multiset1Input = "1 2 3 3 4 4 4 5";
string multiset2Input = "2 3 3 4 4 6 7";

stringstream ss;

// Parse BST input
TreeNode* bst = NULL;
ss.str(bstInput);
int val;
while (ss >> val) {
    bst = insertToBST(bst, val);
}
ss.clear();

// Test inorder traversal
vector<int> inorder;
inorderTraversal(bst, inorder);
cout << "Inorder traversal: ";
for (int num : inorder) {
    cout << num << " ";
}
cout << endl;

// Parse list inputs
vector<int> list1, list2;
ss.str(list1Input);
while (ss >> val) {
    list1.push_back(val);
}
ss.clear();

ss.str(list2Input);
while (ss >> val) {
    list2.push_back(val);
}
ss.clear();

// Test merge sorted lists
vector<int> merged = mergeSortedLists(list1, list2);
cout << "Merged sorted lists: ";
for (int num : merged) {
    cout << num << " ";
}
cout << endl;

// Parse stack inputs
stack<int> stack1, stack2;
ss.str(stack1Input);
while (ss >> val) {
    stack1.push(val);
}
ss.clear();

ss.str(stack2Input);
while (ss >> val) {
    stack2.push(val);
}
ss.clear();

// Test if one stack contains another stack
cout << "Stack1 contains Stack2: " << (isStackContained(stack1, stack2) ? "true" : "false") << endl;

// Parse multiset inputs
multiset<int> ms1, ms2;
ss.str(multiset1Input);
while (ss >> val) {
    ms1.insert(val);
}
ss.clear();

ss.str(multiset2Input);
while (ss >> val) {
    ms2.insert(val);
}
ss.clear();

// Test get all duplicate elements from a multiset
vector<int> duplicates = getDuplicates(ms1);
cout << "Duplicate elements: ";
for (int num : duplicates) {
    cout << num << " ";
}
cout << endl;

// Test XOR of two multisets
multiset<int> msXOR = multisetXOR(ms1, ms2);
cout << "Multiset XOR: ";
for (auto num : msXOR) {
cout << num << " ";
}
cout << endl;
// Parse priority queue input
priority_queue<int, vector<int>, greater<int>> pq;
string pqInput = "3 1 7 5 2 8 4";
ss.str(pqInput);
while (ss >> val) {
    pq.push(val);
}
ss.clear();

// Test find the element with the smallest priority in a priority queue
cout << "Element with the smallest priority: " << findSmallestPriority(pq) << endl;

return 0;
}

