#include <iostream>
#include <vector>
#include <algorithm>

struct Edge {
    int source;
    int destination;
    int weight;
};

bool compareEdges(Edge a, Edge b) {
    return a.weight < b.weight;
}

int find(std::vector<int>& parent, int x) {
    if (parent[x] == x) {
        return x;
    }
    return parent[x] = find(parent, parent[x]);
}

void unionSets(std::vector<int>& parent, std::vector<int>& rank, int x, int y) {
    int xRoot = find(parent, x);
    int yRoot = find(parent, y);

    if (xRoot == yRoot) {
        return;
    }

    if (rank[xRoot] < rank[yRoot]) {
        parent[xRoot] = yRoot;
    } else if (rank[xRoot] > rank[yRoot]) {
        parent[yRoot] = xRoot;
    } else {
        parent[yRoot] = xRoot;
        rank[xRoot]++;
    }
}

std::vector<Edge> kruskal(std::vector<Edge>& edges, int numVertices) {
    std::vector<int> parent(numVertices);
    std::vector<int> rank(numVertices, 0);

    for (int i = 0; i < numVertices; i++) {
        parent[i] = i;
    }

    std::sort(edges.begin(), edges.end(), compareEdges);

    std::vector<Edge> result;

    for (const auto& edge : edges) {
        int sourceRoot = find(parent, edge.source);
        int destRoot = find(parent, edge.destination);

        if (sourceRoot != destRoot) {
            result.push_back(edge);
            unionSets(parent, rank, sourceRoot, destRoot);
        }
    }

    return result;
}

int main() {
    int numVertices, numEdges;

    std::cout << "Enter the number of vertices and edges: ";
    std::cin >> numVertices >> numEdges;

    std::vector<Edge> edges(numEdges);

    std::cout << "Enter the source, destination, and weight of each edge:\n";
    for (int i = 0; i < numEdges; i++) {
        std::cin >> edges[i].source >> edges[i].destination >> edges[i].weight;
    }

    std::vector<Edge> result = kruskal(edges, numVertices);

    std::cout << "Minimum Spanning Tree:\n";
    for (const auto& edge : result) {
        std::cout << "Edge (" << edge.source << ", " << edge.destination << ") Weight: " << edge.weight << std::endl;
    }

    return 0;
}
