#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef vector<char> Vec;
typedef vector<Vec> Board;
vector<pair<int,int>> movs = {{-1,0}, {0,-1}, {0,1}, {1,0}, {1,1},{1,-1}, {-1,1}, {-1,-1}};

void write(Board& B) {
    for (int i = 0; i < B.size(); ++i) {
        for (int j = 0; j < B[0].size(); ++j) {
            cout << B[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

bool ok(Board& B, int x, int y) {
    return x >= 0 and y >= 0 and x < B.size() and y < B[0].size();
}

bool ghostnear (Board& B, int x, int y) {
    for (int i = 0; i < 8; ++i) {
        if (ok(B, x+movs[i].first, y + movs[i].second) and B[x + movs[i].first][y + movs[i].second] == 'F') {
            B[x + movs[i].first][y + movs[i].second] = '-';
            return true;
        }
    }
    return false;
}

void tractar(Board& B, int x, int y, vector<vector<bool>>& vis, queue<pair<int,int>>& Q) {
    int n = B.size();
    int m = B[0].size();
    if (x >= 0 and x < n and y >= 0 and y < m) {
        if (!vis[x][y]) {
            vis[x][y] = true;
            if (B[x][y] != 'X') Q.push(make_pair(x,y));
        }
    }
}

bool bfs(Board& B, int x, int y) {
    int n = B.size();
    int m = B[0].size();
    vector<vector<bool>> vis (n, vector<bool>(m, false));
    queue<pair<int,int>> Q;

    vis[x][y] = true;
    Q.push(make_pair(x,y));
    while(!Q.empty()) {
        pair<int,int> u = Q.front();
        if (B[u.first][u.second] == 'B') return true;
        Q.pop();

        if (!ghostnear(B, u.first, u.second)) {tractar(B, u.first - 1, u.second, vis, Q); cerr << "DEBUG UP" << endl;}
        if (!ghostnear(B, u.first, u.second)) {tractar(B, u.first + 1, u.second, vis, Q);  cerr << "DEBUG DOWN" << endl;}
        if (!ghostnear(B, u.first, u.second)) {tractar(B, u.first, u.second - 1, vis, Q);  cerr << "DEBUG LEFT" << endl;}
        if (!ghostnear(B, u.first, u.second)) {tractar(B, u.first, u.second + 1, vis, Q);  cerr << "DEBUG RIGHT" << endl;}
    }
    return false;
}

int main() {
    int n, m;
    while(cin >> n >> m) {
        Board B(n, Vec(m));
        //pair<int,int> org;          // Pos original, .first X, .second Y
        int x, y;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cin >> B[i][j];
                if (B[i][j] == 'P') {
                    x = i;
                    y = j;
                }
            }
        }
        
        if (bfs(B, x, y)) cout << "yes" << endl;
        else cout << "no" << endl;
        write(B);
    }
}