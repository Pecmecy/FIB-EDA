#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef vector<char> Vec;
typedef vector<Vec> Board;

vector<pair<int,int>> movs = {{-1,0}, {0,-1}, {0,1}, {1,0}, {1,1},{1,-1}, {-1,1}, {-1,-1}};

/*bool findpellet(Board& B, pair<int,int> org) {
    int n = B.size();
    int m = B[0].size();
    vector<vector<bool>> vis(n, vector<bool>(m, false));
    queue<pair<int,int>> Q;
    Q.push(org);

    while(!Q.empty()) {
        pair<int,int> u = Q.front();
        if (B[u.first][u.second] == "B") return true;
        Q.pop();

        for ()) {
            pair<int,int> v = u;

        }
    }
}*/

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
        if (ok(B, x+movs[i].first, y + movs[i].second) and B[x + movs[i].first][y + movs[i].second] == 'F') return true;
    }
    return false;
}


bool findpellet(Board& B, int x, int y) {
    if (ok(B, x, y)) {
        if (ghostnear(B, x, y)) return false;
        if (B[x][y] == 'X') return false;
        if (B[x][y] == 'B') return true;
        if (B[x][y] == 'v') return false;
        else B[x][y] = 'v';
        
        write(B);
        if (findpellet(B, x+1, y)) return true;
        else if (findpellet(B, x-1, y)) return true;
        else if (findpellet(B, x, y+1)) return true;
        else if (findpellet(B, x, y-1)) return true;
    }
    return false;
}

int main() {
    int n, m;
    while(cin >> n >> m) {
        Board B(n, Vec(m));
        pair<int,int> org;          // Pos original, .first X, .second Y

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cin >> B[i][j];
                if (B[i][j] == 'P') {
                    org.first = i;
                    org.second = j;
                }
            }
        }

        if (findpellet(B, org.first, org.second)) cout << "yes" << endl;
        else cout << "no" << endl;
    }
}