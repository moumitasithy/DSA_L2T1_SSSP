#include <bits/stdc++.h>
using namespace std;

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> grid(n, vector<int>(m));
    vector<vector<int>> vis(n, vector<int>(m, 0));

    // input grid
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }

    queue<pair<int,int>> q;

    // Starting point (0,0) for example
    q.push({0,0});
    vis[0][0] = 1;

    while(!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        cout << "Visiting: (" << x << "," << y << ")\n"; // optional

        for(int k = 0; k < 4; k++) {
            int nx = x + dx[k];
            int ny = y + dy[k];

            // boundary check + visited check
            if(nx >= 0 && nx < n && ny >= 0 && ny < m) {
                if(!vis[nx][ny]) {
                    vis[nx][ny] = 1;
                    q.push({nx, ny});
                }
            }
        }
    }

    return 0;
}
