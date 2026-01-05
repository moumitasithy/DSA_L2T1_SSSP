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
    int used;  // 0 = coupon not used, 1 = coupon used

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

    // dist[node][state]
    vector<vector<long long>> dist(n + 1, vector<long long>(2, INF));
    dist[1][0] = 0;

    priority_queue<Node, vector<Node>, greater<Node>> pq;
    pq.push(Node(0, 1, 0));

    while (!pq.empty()) {
        Node cur = pq.top();
        pq.pop();

        long long d = cur.dist;
        int u = cur.node;
        int used = cur.used;

        if (d != dist[u][used])
            continue;

        for (auto &e : graph[u]) {
            int v = e.to;
            long long w = e.cost;

            // A) Normal transition (coupon not used here)
            if (dist[v][used] > d + w) {
                dist[v][used] = d + w;
                pq.push(Node(dist[v][used], v, used));
            }

            // B) Use coupon if not used yet
            if (used == 0) {
                long long half = w / 2;
                if (dist[v][1] > d + half) {
                    dist[v][1] = d + half;
                    pq.push(Node(dist[v][1], v, 1));
                }
            }
        }
    }

    cout << dist[n][1] << endl;

    return 0;
}
