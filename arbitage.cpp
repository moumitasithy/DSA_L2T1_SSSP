#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v;
    double w;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<Edge> edges;

    for (int i = 0; i < m; i++) {
        int u, v;
        double rate;
        cin >> u >> v >> rate;

        // convert to -log(rate)
        edges.push_back({u, v, -log(rate)});
    }

    // Bellman-Ford
    vector<double> dist(n + 1, 0.0);

    bool arbitrage = false;

    for (int i = 1; i <= n; i++) {
        bool updated = false;
        for (auto &e : edges) {
            if (dist[e.v] > dist[e.u] + e.w) {
                dist[e.v] = dist[e.u] + e.w;
                updated = true;

                // update in nth iteration means negative cycle
                if (i == n) {
                    arbitrage = true;
                }
            }
        }
    }

    if (arbitrage)
        cout << "YES\n";
    else
        cout << "NO\n";

    return 0;
}
