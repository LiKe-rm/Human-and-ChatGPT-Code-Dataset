#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Node {
    int left, right;
    int left_num, right_num;
    int mx, mx_num;
};

class SegmentTree {
private:
    vector<int> arr;
    vector<Node> tree;

    void build(int idx, int left, int right) {
        tree[idx].left = left;
        tree[idx].right = right;
        if (left == right) {
            tree[idx].left_num = tree[idx].right_num = tree[idx].mx = arr[left];
            tree[idx].mx_num = 1;
            return;
        }

        int mid = left + (right - left) / 2;
        build(idx * 2, left, mid);
        build(idx * 2 + 1, mid + 1, right);

        if (tree[idx * 2].mx == tree[idx * 2 + 1].mx) {
            tree[idx].mx = tree[idx * 2].mx;
            tree[idx].mx_num = tree[idx * 2].mx_num + tree[idx * 2 + 1].mx_num;
        } else {
            if (tree[idx * 2].mx_num > tree[idx * 2 + 1].mx_num) {
                tree[idx].mx = tree[idx * 2].mx;
                tree[idx].mx_num = tree[idx * 2].mx_num;
            } else {
                tree[idx].mx = tree[idx * 2 + 1].mx;
                tree[idx].mx_num = tree[idx * 2 + 1].mx_num;
            }
        }

        tree[idx].left_num = tree[idx * 2].left_num;
        tree[idx].right_num = tree[idx * 2 + 1].right_num;
    }

    Node query(int idx, int left, int right) {
        if (left <= tree[idx].left && tree[idx].right <= right) {
            return tree[idx];
        }

        int mid = tree[idx].left + (tree[idx].right - tree[idx].left) / 2;
        if (right <= mid) {
            return query(idx * 2, left, right);
        } else if (left > mid) {
            return query(idx * 2 + 1, left, right);
        } else {
            Node left_res = query(idx * 2, left, mid);
            Node right_res = query(idx * 2 + 1, mid + 1, right);
            Node res;
            res.left = left_res.left;
            res.right = right_res.right;

            if (left_res.mx == right_res.mx) {
                res.mx = left_res.mx;
                res.mx_num = left_res.mx_num + right_res.mx_num;
            } else {
                if (left_res.mx_num > right_res.mx_num) {
                    res.mx = left_res.mx;
                    res.mx_num = left_res.mx_num;
                } else {
                    res.mx = right_res.mx;
                    res.mx_num = right_res.mx_num;
                }
            }

            res.left_num = left_res.left_num;
            res.right_num = right_res.right_num;

            return res;
        }
    }

public:
    SegmentTree(const vector<int> &data) {
        arr = data;
        tree.resize(4 * arr.size());
        build(1, 0, arr.size() - 1);
    }

    int query_max_frequency(int left, int right) {
    Node res = query(1, left, right);
    return res.mx_num;
    }
};

