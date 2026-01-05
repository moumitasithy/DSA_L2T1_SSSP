#include <bits/stdc++.h>
using namespace std;

int n, k;
int board[15][15];
pair<int,int> knights[105];

int sumDist[15][15];       // total distance of all knights
int unreachable[15][15];   // how many knights can't reach this cell

int dist[15][15];          // BFS temp matrix

int dx[8] = {1,1,2,2,-1,-1,-2,-2};
int dy[8] = {2,-2,1,-1,2,-2,1,-1};

bool valid(int x, int y) {
    return (x >= 0 && y >= 0 && x < n && y < n);
}

void bfs(int sx, int sy) {
    // reset dist matrix
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            dist[i][j] = -1;

    queue<pair<int,int>> q;
    dist[sx][sy] = 0;
    q.push({sx, sy});

    while(!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        for(int i = 0; i < 8; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if(valid(nx, ny) && dist[nx][ny] == -1) {
                dist[nx][ny] = dist[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }

    // accumulate distances into sumDist
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(dist[i][j] == -1) {
                unreachable[i][j]++;   // this knight can't reach
            } else {
                sumDist[i][j] += dist[i][j];
            }
        }
    }
}

int main() {
    cin >> n >> k;

    int cnt = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cin >> board[i][j];
            if(board[i][j] == 1) {
                knights[cnt++] = {i, j};
            }
        }
    }

    // initially sumDist = 0, unreachable = 0 (global array behavior)

    // Run BFS for each knight
    for(int t = 0; t < cnt; t++) {
        bfs(knights[t].first, knights[t].second);
    }

    int ans = INT_MAX;

    // check best cell
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(unreachable[i][j] == 0) {  // all knights can reach
                ans = min(ans, sumDist[i][j]);
            }
        }
    }

    if(ans == INT_MAX) cout << -1 << endl;
    else cout << ans << endl;

    return 0;
}