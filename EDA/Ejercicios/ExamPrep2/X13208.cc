#include <iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

typedef vector<int> Vint;
typedef vector<Vint> Board;
typedef vector<vector<bool>> Mbool;
typedef pair<int,int> Cell;
int INF = std::numeric_limits<int>::max();
const vector<pair<int,int>> movs = {{0,-1},{0,1},{1,0},{-1,0}};

bool border(Cell& u, int n) {
    return u.first == 0 or u.first == n-1 or u.second == 0 or u.second == n-1;
}

int Dijkstra(Board& B, int n) {
    Cell c = {n/2, n/2};
    Board dist(n, Vint(n, INF));
    Mbool vis(n, vector<bool>(n, false));
    priority_queue<pair<int,Cell>, vector<pair<int,Cell>>, greater<pair<int,Cell>>> Q;
    dist[c.first][c.second] = B[c.first][c.second];
    Q.push({dist[c.first][c.second],c});

    while(!Q.empty()) {
        Cell u = Q.top().second;
        if (border(u, n)) {
            cout << vis[c.first][c.second] << endl;
            return dist[u.first][u.second];
        }
        Q.pop();
        if (!vis[u.first][u.second]) {
            vis[u.first][u.second] = true;
            for (auto i : movs) {
                Cell v = u;
                v.first += i.first;
                v.second += i.second;
                if (dist[u.first][u.second] + B[v.first][v.second] < dist[v.first][v.second]) {
                    dist[v.first][v.second] = dist[u.first][u.second] + B[v.first][v.second];
                    Q.push({dist[v.first][v.second],v});
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