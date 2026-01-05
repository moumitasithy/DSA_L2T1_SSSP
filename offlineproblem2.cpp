#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v;
    long long w;
};

int main() {
    int n, m;
    cin >> n >> m;

    vector<Edge> edges(m);

    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }

    const long long INF = 1e18;

    // Try starting Bellman-Ford from each node
    for (int start = 1; start <= n; start++) {

        vector<long long> dist(n + 1, INF);
        vector<int> parent(n + 1, -1);
        dist[start] = 0;

        int x = -1;

        // n relaxations
        for (int i = 1; i <= n; i++) {
            x = -1;
            for (auto &e : edges) {
                if (dist[e.u] < INF && dist[e.v] > dist[e.u] + e.w) {
                    dist[e.v] = dist[e.u] + e.w;
                    parent[e.v] = e.u;
                    x = e.v;
                }
            }
        }

        // no cycle from this start
        if (x == -1) continue;

        // negative cycle found
        int y = x;
        for (int i = 0; i < n; i++)
            y = parent[y];

        vector<int> cycle;
        cycle.push_back(y);
        int cur = parent[y];

        while (cur != y) {
            cycle.push_back(cur);
            cur = parent[cur];
        }

        reverse(cycle.begin(), cycle.end());

        for (int v : cycle) cout << v << " ";
        return 0;
    }

    cout << -1;
    return 0;
}
