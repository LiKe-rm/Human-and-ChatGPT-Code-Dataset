#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <limits>
#include <algorithm>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

// 计算两个向量的互信息
double mutual_information(const VectorXd &a, const VectorXd &b) {
    double result = 0.0;
    VectorXd joint_entropy = a.cwiseProduct(b);
    VectorXd a_entropy = a.cwiseProduct(a);
    VectorXd b_entropy = b.cwiseProduct(b);

    for (int i = 0; i < a.size(); i++) {
        if (joint_entropy(i) > 0) {
            result += joint_entropy(i) * log2(joint_entropy(i) / (a_entropy(i) * b_entropy(i)));
        }
    }
    return result;
}

// 使用 Kruskal 算法计算最大生成树
vector<pair<int, int>> kruskal_algorithm(const MatrixXd &mutual_info, int n) {
    vector<pair<int, int>> edges;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            edges.push_back(make_pair(i, j));
        }
    }

    sort(edges.begin(), edges.end(), [&](const pair<int, int> &a, const pair<int, int> &b) {
        return mutual_info(a.first, a.second) > mutual_info(b.first, b.second);
    });

    vector<int> parent(n);
    for (int i = 0; i < n; ++i) {
        parent[i] = i;
    }

    function<int(int)> find = [&](int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    };

    vector<pair<int, int>> mst;
    for (const auto &e : edges) {
        int u = e.first, v = e.second;
        int pu = find(u), pv = find(v);
        if (pu != pv) {
            mst.push_back(e);
            parent[pv] = pu;
        }
    }
    return mst;
}

// 构建 Chow-Liu 树
vector<pair<int, int>> build_chow_liu_tree(const MatrixXd &data, double threshold) {
    int n = data.rows();
    int m = data.cols();

    // 计算互信息矩阵
    MatrixXd mutual_info(n, n);
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            mutual_info(i, j) = mutual_information(data.row(i), data.row(j));
            mutual_info(j, i) = mutual_info(i, j);
        }
    }

    // 使用 Kruskal 算法计算最大生成树
    vector<pair<int, int>> mst = kruskal_algorithm(mutual_info, n);

    // 使用信息阈值筛选边
    vector<pair<int, int>> chow_liu_tree;
    for (const auto &e : mst) {
        int u = e.first, v = e.second;
        if (mutual_info(u, v) >= threshold) {
            chow_liu_tree.push_back(e);
        }
    }

    return chow_liu_tree;
    }
