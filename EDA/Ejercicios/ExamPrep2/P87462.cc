#include <iostream>
#include <vector>
using namespace std;

typedef vector<char> Vchar;
typedef vector<Vchar> Board;
vector<pair<int,int>> movs = {{0,0},{-1,0},{-1,-1},{0,-1},{1,-1},{1,0},{1,1},{0,1},{-1,1}};
vector<pair<int,int>> movp = {{-1,0},{0,-1},{1,0},{0,1}};

void write(Board& B) {
    for (int i = 0; i < B.size(); ++i) {
        for (int j = 0; j < B[0].size(); ++j) {
            cout << B[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

void actmap(Board& B, vector<pair<int,int>>& g) {
    for (int i = 0; i < g.size(); ++i) {
        int x = g[i].first;
        int y = g[i].second;
        for (int k = 0; k < 9; ++k) {
            B[x+movs[k].first][y+movs[k].second] = 'X';
        }
    }
}

bool findpellet(Board& B, int x, int y) {
    if (B[x][y] == 'X') return false;
    if (B[x][y] == 'B') return true;
    else B[x][y] = 'X';

    /*if (findpellet(B, x+1,y)) return true;
    if (findpellet(B, x-1,y)) return true;
    if (findpellet(B, x,y+1)) return true;
    if (findpellet(B, x,y-1)) return true;*/

    for (int i = 0; i < 4; ++i) {
        int xx = x + movp[i].first;
        int yy = y + movp[i].second;
        if (findpellet(B, xx, yy)) return true;
    }
    return false;
}

int main() {
    int n, m;
    while (cin >> n >> m) {
        Board B(n, Vchar(m));
        vector<pair<int,int>> ghosts;
        pair<int,int> Pacman;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                char c;
                cin >> c;
                B[i][j] = c;
                
                if (c == 'P') {
                    Pacman.first = i;
                    Pacman.second = j;
                }

                else if (c == 'F') ghosts.push_back(make_pair(i,j));
            }
        }

        actmap(B, ghosts);
        //for (auto l : ghosts) cout << l.first << " " << l.second << endl;
        //write(B);
        if (findpellet(B, Pacman.first, Pacman.second)) cout << "yes" << endl;
        else cout << "no" << endl;
        //write(B);
    }
}