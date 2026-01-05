#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v;
    long long w;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<Edge> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
        edges[i].w = -edges[i].w;   // negate weight
    }

    const long long INF = 1e18;
    vector<long long> dist(n + 1, INF);
    dist[1] = 0;

    vector<int> affected(n + 1, 0);

    // Bellman-Ford
    for (int i = 1; i <= n; i++) {
        for (auto &e : edges) {
            if (dist[e.u] < INF && dist[e.v] > dist[e.u] + e.w) {
                dist[e.v] = dist[e.u] + e.w;

                if (i == n) {
                    affected[e.v] = 1; // part of or affected by negative cycle
                }
            }
        }
    }

    // Propagate negative cycle effect
    for (int i = 1; i <= n; i++) {
        for (auto &e : edges) {
            if (affected[e.u]) {
                affected[e.v] = 1;
            }
        }
    }

    // If destination affected → infinite longest path
    if (affected[n]) {
        cout << -1 << "\n";
    } else {
        cout << -dist[n] << "\n";  // negate back
    }

    return 0;
}
