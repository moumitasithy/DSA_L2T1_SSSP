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
    }

    // Bellman-Ford
    vector<long long> dist(n + 1, 0);

    bool hasNegativeCycle = false;

    for (int i = 1; i <= n; i++) {
        bool updated = false;
        for (auto &e : edges) {
            if (dist[e.v] > dist[e.u] + e.w) {
                dist[e.v] = dist[e.u] + e.w;
                updated = true;

                if (i == n) {
                    hasNegativeCycle = true;
                }
            }
        }
        if (!updated) break;
    }

    if (hasNegativeCycle)
        cout << "YES\n";
    else
        cout << "NO\n";

    return 0;
}
