#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>

using namespace std;

const int MAXN = 510;
const int INF = numeric_limits<int>::max() / 2;

struct Edge {
    int to, distance, bikes;
    Edge(int t, int d, int b) : to(t), distance(d), bikes(b) {}
};

vector<Edge> graph[MAXN];
int N, M, S, T;
int bikes[MAXN];
int dist[MAXN];
vector<int> dij_prev[MAXN];

void dijkstra(int s) {
    for (int i = 0; i < N; i++) {
        dist[i] = INF;
    }
    dist[s] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, s});

    while (!pq.empty()) {
        int current = pq.top().second;
        int current_dist = pq.top().first;
        pq.pop();

        if (current_dist > dist[current]) continue;

        for (const Edge &edge : graph[current]) {
            int to = edge.to;
            int d = edge.distance;
            if (current_dist + d < dist[to]) {
                dist[to] = current_dist + d;
                pq.push({dist[to], to});
                dij_prev[to].clear();
                dij_prev[to].push_back(current);
            } else if (current_dist + d == dist[to]) {
                dij_prev[to].push_back(current);
            }
        }
    }
}

int min_bikes_brought = INF, min_bikes_taken = INF;
vector<int> best_path, current_path;

void dfs(int node, int bikes_brought, int bikes_taken) {
    current_path.push_back(node);
    if (node == S) {
        if (bikes_brought < min_bikes_brought ||
            (bikes_brought == min_bikes_brought && bikes_taken < min_bikes_taken)) {
            min_bikes_brought = bikes_brought;
            min_bikes_taken = bikes_taken;
            best_path = current_path;
        }
    } else {
        for (int prev : dij_prev[node]) {
            int new_bikes_brought = bikes_brought;
            int new_bikes_taken = bikes_taken;
            if (bikes[prev] > 0) {
                new_bikes_brought += bikes[prev];
            } else {
                new_bikes_taken -= bikes[prev];
            }
            dfs(prev, min(new_bikes_brought, N), new_bikes_taken);
        }
    }
    current_path.pop_back();
}

int main() {
    cin >> N >> M >> S >> T;
    for (int i = 0; i < N; i++) {
        cin >> bikes[i];
        bikes[i] -= 1;
    }

    for (int i = 0; i < M; i++) {
        int u, v, d;
        cin >> u >> v >> d;
        graph[u].emplace_back(v, d, bikes[v]);
        graph[v].emplace_back(u, d, bikes[u]);
    }

    dijkstra(S);
    dfs(T, 0, 0);

    reverse(best_path.begin(), best_path.end());
    cout << min_bikes_brought << " ";
    for (int i = 0; i < best_path.size() - 1; i++) {
        cout << best_path[i] << "->";
    }
    cout << best_path.back() << " " << min_bikes_taken << endl;

    return 0;
}
