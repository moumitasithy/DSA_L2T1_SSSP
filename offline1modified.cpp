#include <bits/stdc++.h>
using namespace std;

class Edge {
public:
    int to;
    long long cost;
    Edge(int _to, long long _cost) {
        to = _to;
        cost = _cost;
    }
};

class Node {
public:
    long long dist;
    int node;
    int used;  // number of coupons used (0,1,2)

    Node(long long _dist, int _node, int _used) {
        dist = _dist;
        node = _node;
        used = _used;
    }

    bool operator>(const Node &other) const {
        return dist > other.dist;
    }
};

int main() {

    int n, m;
    cin >> n >> m;

    vector<vector<Edge>> graph(n + 1);

    for (int i = 0; i < m; i++) {
        int a, b;
        long long c;
        cin >> a >> b >> c;
        graph[a].push_back(Edge(b, c));
    }

    const long long INF = 9e18;

    // dist[node][coupons_used]
    vector<vector<long long>> dist(n + 1, vector<long long>(3, INF));
    dist[1][0] = 0;

    priority_queue<Node, vector<Node>, greater<Node>> pq;
    pq.push(Node(0, 1, 0));

    while (!pq.empty()) {
        Node cur = pq.top();
        pq.pop();

        long long d = cur.dist;
        int u = cur.node;
        int used = cur.used;

        if (d != dist[u][used]) continue;

        for (auto &e : graph[u]) {
            int v = e.to;
            long long w = e.cost;

            // A) Without using coupon
            if (dist[v][used] > d + w) {
                dist[v][used] = d + w;
                pq.push(Node(dist[v][used], v, used));
            }

            // B) Use a coupon (if we still have one)
            if (used < 2) {
                long long half = w / 2;
                if (dist[v][used + 1] > d + half) {
                    dist[v][used + 1] = d + half;
                    pq.push(Node(dist[v][used + 1], v, used + 1));
                }
            }
        }
    }

    long long ans = min({dist[n][0], dist[n][1], dist[n][2]});
    cout << ans << endl;

    return 0;
}
