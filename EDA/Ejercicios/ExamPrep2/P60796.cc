#include <iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

typedef vector<char> Vchar;
typedef vector<Vchar> Board;
vector<pair<int,int>> movs = {{1,0}, {0,-1}, {0,1}, {-1,0}};
int INF = std::numeric_limits<int>::max();


bool ok(Board& B, int n, int m, int x, int y) {
    return x >= 0 and y >= 0 and x < n and y < m and B[x][y] != 'X';
}

int Bfs(Board& B, pair<int,int>& org) {
    int n = B.size();
    int m = B[0].size();
    int distmax = INF;
    vector<vector<int>> dis(n, vector<int>(m, -1));
    queue<pair<int,int>> Q;
    Q.push(org);
    dis[org.first][org.second] = 0;

    while(!Q.empty()) {
        pair<int,int> u = Q.front();
        if (B[u.first][u.second] == 't' and dis[u.first][u.second] < distmax) distmax = dis[u.first][u.second];
        Q.pop();

        for (int i = 0; i < 4; ++i) {
            pair<int,int> v = u;
            v.first += movs[i].first;
            v.second += movs[i].second;

            if (ok(B, n, m, v.first, v.second) and dis[v.first][v.second] == -1) {
                dis[v.first][v.second] = dis[u.first][u.second] + 1;
                Q.push(v);
            }
        }
    }
    return distmax;
}

int main() {
    int n, m;
    cin >> n >> m;
    Board B(n, Vchar(m));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) cin >> B[i][j];
    }

    pair<int,int> org;
    cin >> org.first >> org.second;
    --org.first;
    --org.second;

    int dist = Bfs(B, org);
    if (dist != INF) cout << "minimum distance: " << dist << endl;
    else cout << "no treasure can be reached" << endl;
    
}