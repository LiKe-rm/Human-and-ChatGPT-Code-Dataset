#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

const int MAXN = 510;
const int INF = INT_MAX;

int N, M, S, D;
int G[MAXN][MAXN], d[MAXN], cost[MAXN][MAXN], c[MAXN];
bool vis[MAXN] = {false};

void dijkstra(int s) {
    fill(d, d + MAXN, INF);
    fill(c, c + MAXN, INF);
    d[s] = 0;
    c[s] = 0;
    for (int i = 0; i < N; ++i) {
        int u = -1, minDist = INF;
        for (int j = 0; j < N; ++j) {
            if (!vis[j] && d[j] < minDist) {
                u = j;
                minDist = d[j];
            }
        }
        if (u == -1) return;
        vis[u] = true;
        for (int v = 0; v < N; ++v) {
            if (!vis[v] && G[u][v] != INF) {
                if (d[u] + G[u][v] < d[v]) {
                    d[v] = d[u] + G[u][v];
                    c[v] = c[u] + cost[u][v];
                } else if (d[u] + G[u][v] == d[v]) {
                    if (c[u] + cost[u][v] < c[v]) {
                        c[v] = c[u] + cost[u][v];
                    }
                }
            }
        }
    }
}

int main() {
    cin >> N >> M >> S >> D;
    fill(G[0], G[0] + MAXN * MAXN, INF);
    for (int i = 0; i < M; ++i) {
        int city1, city2, distance, cost_;
        cin >> city1 >> city2 >> distance >> cost_;
        G[city1][city2] = G[city2][city1] = distance;
        cost[city1][city2] = cost[city2][city1] = cost_;
    }

    dijkstra(S);
    cout << d[D] << " " << c[D] << endl;
    return 0;
}
