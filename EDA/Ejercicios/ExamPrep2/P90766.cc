#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef vector<char> Vchar;
typedef vector<Vchar> Board;
vector<pair<int,int>> movs = {{1,0}, {0,-1}, {0,1}, {-1,0}};

bool ok(Board& B, int n, int m, int x, int y) {
    return x >= 0 and y >= 0 and x < n and y < m and B[x][y] != 'X';
}

int Bfs(Board& B, pair<int,int>& org) {
    int contador = 0;
    int n = B.size();
    int m = B[0].size();
    vector<vector<bool>> vis(n, vector<bool>(m, false));
    queue<pair<int,int>> Q;
    Q.push(org);
    vis[org.first][org.second];

    while(!Q.empty()) {
        pair<int,int> u = Q.front();
        if (B[u.first][u.second] == 't') ++contador;
        Q.pop();

        for (int i = 0; i < 4; ++i) {
            pair<int,int> v = u;
            v.first += movs[i].first;
            v.second += movs[i].second;

            if (ok(B, n, m, v.first, v.second) and!vis[v.first][v.second]) {
                vis[v.first][v.second] = true;
                Q.push(v);
            }
        }
    }
    return contador;
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

    cout << Bfs(B, org) << endl;
    
}