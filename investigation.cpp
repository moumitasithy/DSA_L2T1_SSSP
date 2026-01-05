#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;
const long long MOD = 1e9 + 7;

int main() {
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<pair<int,int>>> adj(n+1);

    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        adj[a].push_back({b, c});
    }

    // ------------------------------------------------
    // Arrays to store information
    // ------------------------------------------------
    vector<long long> dist(n+1, INF);
    vector<long long> ways(n+1, 0);
    vector<long long> minFlights(n+1, INF);
    vector<long long> maxFlights(n+1, 0);

    // Priority queue (min-heap)
    priority_queue<pair<long long,int>,
        vector<pair<long long,int>>,
        greater<pair<long long,int>>> pq;

    // Initialize source city (1)
    dist[1] = 0;
    ways[1] = 1;
    minFlights[1] = 0;
    maxFlights[1] = 0;

    pq.push({0, 1});

    // ------------------------------------------------
    // Modified Dijkstra
    // ------------------------------------------------
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist[u]) continue;

        for (auto &edge : adj[u]) {
            int v = edge.first;
            long long w = edge.second;

            long long nd = d + w;

            // Case 1: Better (smaller) distance found
            if (nd < dist[v]) {
                dist[v] = nd;
                ways[v] = ways[u] % MOD;
                minFlights[v] = minFlights[u] + 1;
                maxFlights[v] = maxFlights[u] + 1;

                pq.push({nd, v});
            }
            // Case 2: Same distance again → add paths
            else if (nd == dist[v]) {
                ways[v] = (ways[v] + ways[u]) % MOD;
                minFlights[v] = min(minFlights[v], minFlights[u] + 1);
                maxFlights[v] = max(maxFlights[v], maxFlights[u] + 1);
            }
        }
    }

    // ------------------------------------------------
    // Output
    // ------------------------------------------------
    cout << dist[n] << " "
         << ways[n] << " "
         << minFlights[n] << " "
         << maxFlights[n] << "\n";

    return 0;
}
