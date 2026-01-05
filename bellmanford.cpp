#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

struct Edge {
    int u, v, w;
};

int main() {
    int n, m;
    cin >> n >> m;   // n = number of vertices, m = number of edges

    vector<Edge> edges(m);

    for(int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }

    int src;
    cin >> src;   // source vertex

    vector<int> dist(n, INF);
    dist[src] = 0;

    // Relax edges V-1 times
    for(int i = 1; i <= n - 1; i++) {
        for(auto e : edges) {
            if(dist[e.u] != INF && dist[e.u] + e.w < dist[e.v]) {
                dist[e.v] = dist[e.u] + e.w;
            }
        }
    }

    // Check for negative cycle
    bool negativeCycle = false;
    for(auto e : edges) {
        if(dist[e.u] != INF && dist[e.u] + e.w < dist[e.v]) {
            negativeCycle = true;
            break;
        }
    }

    if(negativeCycle) {
        cout << "Negative weight cycle detected\n";
    } else {
        for(int i = 0; i < n; i++) {
            if(dist[i] == INF)
                cout << "INF\n";
            else
                cout << dist[i] << "\n";
        }
    }

    return 0;
}
