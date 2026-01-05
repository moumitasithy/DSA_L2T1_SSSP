#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<pair<int,long long>>> g(n+1);

    for(int i = 0; i < m; i++) {
        int a, b;
        long long c;
        cin >> a >> b >> c;
        g[a].push_back({b, c});
    }

    vector<long long> best(n+1, 0);
    priority_queue<pair<long long,int>> pq;

    best[1] = LLONG_MAX;
    pq.push({best[1], 1});

    while(!pq.empty()) {
        auto [speed, u] = pq.top();
        pq.pop();

        if(speed < best[u]) continue;

        for(auto [v, c] : g[u]) {
            long long ns = min(speed, c);
            if(ns > best[v]) {
                best[v] = ns;
                pq.push({ns, v});
            }
        }
    }

    cout << best[n];
}
