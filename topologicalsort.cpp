#include <bits/stdc++.h>
using namespace std;

void dfs(int node, vector<int>& vis, vector<vector<int>>& adj, vector<int>& topo) {
    vis[node] = 1;

    for(int next : adj[node]) {
        if(!vis[next]) {
            dfs(next, vis, adj, topo);
        }
    }

    topo.push_back(node);   // add after visiting all neighbors
}

int main() {
    int n, m;
    cin >> n >> m;           // n = number of nodes, m = edges

    vector<vector<int>> adj(n);
    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;       // directed edge u -> v
        adj[u].push_back(v);
    }

    vector<int> vis(n, 0);
    vector<int> topo;

    for(int i = 0; i < n; i++) {
        if(!vis[i]) dfs(i, vis, adj, topo);
    }

    reverse(topo.begin(), topo.end());   // final topological order

    cout << "Topological Sort: ";
    for(int x : topo) cout << x << " ";
    cout << endl;

    return 0;
}
