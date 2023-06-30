//P90766
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef vector<vector<char>> Map;
typedef vector<vector<bool>> Vis;

int sumx[4] = {1, -1, 0, 0};
int sumy[4] = {0, 0, 1, -1};

void writemap(Map& map) {
    for (int i = 0; i < map.size(); ++i) {
        for (int j = 0; j < map[0].size(); ++j) {
            cout << map[i][j];
        }
        cout << endl;
    }
}


int DFS (Map& map, int x, int y, Vis& vis, int n, int m) {
    int contador = 0;
    vis[x][y] = true;
    if (map[x][y] == 't') ++contador;
    if (map[x][y] != 'X') {
        for (int i = 0; i < 4; ++i) {
            int xn = x + sumx[i];
            int yn = y + sumy[i];
            if (xn >= 0 and yn >= 0 and xn < n and yn < m and !vis[xn][yn]) {
                contador = contador + DFS(map, xn, yn, vis, n, m);
            }
        }
    }
    return contador;
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
    Vis vis(n, vector<bool>(m, false));
    int cont = (DFS(map, r-1, c-1, vis, n, m));
    cout << cont << endl;
    // cout << (buscar(map, --x, --y)? "yes":"no") << endl;
    // writemap(coord);
}
