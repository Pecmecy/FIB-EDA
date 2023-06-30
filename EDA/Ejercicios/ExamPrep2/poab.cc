#include <iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

typedef vector<int> Vint;
typedef vector<Vint> Board;
typedef vector<vector<bool>> Vis;
typedef pair<int,int> Cell;

const int INF = numeric_limits<int>::max();
const vector<Cell> movs = {{1,0}, {-1,0},{0,-1},{0,1}};

bool border(int x, int y, int n) {
    return x == 0 or y == 0 or x == n-1 or y == n-1;
}

int Dijkstra(Board& B, int n) {
    Vis vis(n, vector<bool>(n, false));
    Board dist(n, Vint(n, INF));
    Cell c = {n/2,n/2};
    dist[c.first][c.second] = B[c.first][c.second];
    priority_queue<pair<int,Cell>, vector<pair<int,Cell>>, greater<pair<int,Cell>>> Q;
    Q.push({dist[c.first][c.second], c});

    while(!Q.empty()) {
        Cell u = Q.top().second;
        if (border(u.first, u.second, n)) return dist[u.first][u.second];
        Q.pop();

        for (auto i : movs) {
            Cell v = u;
            v.first += i.first;
            v.second += i.second;

            if (!vis[v.first][v.second]) {
                vis[v.first][v.second] = true;
                if (dist[u.first][u.second] + B[v.first][v.second] < dist[v.first][v.second]) {
                    dist[v.first][v.second] = dist[u.first][u.second] + B[v.first][v.second];
                    Q.push({dist[v.first][v.second], v});
                }
            }
        }
    }
    return -1;
}

int main() {
    int n;
    while (cin >> n) {
        Board B(n, Vint(n));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) cin >> B[i][j];
        }

        cout << Dijkstra(B, n) << endl;
    }
}