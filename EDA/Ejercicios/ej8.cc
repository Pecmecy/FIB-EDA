//P70690
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef vector<vector<char>> Map;

/*
void writemap(Vert& coord) {
    for (int i = 0; i < map.size(); ++i) {
        for (int j = 0; j < map[0].size(); ++j) {
            cout << map[i][j];
        }
        cout << endl;
    }
    cout << coord.first << " " << coord.second << endl;
}
*/

bool DFS(Map& map, int r, int c) {
    if (r < map.size() and c < map[0].size() and r >= 0 and c >= 0) {
        if (map[r][c] == 'v') return false;
        if (map[r][c] == 't') return true;
        if (map[r][c] == 'X') return false;
        else map[r][c] = 'v';
        if (DFS(map, r-1, c)) return true;
        else if (DFS(map, r+1, c)) return true;
        else if (DFS(map, r, c-1)) return true;    
        else if (DFS(map, r, c+1)) return true;
    }
    return false;
}

int main() {
    int n, m;
    cin >> n >> m;
    Map map(n, vector<char>(m));
    for (int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            cin >> map[i][j];
        }
    }
    int r, c;
    cin >> r >> c;
    --r;
    --c;
    if(DFS(map, r, c)) cout << "yes" << endl;
    else cout << "no" << endl;
    // cout << (buscar(map, --x, --y)? "yes":"no") << endl;
    // writemap(coord);
}
