#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
int n, m;

int dr[4] = {1, -1, 0, 0};
int dc[4] = {0, 0, 1, -1};
char dirChar[4] = {'D', 'U', 'R', 'L'};

int main() {
    cin >> n >> m;
    vector<string> grid(n);
    for(int i = 0; i < n; i++) cin >> grid[i];

    vector<vector<int>> monsterDist(n, vector<int>(m, INF));
    vector<vector<int>> yourDist(n, vector<int>(m, INF));
    vector<vector<char>> parent(n, vector<char>(m));

    queue<pair<int,int>> q;

    int sr, sc;

    // Step 1: Initialize monster BFS
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(grid[i][j] == 'M') {
                monsterDist[i][j] = 0;
                q.push({i, j});
            }
            if(grid[i][j] == 'A') {
                sr = i;
                sc = j;
            }
        }
    }

    // Monster BFS
    while(!q.empty()) {
        auto [r, c] = q.front(); q.pop();
        for(int d = 0; d < 4; d++) {
            int nr = r + dr[d];
            int nc = c + dc[d];
            if(nr < 0 || nc < 0 || nr >= n || nc >= m) continue;
            if(grid[nr][nc] == '#') continue;
            if(monsterDist[nr][nc] > monsterDist[r][c] + 1) {
                monsterDist[nr][nc] = monsterDist[r][c] + 1;
                q.push({nr, nc});
            }
        }
    }

    // Step 2: Your BFS
    queue<pair<int,int>> q2;
    yourDist[sr][sc] = 0;
    q2.push({sr, sc});

    while(!q2.empty()) {
        auto [r, c] = q2.front(); q2.pop();

        // Reached boundary → SUCCESS
        if(r == 0 || c == 0 || r == n-1 || c == m-1) {
            cout << "YES\n";
            string path;
            while(r != sr || c != sc) {
                char d = parent[r][c];
                path.push_back(d);
                if(d == 'D') r--;
                else if(d == 'U') r++;
                else if(d == 'R') c--;
                else if(d == 'L') c++;
            }
            reverse(path.begin(), path.end());
            cout << path.size() << "\n";
            cout << path << "\n";
            return 0;
        }

        for(int d = 0; d < 4; d++) {
            int nr = r + dr[d];
            int nc = c + dc[d];
            if(nr < 0 || nc < 0 || nr >= n || nc >= m) continue;
            if(grid[nr][nc] == '#') continue;
            if(yourDist[r][c] + 1 >= monsterDist[nr][nc]) continue;
            if(yourDist[nr][nc] == INF) {
                yourDist[nr][nc] = yourDist[r][c] + 1;
                parent[nr][nc] = dirChar[d];
                q2.push({nr, nc});
            }
        }
    }

    cout << "NO\n";
    return 0;
}
