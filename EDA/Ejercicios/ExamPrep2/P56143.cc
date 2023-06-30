#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

typedef vector<char> Vchar;
typedef vector<Vchar> Board;
typedef vector<pair<int,int>> Vcoord;
typedef vector<Vcoord> Mcoord; 
vector<pair<int,int>> movs = {{-1,0},{-1,-1},{0,-1},{1,-1},{1,0},{1,1},{0,1},{-1,1}};
pair<int,int> NEG = {0,0};

bool ok(Board& B, Mcoord& MC, int x, int y, int n, int m, pair<int,int> base) {
    return x >= 0 and y >= 0 and x < n and y < m and B[x][y] != 'X' and MC[x][y] == base; 
} 

void Bfs(Board& B, Mcoord& MC, int x, int y, pair<int,int>& f) {
    int n = B.size();
    int m = B[0].size();
    queue<pair<int,int>> Q;
    Q.push(make_pair(x,y));
    MC[x][y] = make_pair(x,y);

    while(!Q.empty()) {
        pair<int,int> u = Q.front();
        if (B[u.first][u.second] == 'F') {
            f = u;
            return;
        }
        Q.pop();

        for (int i = 0; i < 8; ++i) {
            pair<int,int> v = u;
            v.first += movs[i].first;
            v.second += movs[i].second;
            if (ok(B, MC, v.first, v.second, n, m, {-1,-1})) {
                MC[v.first][v.second] = u;
                Q.push(v);
            }
        }
    }
}

stack<pair<int,int>> Bfs(Board& B, pair<int,int>& org) {
    int n = B.size();
    int m = B[0].size();
    Mcoord MC(n, Vcoord(m, {-1,-1}));
    pair<int,int> farmer;
    Bfs(B, MC, org.first, org.second, farmer);

    stack<pair<int,int>> movknight;
    if (farmer == NEG) return movknight;
    cerr << farmer.first << " " << farmer.second << endl;

    movknight.push(farmer);
    //cerr << farmer.first << " " << farmer.second << endl;
    while(farmer != org) {
        cerr << "DEBUG" << endl;
        movknight.push(MC[farmer.first][farmer.second]);
        farmer.first = MC[farmer.first][farmer.second].first;
        farmer.second = MC[farmer.first][farmer.second].second;

    }
    return movknight;
}

int main() {
    int n, m;
    while(cin >> n >> m) {
        Board B(n, Vchar(m));
        pair<int,int> org;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cin >> B[i][j];
                if (B[i][j] == 'K') {
                    org.first = i;
                    org.second = j;
                }
            }
        }

        stack<pair<int,int>> movements = Bfs(B, org);
        int size = movements.size();
        cerr << size << endl;
        cout << size;
        for (int i = 0; i < size; ++i) {
            pair<int,int> coord = movements.top();
            cout << "  " << coord.first << " " << coord.second;
            movements.pop();
        }
        cout << endl;
    }
}