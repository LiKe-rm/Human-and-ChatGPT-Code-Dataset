#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

struct Person {
    string name;
    int weight;
    vector<string> connections;
};

struct Cluster {
    string max_weight_name;
    int total_weight;
    int num_people;
};

vector<string> split_string(const string &s, char delimiter) {
    vector<string> tokens;
    string token;
    for (const char &c : s) {
        if (c == delimiter) {
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
        } else {
            token += c;
        }
    }
    if (!token.empty()) {
        tokens.push_back(token);
    }
    return tokens;
}

map<string, Person> build_adj_matrix(int num_people) {
    map<string, Person> adj_matrix;
    for (int i = 0; i < num_people; ++i) {
        string line;
        getline(cin, line);
        vector<string> parts = split_string(line, ' ');

        Person person;
        person.name = parts[0];
        person.weight = stoi(parts[1]);

        for (size_t j = 2; j < parts.size(); ++j) {
            person.connections.push_back(parts[j]);
        }
        adj_matrix[person.name] = person;
    }
    return adj_matrix;
}

Cluster bfs(const string &start, map<string, Person> &adj_matrix, int threshold) {
    Cluster cluster;
    cluster.total_weight = 0;
    cluster.num_people = 0;
    cluster.max_weight_name = "";

    queue<string> q;
    q.push(start);

    while (!q.empty()) {
        string current = q.front();
        q.pop();

        if (adj_matrix[current].weight == -1) {
            continue;
        }

        cluster.total_weight += adj_matrix[current].weight;
        cluster.num_people++;

        if (cluster.max_weight_name.empty() || adj_matrix[current].weight > adj_matrix[cluster.max_weight_name].weight) {
            cluster.max_weight_name = current;
        }

        adj_matrix[current].weight = -1;

        for (const string &neighbor : adj_matrix[current].connections) {
            if (adj_matrix[neighbor].weight != -1) {
                q.push(neighbor);
            }
        }
    }

    if (cluster.total_weight <= 2 * threshold || cluster.num_people <= 2) {
        cluster.num_people = 0;
    }

    return cluster;
}

vector<Cluster> find_clusters(map<string, Person> &adj_matrix, int threshold) {
    vector<Cluster> clusters;

    for (const auto &p : adj_matrix) {
        if (p.second.weight != -1) {
            Cluster cluster = bfs(p.first, adj_matrix, threshold);
            if (cluster.num_people > 0) {
                clusters.push_back(cluster);
            }
        }
    }

    return clusters;
}

int main() {
    int num_people, threshold;
    cin >> num_people >> threshold;
    cin.ignore();

    map<string, Person> adj_matrix = build_adj_matrix(num_people);

    vector<Cluster> clusters = find_clusters(adj_matrix, threshold);

    sort(clusters.begin(), clusters.end(), [](const Cluster &a, const Cluster &b) {
        return a.max_weight_name < b.max_weight_name;
    });

    cout << clusters.size() << endl;
    for (const Cluster &cluster : clusters) {
        cout << cluster.max_weight_name << " " << cluster.num_people << endl;
    }

    return 0;
}
