#include <bits/stdc++.h>
using namespace std;

int main() {
    //ios::sync_with_stdio(false);
    //cin.tie(NULL);

    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<pair<int,int>>> adj(n+1);//adj list

    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        adj[a].push_back({b, c});
    }

    // --------------------------
    // CHANGED DIST ARRAY
    // --------------------------
    vector<vector<long long>> dist(n+1, vector<long long>(k, LLONG_MAX));//shbr jonn k ta distance

    // min-heap
    priority_queue<pair<long long,int>,
                   vector<pair<long long,int>>,
                   greater<pair<long long,int>>> pq;

    // source
    dist[1][0] = 0;
    pq.push({0, 1});//pair(dis,vertex name)

    // --------------------------
    // MODIFIED DIJKSTRA
    // --------------------------
    while (!pq.empty()) {
        auto top = pq.top();
        pq.pop();

        long long d = top.first;
        int u = top.second;

        // Skip outdated distances
        if (d > dist[u][k-1])
            continue;

        // Relax edges
        for (auto &p : adj[u]) {
            int v = p.first;
            long long w = p.second;
            long long nd = d + w;

            // Check if new distance can fit in k shortest
            if (nd < dist[v][k-1]) {

                dist[v][k-1] = nd;
                sort(dist[v].begin(), dist[v].end());

                pq.push({nd, v});
            }
        }
    }

    // --------------------------
    // OUTPUT THE k SHORTEST DISTANCES
    // --------------------------
    for (int i = 0; i < k; i++) {
        cout << dist[n][i] << " ";
    }
    cout << "\n";

    return 0;
}
